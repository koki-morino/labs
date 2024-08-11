#include "ldev.h"

int8_t GPU_ldev(GPU_ctx *ctx)
{
    uint32_t count = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(ctx->pdev, &count, NULL);
    printf("%u queue families found\n", count);

    VkQueueFamilyProperties *queue_families =
        malloc(sizeof(VkQueueFamilyProperties) * count);

    vkGetPhysicalDeviceQueueFamilyProperties(ctx->pdev, &count, queue_families);

    // Search for compute capable queue family.
    while ((ctx->compute_queue_family_index < count) &&
           (queue_families[ctx->compute_queue_family_index].queueFlags &
            VK_QUEUE_COMPUTE_BIT) == 0)
    {
        ++ctx->compute_queue_family_index;
    }

    free(queue_families);

    if (ctx->compute_queue_family_index == count)
    {
        printf("Failed to find requested queue family\n");
        return EXIT_FAILURE;
    }

    float priority = 1.f;

    VkDeviceQueueCreateInfo queue_create_info;
    memset(&queue_create_info, 0, sizeof(queue_create_info));
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = ctx->compute_queue_family_index;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &priority;

    VkDeviceCreateInfo device_create_info;
    memset(&device_create_info, 0, sizeof(device_create_info));
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.pQueueCreateInfos = &queue_create_info;
    device_create_info.queueCreateInfoCount = 1;

    VkResult result;
    if ((result = vkCreateDevice(ctx->pdev, &device_create_info, NULL,
                                 &ctx->ldev)) != VK_SUCCESS)
    {
        printf("Failed to create logical device (%d)\n", result);
        return EXIT_FAILURE;
    }

    vkGetDeviceQueue(ctx->ldev, ctx->compute_queue_family_index, 0,
                     &ctx->compute_queue);

    return EXIT_SUCCESS;
}
