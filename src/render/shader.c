/*************************************************
 *File----------shader.c
 *Project-------ChessEngine
 *Author--------Justin Kachele
 *Created-------Tuesday Jan 21, 2025 09:48:59 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include "shader.h"

static unsigned int compile(const char *path, GLenum type) {
        FILE *f;
        char *shaderSource;
        long len;

        f = fopen(path, "rb");
        if (f == NULL) {
                fprintf(stderr, "Error loading shader at %s\n", path);
                exit(1);
        }

        fseek(f, 0, SEEK_END);
        len = ftell(f);
        assert(len > 0);
        fseek(f, 0, SEEK_SET);
        shaderSource = calloc(1, len);
        assert(shaderSource != NULL);
        fread(shaderSource, 1, len, f);
        assert(strlen(shaderSource) > 0);
        fclose(f);

        unsigned int shaderHandle = glCreateShader(type);
        glShaderSource(shaderHandle, 1, (const GLchar**) &shaderSource,
                        (const GLint*)&len);
        glCompileShader(shaderHandle);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
                if (type == GL_VERTEX_SHADER)
                        printf("ERROR: SHADER VERTEX COMPILATION FAILED\n%s\n",
                                infoLog);
                if (type == GL_FRAGMENT_SHADER)
                        printf("ERROR: SHADER FRAGMENT COMPILATION FAILED\n"
                                        "%s\n", infoLog);
                else
                        printf("ERROR: SHADER COMPILATION FAILED\n%s\n",
                                infoLog);
        }

        free(shaderSource);
        return shaderHandle;
}

unsigned int compileShader(const char *vPath, const char *fPath) {

        unsigned int vertexShader = compile(vPath, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compile(fPath, GL_FRAGMENT_SHADER);

        unsigned int shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);

        int success;
        char infoLog[512];
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                printf("ERROR: SHADER LINKING FAILED\n%s\n",
                                infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shader;
}

