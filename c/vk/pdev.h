
/**
 * Physical device
 */

#ifndef GPU_PDEV_H
#define GPU_PDEV_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"

/**
 * Create Vulkan instance and physical device.
 */
int8_t GPU_pdev(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
