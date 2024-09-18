/**
 * Entry point
 */

#include <stdlib.h>

#include "cmd.h"
#include "ctx.h"
#include "desc.h"
#include "ldev.h"
#include "mem.h"
#include "pdev.h"
#include "ppl.h"

int main(void)
{
    GPU_ctx ctx;
    if (GPU_ctx_init(&ctx) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    if (GPU_pdev(&ctx) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    if (GPU_ldev(&ctx) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    if (GPU_pipeline(&ctx) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    uint32_t input_data[1000];
    float output_data[1000];

    if (GPU_desc(&ctx, sizeof(input_data), sizeof(output_data)) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    for (uint32_t i = 0; i < 1000; i++)
    {
        input_data[i] = i;
        output_data[i] = 0;
    }

    if (GPU_mem_to(&ctx, &ctx.input_memory, input_data, sizeof(input_data)) !=
        EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    if (GPU_cmd(&ctx) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    if (GPU_mem_from(&ctx, &ctx.output_memory, output_data,
                     sizeof(output_data)) != EXIT_SUCCESS)
    {
        GPU_ctx_destroy(&ctx);
        return EXIT_FAILURE;
    };

    for (uint32_t i = 0; i < 1000; i += 50)
    {
        printf("%3u -> %6.0f\n", input_data[i], output_data[i]);
    }

    GPU_ctx_destroy(&ctx);

    return EXIT_SUCCESS;
}
