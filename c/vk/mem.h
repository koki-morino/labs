#ifndef GPU_MEM_H
#define GPU_MEM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "desc.h"

int8_t GPU_mem(GPU_ctx *ctx, uint32_t size, VkBuffer *buffer,
               VkDeviceMemory *memory);

int8_t GPU_mem_to(GPU_ctx *ctx, VkDeviceMemory *dst, void *data, uint32_t size);

int8_t GPU_mem_from(GPU_ctx *ctx, VkDeviceMemory *src, void *data,
                    uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
