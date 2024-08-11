/**
 * Logical device
 */

#ifndef GPU_LDEV_H
#define GPU_LDEV_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"
#include "mem.h"

/**
 * Create logical device and get queue.
 */
int8_t GPU_ldev(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
