#include <epoxy/gl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

int8_t create_shader(GLenum type, char *path, GLuint *shader)
{
    FILE *f = NULL;
    size_t size;
    size_t read_size;
    char *content = NULL;
    GLint GLresult;
    int8_t result = FALSE;

    f = fopen(path, "rb");
    if (!f)
    {
        printf("Failed to open shader file: %d\n", errno);
        goto cleanup;
    }

    if (fseek(f, 0, SEEK_END) != 0)
    {
        printf("Failed to seek to the end of shader file: %d\n", errno);
        goto cleanup;
    }

    if ((size = ftell(f)) == -1L)
    {
        printf("Failed to get the end position in shader file: %d\n", errno);
        goto cleanup;
    }

    if (fseek(f, 0, SEEK_SET) != 0)
    {
        printf("Failed to seek to the beginning of shader file: %d\n", errno);
        goto cleanup;
    }

    if ((content = malloc(size)) == NULL)
    {
        printf("Failed to allocate memory to read shader file\n");
        goto cleanup;
    }

    read_size = fread(content, sizeof(char), size, f);
    if (read_size < size)
    {
        printf("Failed to read shader file\n");
        goto cleanup;
    }

    printf("%s\n", content);

    *shader = NULL;
    *shader = glCreateShader(type);

cleanup:
    if (content)
    {
        free(content);
    }

    if (f)
    {
        fclose(f);
    }

    return result;
}
