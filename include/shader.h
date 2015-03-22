#pragma once

#include <GL/glew.h>

typedef GLuint shader_program;
typedef GLuint shader;

shader load_shader(char *path, GLenum type);
shader_program make_shader_program(char *fragdata);
void attach_shader(shader_program sp, shader s);
void compile_shader_program(shader_program sp);
void use_shader_program(shader_program sp);
