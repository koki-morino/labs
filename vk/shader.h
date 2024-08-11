#ifndef GPU_SHADER_H
#define GPU_SHADER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"

int8_t GPU_shader_module(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
