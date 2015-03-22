#include "render.h"

#include <stdlib.h>
#include <stddef.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "init.h"
#include "shader.h"

vao make_vao(int num_values)
{
	vao ret;
	ret.num_values = num_values;
	glGenVertexArrays(1, &ret.buf);
	return ret;
}

void activate_vao(vao v)
{
	glBindVertexArray(v.buf);
}

render_context make_render_context(window w, shader_program sp, int num_values)
{
	render_context ret;
	ret.w = w;
	ret.sp = sp;

	glGenFramebuffers(1, &(ret.fb));
	glBindFramebuffer(GL_FRAMEBUFFER, ret.fb);
	GLuint color_buffer;
	glGenTextures(1, &color_buffer);
	glBindTexture(GL_TEXTURE_2D, color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer, 0);
	GLuint render_buffer;
	glGenRenderbuffers(1, &render_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer);

	ret.v = make_vao(num_values);
	return ret;
}

void set_attribute(render_context r, char *name, int size, int offset)
{
	GLint attrib = glGetAttribLocation(r.sp, name);
	glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, r.v.num_values * sizeof(float), (void *) (offset * sizeof(float)));
	glEnableVertexAttribArray(attrib);
}

void set_matrix(render_context r, char *name, mat4x4 m)
{
	glUniformMatrix4fv(glGetUniformLocation(r.sp, name), 1, GL_FALSE, (GLfloat *) m);
}

void activate_render_context(render_context r)
{
	activate_vao(r.v);
	glBindFramebuffer(GL_FRAMEBUFFER, r.fb);
	glEnable(GL_DEPTH_TEST);
}

void blit_render_context(render_context r)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlitFramebuffer(0, 0, 800, 600, 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
