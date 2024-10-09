#include <GLES2/gl2.h>
#include <SDL.h>
#include <stdio.h>
#include <unistd.h>

#include "defs.h"
#include "font.h"
#include "shader.h"

#define GL_VARIANT "OpenGL ES"
#define GL_MAJOR_VER_NEED 2
#define GL_MINOR_VER_NEED 0

#define APP_TITLE GL_VARIANT STR(GL_MAJOR_VER_NEED) "." STR(GL_MINOR_VER_NEED)
#define INITIAL_WINDOW_WIDTH 320
#define INITIAL_WINDOW_HEIGHT 240

int main(int argc, char *argv[])
{
    SDL_Window *win = NULL;
    SDL_GLContext *GL_ctx = NULL;
    SDL_Event event;
    int GL_major_ver;
    int GL_minor_ver;
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;
    char *font_path = NULL;
    int exit_code = EXIT_FAILURE;

    font_get_path(&font_path);
    if (!font_path)
    {
        printf("Failed to get font path\n");
        goto cleanup;
    }

    printf("Font: %s\n", font_path);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VER_NEED);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VER_NEED);

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");

    win = SDL_CreateWindow(APP_TITLE, SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, INITIAL_WINDOW_WIDTH,
                           INITIAL_WINDOW_HEIGHT,
                           SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!win)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        goto cleanup;
    }

    GL_ctx = SDL_GL_CreateContext(win);
    if (!GL_ctx)
    {
        printf("Failed to create " GL_VARIANT " context: %s\n", SDL_GetError());
        goto cleanup;
    }

    if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &GL_major_ver))
    {
        printf("Failed to get OpenGL major version: %s\n", SDL_GetError());
        goto cleanup;
    }

    if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &GL_minor_ver))
    {
        printf("Failed to get " GL_VARIANT " minor version: %s\n",
               SDL_GetError());
        goto cleanup;
    }

    if (GL_major_ver != GL_MAJOR_VER_NEED || GL_minor_ver != GL_MINOR_VER_NEED)
    {
        printf(GL_VARIANT
               " version doesn't match needed version: %d.%d, "
               "actual: %d.%d\n",
               GL_MAJOR_VER_NEED, GL_MINOR_VER_NEED, GL_major_ver,
               GL_minor_ver);
        goto cleanup;
    }

    printf(GL_VARIANT " version: %d.%d\n", GL_major_ver, GL_minor_ver);

    // One means VSync
    SDL_GL_SetSwapInterval(1);

    shader_create(GL_VERTEX_SHADER, "", &vertex_shader);
    if (vertex_shader == 0)
    {
        printf("Failed to create vertex shader\n");
        goto cleanup;
    }

    shader_create(GL_FRAGMENT_SHADER, "", &fragment_shader);
    if (fragment_shader == 0)
    {
        printf("Failed to create fragment shader\n");
        goto cleanup;
    }

    while (TRUE)
    {
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(win);

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }
    }

    exit_code = EXIT_SUCCESS;

cleanup:
    if (vertex_shader != 0)
        glDeleteShader(vertex_shader);

    if (fragment_shader != 0)
        glDeleteShader(fragment_shader);

    if (GL_ctx)
        SDL_GL_DeleteContext(GL_ctx);

    if (win)
        SDL_DestroyWindow(win);

    SDL_Quit();

    if (font_path)
        free(font_path);

    return exit_code;
}
