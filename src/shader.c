#include "shader.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <GL/glew.h>

GLuint load_shader(char *path, GLenum type)
{
	FILE *f = fopen(path, "rb");
	if (f == NULL) {
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);

	char *buffer = (char *) calloc(sizeof(char), size + 1);
	fread(buffer, size, 1, f);
	fclose(f);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar * const *) &buffer, NULL);
	glCompileShader(shader);

	return shader;
}

shader_program make_shader_program(char *fragdata)
{
	GLuint sp = glCreateProgram();
	glBindFragDataLocation(sp, 0, fragdata);
	return sp;
}

void attach_shader(shader_program sp, shader s)
{
	glAttachShader(sp, s);
}

void compile_shader_program(shader_program sp)
{
	glLinkProgram(sp);
}

void use_shader_program(shader_program sp)
{
	glUseProgram(sp);
}
