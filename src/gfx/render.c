/*************************************************
 *File----------render.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:06:45 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "render.h"


void renderInit(struct Renderer *self) {
        *self = (struct Renderer) {0};

        shaderInit(&self->shader);

        float vertices[] = {
                // Position             color
                -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
                 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {0, 1, 2};

        glGenBuffers(1, &self->vbo);
        glGenBuffers(1, &self->ebo);
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                        vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                        indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
}

void renderUpdate(struct Renderer *self) {
        shaderUpdate(&self->shader);

        glBindVertexArray(self->vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void renderDestroy(struct Renderer *self) {
        shaderDestroy(&self->shader);

        glDeleteVertexArrays(1, &self->vao);
        glDeleteBuffers(1, &self->vbo);
        glDeleteBuffers(1, &self->ebo);
}

