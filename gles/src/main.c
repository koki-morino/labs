#include <GLES2/gl2.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "font.h"

static void quit(int status)
{
    glfwTerminate();
    exit(status);
}

static void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static void printGLInfo()
{
    GLFWwindow* window = glfwGetCurrentContext();
    if (!window)
    {
        printf("Failed to get GL context\n");
        quit(EXIT_FAILURE);
    }

    const GLubyte* vendor = glGetString(GL_VENDOR);
    printf("GL Vendor: %s\n", vendor);

    const GLubyte* renderer = glGetString(GL_RENDERER);
    printf("GL Renderer: %s\n", renderer);

    const GLubyte* version = glGetString(GL_VERSION);
    printf("GL Version: %s\n", version);
}

int main()
{
    font_list();

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        quit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(errorCallback);

    // Graphics backend hint.
    // glfwInitHint(GLFW_ANGLE_PLATFORM_TYPE, GLFW_ANGLE_PLATFORM_TYPE_D3D11);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLES 2.0", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create window\n");
        quit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    printGLInfo();

    glfwSwapInterval(1);

    GLfloat r = 0;
    GLfloat d = 0.01;

    // Windows blocks main thread while resizing window.
    // Maybe rendering in another thread can change the behavior.
    while (!glfwWindowShouldClose(window))
    {
        if (r > 1)
        {
            d = -0.01;
        }
        if (r < 0)
        {
            d = 0.01;
        }
        r += d;

        glClearColor(r, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
