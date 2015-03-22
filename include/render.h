#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "init.h"
#include "shader.h"

typedef struct vao {
	int num_values;
	GLuint buf;
} vao;

typedef struct render_context {
	window w;
	shader_program sp;
	GLuint fb;
	vao v;
} render_context;

vao make_vao(int num_values);
void activate_vao(vao v);
render_context make_render_context(window w, shader_program sp, int num_values);
void set_attribute(render_context r, char *name, int size, int offset);
void set_matrix(render_context r, char *name, mat4x4 m);
void activate_render_context(render_context r);

void blit_render_context(render_context r);
