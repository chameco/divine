#include "cube.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glew.h>

#include "linmath.h"
#include "texture.h"
#include "shader.h"

cube_type WORLD[20][20][20] = {{{0}}};

GLfloat CUBE_VERTICES[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

GLuint CUBE_VBO;
GLuint CUBE_TILESHEET;


mat4x4 MODEL;

void initialize_world(shader_program sp)
{
	glGenBuffers(1, &CUBE_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, CUBE_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

	CUBE_TILESHEET = load_texture("textures/tilesheet.png", GL_TEXTURE1);
}

void create_cube(cube_type t, int x, int y, int z)
{
	WORLD[x][y][z] = t;
}

cube_type get_cube(int x, int y, int z)
{
	return WORLD[x][y][z];
}

double radius_from_angle(double angle)
{
	/*double adjacent = 0.5;
	double a_over_h = cos(angle);
	if (fabs(a_over_h) <= 0.000000001) {
		return fabs(adjacent);
	}
	return fabs(adjacent / a_over_h);*/
	return 0.75;
}

bool collides_with_cylinder(double cx, double cy, double cz, double rad, double h, int x, int y, int z)
{
	/*if (z + 0.5 <= cz && z - 0.5 >= cz + h) {
		return false;
	}
	double xdiff = x - cx;
	double ydiff = y - cy;
	double angle = atan(ydiff/xdiff);
	double cube_rad = radius_from_angle(angle);
	double sum_rad = cube_rad + rad;
	double distance = sqrt(xdiff * xdiff + ydiff * ydiff);
	if (distance < sum_rad) {
		return true;
	}
	return false;*/

	if (fabs(cx - x) < 0.9) {
		if (fabs(cy - y) < 0.9) {
			if (fabs(cz - z) < 0.9) {
				return true;
			}
		}
	}
	return false;
}

void draw_cube(shader_program sp, cube_type t, int x, int y, int z)
{
	mat4x4_translate(MODEL, x, y, z);
	glUniformMatrix4fv(glGetUniformLocation(sp, "model"), 1, GL_FALSE, (GLfloat *) MODEL);

	glUniform1f(glGetUniformLocation(sp, "ax"), (t % 8)/8.0);
	glUniform1f(glGetUniformLocation(sp, "ay"), (t / 8)/8.0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void draw_world(shader_program sp)
{
	glBindTexture(GL_TEXTURE_2D, CUBE_TILESHEET);
	glUniform1i(glGetUniformLocation(sp, "tex"), 1);
	glUniform1f(glGetUniformLocation(sp, "numtiles"), 8.0);
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			for (int z = 0; z < 10; z++) {
				if (WORLD[x][y][z] != 0) {
					draw_cube(sp, WORLD[x][y][z], x, y, z);
				}
			}
		}
	}
}
