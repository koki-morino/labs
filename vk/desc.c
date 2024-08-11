#include "desc.h"

int8_t desc_set(GPU_ctx *ctx);
static int8_t desc_pool(GPU_ctx *ctx);

int8_t GPU_desc(GPU_ctx *ctx, uint32_t input_size, uint32_t output_size)
{
    if (desc_set(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    // Input buffer
    if (GPU_mem(ctx, input_size, &ctx->input_buffer, &ctx->input_memory) !=
        EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    // Output buffer
    if (GPU_mem(ctx, output_size, &ctx->output_buffer, &ctx->output_memory) !=
        EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    VkDescriptorBufferInfo buffers[2];
    buffers[0].buffer = ctx->input_buffer;
    buffers[0].offset = 0;
    buffers[0].range = input_size;

    buffers[1].buffer = ctx->output_buffer;
    buffers[1].offset = 0;
    buffers[1].range = output_size;

    VkWriteDescriptorSet writes;
    memset(&writes, 0, sizeof(writes));
    writes.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes.dstSet = ctx->descriptor_set;
    writes.dstBinding = 0;
    writes.descriptorCount = 2;
    writes.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    writes.pBufferInfo = buffers;

    vkUpdateDescriptorSets(ctx->ldev, 1, &writes, 0, NULL);

    return EXIT_SUCCESS;
}

int8_t desc_set(GPU_ctx *ctx)
{
    desc_pool(ctx);

    VkDescriptorSetAllocateInfo descriptor_set_allocate_info;
    memset(&descriptor_set_allocate_info, 0,
           sizeof(descriptor_set_allocate_info));
    descriptor_set_allocate_info.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptor_set_allocate_info.descriptorSetCount = 1;
    descriptor_set_allocate_info.pSetLayouts = &ctx->descriptor_set_layout;
    descriptor_set_allocate_info.descriptorPool = ctx->descriptor_pool;

    VkResult result;
    if ((result = vkAllocateDescriptorSets(
             ctx->ldev, &descriptor_set_allocate_info, &ctx->descriptor_set)) !=
        VK_SUCCESS)
    {
        printf("Failed to allocate descriptor set (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int8_t desc_pool(GPU_ctx *ctx)
{
    VkDescriptorPoolSize pool_size;
    memset(&pool_size, 0, sizeof(pool_size));
    pool_size.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    pool_size.descriptorCount = 2;

    VkDescriptorPoolCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    create_info.maxSets = 1;
    create_info.pPoolSizes = &pool_size;
    create_info.poolSizeCount = 1;

    VkResult result;
    if ((result = vkCreateDescriptorPool(ctx->ldev, &create_info, NULL,
                                         &ctx->descriptor_pool)) != VK_SUCCESS)
    {
        printf("Failed to create descriptor pool (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
