/**
 * Descriptor
 */

#ifndef GPU_DESC_H
#define GPU_DESC_H

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

int8_t GPU_desc(GPU_ctx *ctx, uint32_t input_size, uint32_t output_size);

#ifdef __cplusplus
}
#endif

#endif
