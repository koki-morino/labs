#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    cl_int cl_result = CL_SUCCESS;
    cl_uint num_platforms;

    cl_result = clGetPlatformIDs(0, NULL, &num_platforms);
    if (cl_result != CL_SUCCESS)
    {
        printf("Failed to get platform ID(s)\n");
        return EXIT_FAILURE;
    }

    printf("Platform(s) found %u\n", num_platforms);

    return EXIT_SUCCESS;
}
