#include <epoxy/gl.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

void create_shader(GLenum type, const char *path, GLuint *shader)
{
    FILE *f = NULL;
    size_t size;
    size_t read_size;
    char *source = NULL;
    const GLchar *sources[1];
    GLint is_compiled = GL_FALSE;
    int8_t failure = FALSE;

    f = fopen(path, "rb");
    if (!f)
    {
        printf("Failed to open shader file (%d)\n", errno);
        failure = TRUE;
        goto cleanup;
    }

    if (fseek(f, 0, SEEK_END) != 0)
    {
        printf("Failed to seek to the end of shader file (%d)\n", errno);
        failure = TRUE;
        goto cleanup;
    }

    if ((size = ftell(f)) == -1L)
    {
        printf("Failed to get the end position in shader file (%d)\n", errno);
        failure = TRUE;
        goto cleanup;
    }

    if (fseek(f, 0, SEEK_SET) != 0)
    {
        printf("Failed to seek to the beginning of shader file (%d)\n", errno);
        failure = TRUE;
        goto cleanup;
    }

    // File size in byte + NULL terminator
    if ((source = malloc(size + 1)) == NULL)
    {
        printf("Failed to allocate memory to read shader file.\n");
        failure = TRUE;
        goto cleanup;
    }

    read_size = fread(source, sizeof(char), size, f);
    if (read_size < size)
    {
        printf("Failed to read shader file.\n");
        failure = TRUE;
        goto cleanup;
    }

    // Check if size fits into int.
    if (size > INT_MAX)
    {
        printf("Shader file is too big.\n");
        failure = TRUE;
        goto cleanup;
    }

    *shader = glCreateShader(type);
    if (*shader == 0)
    {
        printf("Failed to create shader.\n");
        failure = TRUE;
        goto cleanup;
    }

    sources[0] = source;
    glShaderSource(*shader, 1, sources, (int *)&size);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        char *error_log = NULL;

        // glGetShaderiv() gives log length including NULL terminator.
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &max_length);
        if ((error_log = malloc(size)) == NULL)
            printf(
                "Failed to allocate memory for shader compilation error "
                "log.\n");
        else
        {
            glGetShaderInfoLog(*shader, max_length, &max_length, error_log);
            printf("Failed to compile shader source: %s\n", error_log);
            free(error_log);
        }

        failure = TRUE;
        goto cleanup;
    }

    failure = TRUE;

cleanup:
    if (source)
        free(source);

    if (f)
        fclose(f);

    if (failure && shader)
        glDeleteShader(*shader);

    if (failure)
        *shader = 0;

    return;
}
