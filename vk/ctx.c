#include "ctx.h"

int8_t GPU_ctx_init(GPU_ctx *ctx)
{
    memset(ctx, 0, sizeof(GPU_ctx));
    return EXIT_SUCCESS;
}

void GPU_ctx_destroy(GPU_ctx *ctx)
{
    if (ctx->fence)
    {
        vkDestroyFence(ctx->ldev, ctx->fence, NULL);
        ctx->fence = NULL;
    }

    if (ctx->compute_command_pool)
    {
        vkDestroyCommandPool(ctx->ldev, ctx->compute_command_pool, NULL);
        ctx->compute_command_pool = NULL;
    }

    if (ctx->input_buffer)
    {
        vkDestroyBuffer(ctx->ldev, ctx->input_buffer, NULL);
        ctx->input_buffer = NULL;
    }

    if (ctx->input_memory)
    {
        vkFreeMemory(ctx->ldev, ctx->input_memory, NULL);
        ctx->input_memory = NULL;
    }

    if (ctx->output_buffer)
    {
        vkDestroyBuffer(ctx->ldev, ctx->output_buffer, NULL);
        ctx->output_buffer = NULL;
    }

    if (ctx->output_memory)
    {
        vkFreeMemory(ctx->ldev, ctx->output_memory, NULL);
        ctx->output_memory = NULL;
    }

    if (ctx->descriptor_pool)
    {
        vkDestroyDescriptorPool(ctx->ldev, ctx->descriptor_pool, NULL);
        ctx->descriptor_pool = NULL;
    }

    if (ctx->shader_module)
    {
        vkDestroyShaderModule(ctx->ldev, ctx->shader_module, NULL);
        ctx->shader_module = NULL;
    }

    if (ctx->descriptor_set_layout)
    {
        vkDestroyDescriptorSetLayout(ctx->ldev, ctx->descriptor_set_layout,
                                     NULL);
        ctx->descriptor_set_layout = NULL;
    }

    if (ctx->pipeline_layout)
    {
        vkDestroyPipelineLayout(ctx->ldev, ctx->pipeline_layout, NULL);
        ctx->pipeline_layout = NULL;
    }

    if (ctx->pipeline)
    {
        vkDestroyPipeline(ctx->ldev, ctx->pipeline, NULL);
        ctx->pipeline = NULL;
    }

    if (ctx->ldev)
    {
        vkDestroyDevice(ctx->ldev, NULL);
        ctx->ldev = NULL;
    }
}
