#include <epoxy/gl.h>

int8_t create_shader(GLenum type, char *path, GLuint *shader)
{
    GLint GLresult;

    *shader = glCreateShader(type);

cleanup:
}
