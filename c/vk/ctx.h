/**
 * Context
 */

#ifndef GPU_CTX_H
#define GPU_CTX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

typedef struct GPU_ctx
{
    VkInstance instance;
    VkPhysicalDevice pdev;
    VkDevice ldev;
    uint32_t compute_queue_family_index;
    VkQueue compute_queue;
    VkDescriptorSetLayout descriptor_set_layout;
    VkPipelineLayout pipeline_layout;
    VkShaderModule shader_module;
    VkPipeline pipeline;
    VkDescriptorPool descriptor_pool;
    VkDescriptorSet descriptor_set;
    VkDeviceMemory input_memory;
    VkBuffer input_buffer;
    VkDeviceMemory output_memory;
    VkBuffer output_buffer;
    VkCommandPool compute_command_pool;
    VkCommandBuffer command_buffer;
    VkFence fence;
} GPU_ctx;

int8_t GPU_ctx_init(GPU_ctx *ctx);

/**
 * Free all resources.
 */
void GPU_ctx_destroy(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
