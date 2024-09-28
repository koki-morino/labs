#include "fence.h"

int8_t GPU_fence(GPU_ctx *ctx)
{
    VkFenceCreateInfo fence_create_info;
    memset(&fence_create_info, 0, sizeof(fence_create_info));
    fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    VkResult result;
    if ((result = vkCreateFence(ctx->ldev, &fence_create_info, NULL,
                                &ctx->fence)) != VK_SUCCESS)
    {
        printf("Failed to create fence (%d)\n", result);
        return EXIT_FAILURE;
    }
}
