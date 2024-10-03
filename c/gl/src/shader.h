#ifndef SHADER_H
#define SHADER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <epoxy/gl.h>

/**
 * Assign 0 to shader on failure.
 */
void create_shader(GLenum type, const char *path, GLuint *shader);

#ifdef __cplusplus
}
#endif

#endif
