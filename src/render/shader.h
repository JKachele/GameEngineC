/*************************************************
 *File----------shader.h
 *Project-------ChessEngine
 *Author--------Justin Kachele
 *Created-------Tuesday Jan 21, 2025 09:49:10 EST
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int compileShader(const char *VertexFilePath,
                           const char *fragmentFilePath);

#endif

