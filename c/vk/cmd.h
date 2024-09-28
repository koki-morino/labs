/**
 * Command
 */

#ifndef GPU_CMD_H
#define GPU_CMD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "ctx.h"
#include "fence.h"

int8_t GPU_cmd(GPU_ctx *ctx);

#ifdef __cplusplus
}
#endif

#endif
