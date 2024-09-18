#include "mem.h"

static uint32_t mem_type_index(GPU_ctx *ctx, uint32_t type_bits,
                               VkMemoryPropertyFlags prop_flags);

int8_t GPU_mem_to(GPU_ctx *ctx, VkDeviceMemory *dst, void *data, uint32_t size)
{
    void *dst_addr;

    VkResult result;
    if ((result = vkMapMemory(ctx->ldev, *dst, 0, size, 0, &dst_addr)) !=
        VK_SUCCESS)
    {
        printf("Failed to map destination memory (%d)\n", result);
        return EXIT_FAILURE;
    }

    memcpy(dst_addr, data, size);
    vkUnmapMemory(ctx->ldev, *dst);

    return EXIT_SUCCESS;
}

int8_t GPU_mem_from(GPU_ctx *ctx, VkDeviceMemory *src, void *data,
                    uint32_t size)
{
    void *src_addr;

    VkResult result;
    if ((result = vkMapMemory(ctx->ldev, *src, 0, size, 0, &src_addr)) !=
        VK_SUCCESS)
    {
        printf("Failed to map source memory\n", result);
        return EXIT_FAILURE;
    }

    memcpy(data, src_addr, size);
    vkUnmapMemory(ctx->ldev, *src);

    return EXIT_SUCCESS;
}

int8_t GPU_mem(GPU_ctx *ctx, uint32_t size, VkBuffer *buffer,
               VkDeviceMemory *memory)
{
    VkBufferCreateInfo create_info;
    memset(&create_info, 0, sizeof(create_info));
    create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    create_info.size = size;
    create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

    VkResult result;
    if ((result = vkCreateBuffer(ctx->ldev, &create_info, NULL, buffer)) !=
        VK_SUCCESS)
    {
        printf("Failed to create memory buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    VkMemoryRequirements requirements;
    vkGetBufferMemoryRequirements(ctx->ldev, *buffer, &requirements);

    VkMemoryAllocateInfo allocate_info;
    memset(&allocate_info, 0, sizeof(allocate_info));
    allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocate_info.allocationSize = requirements.size;
    allocate_info.memoryTypeIndex =
        mem_type_index(ctx, requirements.memoryTypeBits,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                           VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if ((result = vkAllocateMemory(ctx->ldev, &allocate_info, NULL, memory)) !=
        VK_SUCCESS)
    {
        printf("Failed to allocate memory for buffer (%d)\n", result);
        return EXIT_FAILURE;
    }

    if ((result = vkBindBufferMemory(ctx->ldev, *buffer, *memory, 0)) !=
        VK_SUCCESS)
    {
        printf("Failed to bind buffer and memory (%d)\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

uint32_t mem_type_index(GPU_ctx *ctx, uint32_t type_bits,
                        VkMemoryPropertyFlags prop_flags)
{
    VkPhysicalDeviceMemoryProperties memory_properties;
    vkGetPhysicalDeviceMemoryProperties(ctx->pdev, &memory_properties);

    for (uint32_t i = 0; i < memory_properties.memoryTypeCount; ++i)
    {
        // Check for memory type and then its properties.
        // Type bits corresponds to memory type index.
        if (type_bits & (1 << i) &&
            (memory_properties.memoryTypes[i].propertyFlags & prop_flags) ==
                prop_flags)
        {
            return i;
        }
    }

    printf("Failed to find memory type index\n");
    return 0;
}
