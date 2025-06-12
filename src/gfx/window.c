/*************************************************
 *File----------window.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 10:59:12 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "window.h"

// Global Window
struct Window window;

static void _sizeCallback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
}

static void _processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
}

void createWindow(WinFunc init, WinFunc render, WinFunc destroy) {
        window.init = init;
        window.render = render;
        window.destroy = destroy;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window.size = (ivec2s){{800, 600}};
        window.handle = glfwCreateWindow(window.size.x, window.size.y,
                        "Chess Engine", NULL, NULL);
        if (window.handle == NULL) {
                fprintf(stderr, "Failed to create GLFW window\n");
                glfwTerminate();
                exit(0);
        }
        glfwMakeContextCurrent(window.handle);
        glfwSetFramebufferSizeCallback(window.handle, _sizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initalize GLAD\n");
                exit(0);
        }
}

void windowLoop(void) {
        window.init();

        while (!glfwWindowShouldClose(window.handle)) {
                _processInput(window.handle);

                // Clear Window
                glClearColor(0.314f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // Rendering happens here
                window.render();

                // Check and call events and swap buffers
                glfwSwapBuffers(window.handle);
                glfwPollEvents();
        }

        window.destroy();

        glfwTerminate();
        exit(0);
}

