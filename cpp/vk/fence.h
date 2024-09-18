/**
 * Fence
 */

#ifndef GPU_FENCE_H
#define GPU_FENCE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"

int8_t GPU_fence(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
