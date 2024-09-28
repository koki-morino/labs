/**
 * Pipeline
 */

#ifndef GPU_PPL_H
#define GPU_PPL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"
#include "shader.h"

int8_t GPU_pipeline(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
