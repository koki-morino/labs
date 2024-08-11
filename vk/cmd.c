#include "cmd.h"

static int8_t cmd_pool(GPU_ctx *ctx);

static int8_t cmd_buf(GPU_ctx *ctx);

int8_t GPU_cmd(GPU_ctx *ctx)
{
    if (cmd_pool(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    if (cmd_buf(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    if (GPU_fence(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    VkSubmitInfo submit_info;
    memset(&submit_info, 0, sizeof(submit_info));
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &ctx->command_buffer;

    VkResult result;
    if ((result = vkQueueSubmit(ctx->compute_queue, 1, &submit_info,
                                ctx->fence)) != VK_SUCCESS)
    {
        printf("Failed to submit the command buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    // Timeout in nanoseconds
    if ((result = vkWaitForFences(ctx->ldev, 1, &ctx->fence, VK_TRUE,
                                  1000 * 1000)) != VK_SUCCESS)
    {
        printf("Failed to wait for the fence (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int8_t cmd_pool(GPU_ctx *ctx)
{
    VkCommandPoolCreateInfo command_pool_create_info;
    memset(&command_pool_create_info, 0, sizeof(command_pool_create_info));
    command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.queueFamilyIndex = ctx->compute_queue_family_index;

    VkResult result;
    if ((result = vkCreateCommandPool(ctx->ldev, &command_pool_create_info,
                                      NULL, &ctx->compute_command_pool)) !=
        VK_SUCCESS)
    {
        printf("Failed to create a compute command pool (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int8_t cmd_buf(GPU_ctx *ctx)
{
    VkCommandBufferAllocateInfo alloc_info;
    memset(&alloc_info, 0, sizeof(alloc_info));
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool = ctx->compute_command_pool;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = 1;

    VkResult result;
    if ((result = vkAllocateCommandBuffers(ctx->ldev, &alloc_info,
                                           &ctx->command_buffer)) != VK_SUCCESS)
    {
        printf("Failed to allocate the command buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    VkCommandBufferBeginInfo begin_info;
    memset(&begin_info, 0, sizeof(begin_info));
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if ((result = vkBeginCommandBuffer(ctx->command_buffer, &begin_info)) !=
        VK_SUCCESS)
    {
        printf("Failed to begin the command buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    vkCmdBindPipeline(ctx->command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE,
                      ctx->pipeline);
    vkCmdBindDescriptorSets(ctx->command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE,
                            ctx->pipeline_layout, 0, 1, &ctx->descriptor_set, 0,
                            NULL);
    vkCmdDispatch(ctx->command_buffer, 6, 1, 1);

    if ((result = vkEndCommandBuffer(ctx->command_buffer)) != VK_SUCCESS)
    {
        printf("Failed to end the command buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
