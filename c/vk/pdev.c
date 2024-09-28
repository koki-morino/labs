#include "pdev.h"

static int8_t instance(GPU_ctx *ctx);

int8_t GPU_pdev(GPU_ctx *ctx)
{
    if (instance(ctx) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    };

    uint32_t count = 0;

    VkResult result;
    if ((result = vkEnumeratePhysicalDevices(ctx->instance, &count, NULL)) !=
        VK_SUCCESS)
    {
        printf("Failed to enumerate physical devices (%d)\n", result);
        return EXIT_FAILURE;
    }

    VkPhysicalDevice *devices = malloc(sizeof(VkPhysicalDevice) * count);
    if ((result = vkEnumeratePhysicalDevices(ctx->instance, &count, devices)) !=
        VK_SUCCESS)
    {
        printf("Failed to get physical devices (%d)\n", result);
        return EXIT_FAILURE;
    }

    ctx->pdev = devices[0];
    free(devices);
    devices = NULL;

    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;

    vkGetPhysicalDeviceProperties(ctx->pdev, &properties);
    vkGetPhysicalDeviceFeatures(ctx->pdev, &features);

    return EXIT_SUCCESS;
}

int8_t instance(GPU_ctx *ctx)
{
#ifndef NDEBUG
    const char *layer_names[] = {"VK_LAYER_KHRONOS_validation"};
    uint32_t layer_count = 1;
#else
    const char **layer_names = NULL;
    uint32_t layer_count = 0;
#endif

    VkInstanceCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.ppEnabledLayerNames = layer_names;
    create_info.enabledLayerCount = layer_count;

    VkResult result;
    if ((result = vkCreateInstance(&create_info, NULL, &ctx->instance)) !=
        VK_SUCCESS)
    {
        printf("Failed to create instance (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
