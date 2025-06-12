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

        // // Triangle
        // float vertices[] = {
        //         // Position             color
        //         -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        //          0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        //          0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
        // };

        // Rectangle
        float vertices[] = {
                // Position           // color            // Texture
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
        };

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
                        8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        shaderInit(&self->shader);
        textureInit(&self->texture);

        glUniform1i(glGetUniformLocation(self->shader.handle, "Tex0"), 0);
        glUniform1i(glGetUniformLocation(self->shader.handle, "Tex1"), 1);
}

void renderUpdate(struct Renderer *self) {
        shaderUse(&self->shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self->texture.handle0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, self->texture.handle1);

        mat4s trans = mat4_identity();
        trans = glms_translate(trans, (vec3s){{0.5f, -0.5f, 0.0f}});
        trans = glms_rotate(trans, (float)glfwGetTime(), (vec3s){{0.0, 0.0, 1.0}});

        GLuint transformLoc = glGetUniformLocation(self->shader.handle, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (const GLfloat*)&trans.raw);

        glBindVertexArray(self->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderDestroy(struct Renderer *self) {
        shaderDestroy(&self->shader);

        glDeleteVertexArrays(1, &self->vao);
        glDeleteBuffers(1, &self->vbo);
        glDeleteBuffers(1, &self->ebo);
}

