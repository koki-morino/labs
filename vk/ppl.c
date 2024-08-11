#include "ppl.h"

#include <vulkan/vulkan_core.h>

static int8_t pipeline_layout(GPU_ctx *ctx);

/**
 * Create descriptor set layout for two buffers.
 */
static int8_t create_descriptor_set_layout(GPU_ctx *ctx);

int8_t GPU_pipeline(GPU_ctx *ctx)
{
    if (GPU_shader_module(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    if (pipeline_layout(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    VkComputePipelineCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    create_info.layout = ctx->pipeline_layout;
    create_info.basePipelineIndex = -1;
    create_info.stage.sType =
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    create_info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    create_info.stage.pName = "main";
    create_info.stage.module = ctx->shader_module;

    VkResult result;
    if ((result = vkCreateComputePipelines(ctx->ldev, VK_NULL_HANDLE, 1,
                                           &create_info, NULL,
                                           &ctx->pipeline)) != VK_SUCCESS)
    {
        printf("Failed to create compute pipeline (%d)\n", result);
        return EXIT_FAILURE;
    }
}

int8_t pipeline_layout(GPU_ctx *ctx)
{
    if (create_descriptor_set_layout(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    VkPipelineLayoutCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    create_info.pSetLayouts = &ctx->descriptor_set_layout;
    create_info.setLayoutCount = 1;

    VkResult result;
    if ((result = vkCreatePipelineLayout(ctx->ldev, &create_info, NULL,
                                         &ctx->pipeline_layout)) != VK_SUCCESS)
    {
        printf("Failed to create compute pipeline layout (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int8_t create_descriptor_set_layout(GPU_ctx *ctx)
{
    VkDescriptorSetLayoutBinding bindings[2];
    memset(&bindings, 0, sizeof(bindings));

    bindings[0].binding = 0;
    bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[0].descriptorCount = 1;

    bindings[1].binding = 1;
    bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[1].descriptorCount = 1;

    VkDescriptorSetLayoutCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    create_info.bindingCount = 2;
    create_info.pBindings = bindings;

    VkResult result;
    if ((result = vkCreateDescriptorSetLayout(ctx->ldev, &create_info, NULL,
                                              &ctx->descriptor_set_layout)) !=
        VK_SUCCESS)
    {
        printf("Failed to create descriptor set layout (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
