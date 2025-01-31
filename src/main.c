/*************************************************
 *File----------main.c
 *Project-------ChessEngine
 *Author--------Justin Kachele
 *Created-------Thursday Jan 16, 2025 09:18:51 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
}

int main(void) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(800, 600, "Chess Engine",
                        NULL, NULL);
        if (window == NULL) {
                fprintf(stderr, "Failed to create GLFW window\n");
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initalize GLAD\n");
                return -1;
        }

        unsigned int shader = compileShader("assets/shaders/vert.glsl",
                        "assets/shaders/frag.glsl");

        float vertices[] = {
                // Position             color
                -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
                 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {0, 1, 2};

        unsigned int vbo;
        unsigned int ebo;
        unsigned int vao;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                        vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                        indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                // Clear Window
                glClearColor(0.314f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // Rendering happens here
                glUseProgram(shader);

                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

                // Check and call events and swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteProgram(shader);

        glfwTerminate();
        return 0;
}

