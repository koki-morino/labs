#include "shader.h"

int8_t GPU_shader_module(GPU_ctx *ctx)
{
    uint32_t data[8192];

    FILE *f = fopen("compute.spv", "rb");
    if (f == NULL)
    {
        printf("Failed to open the shader file\n");
        return EXIT_FAILURE;
    }

    size_t size = fread(data, 1, sizeof(data), f);
    fclose(f);

    if (!size)
    {
        printf("Faile to read the shader file\n");
        return EXIT_FAILURE;
    }

    VkShaderModuleCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = size;
    create_info.pCode = data;

    // Destroy previous shader module if there is.
    if (ctx->shader_module)
    {
        vkDestroyShaderModule(ctx->ldev, ctx->shader_module, NULL);
        ctx->shader_module = NULL;
    }

    VkResult result;
    if ((result = vkCreateShaderModule(ctx->ldev, &create_info, NULL,
                                       &ctx->shader_module)) != VK_SUCCESS)
    {
        printf("Failed to create shader module (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
