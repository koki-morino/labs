#ifndef SHADER_H
#define SHADER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <GLES2/gl2.h>

/**
 * Assign 0 to shader on failure.
 */
void shader_create(GLenum type, const char *path, GLuint *shader);

#ifdef __cplusplus
}
#endif

#endif
