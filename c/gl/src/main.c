#include <SDL.h>
#include <epoxy/gl.h>
#include <stdio.h>
#include <unistd.h>

#include "defs.h"

#define GL_MAJOR_VER_NEED 3
#define GL_MINOR_VER_NEED 3

#define APP_TITLE "OpenGL " STR(GL_MAJOR_VER_NEED) "." STR(GL_MINOR_VER_NEED)
#define INITIAL_WINDOW_WIDTH 320
#define INITIAL_WINDOW_HEIGHT 240

int main(int argc, char *argv[])
{
    SDL_Window *win = NULL;
    SDL_GLContext *GL_ctx = NULL;
    SDL_Event event;
    int GL_major_ver;
    int GL_minor_ver;
    int exit_code = EXIT_SUCCESS;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VER_NEED);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MAJOR_VER_NEED);

    win = SDL_CreateWindow(APP_TITLE, SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, INITIAL_WINDOW_WIDTH,
                           INITIAL_WINDOW_HEIGHT,
                           SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!win)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    GL_ctx = SDL_GL_CreateContext(win);
    if (!GL_ctx)
    {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &GL_major_ver))
    {
        printf("Failed to get OpenGL major version: %s\n", SDL_GetError());
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &GL_minor_ver))
    {
        printf("Failed to get OpenGL minor version: %s\n", SDL_GetError());
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (GL_major_ver != GL_MAJOR_VER_NEED || GL_minor_ver != GL_MINOR_VER_NEED)
    {
        printf(
            "OpenGL version doesn't match needed version: %d.%d, "
            "actual: %d.%d\n",
            GL_MAJOR_VER_NEED, GL_MINOR_VER_NEED, GL_major_ver, GL_minor_ver);
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }
    else
        printf("OpenGL version %d.%d\n", GL_major_ver, GL_minor_ver);

    // One means VSync
    SDL_GL_SetSwapInterval(1);

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

cleanup:
    if (GL_ctx)
    {
        SDL_GL_DeleteContext(GL_ctx);
        GL_ctx = NULL;
    }
    if (win)
    {
        SDL_DestroyWindow(win);
        win = NULL;
    }
    SDL_Quit();

    return exit_code;
}
