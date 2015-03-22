#pragma once

#include <stdbool.h>

#include "shader.h"

typedef enum cube_type {
	CUBE_TYPE_VOID=0,
	CUBE_TYPE_STONEFLOOR,
	CUBE_TYPE_PLANKS,
	CUBE_TYPE_GRASS,
	CUBE_TYPE_SNOW,
	CUBE_TYPE_SAND,
	CUBE_TYPE_CARPET,
	CUBE_TYPE_WATER,
	CUBE_TYPE_STONE=8,
	CUBE_TYPE_STONETOP,
	CUBE_TYPE_STONETORCH,
	CUBE_TYPE_SHRUB=16
} cube_type;

void initialize_world();
void create_cube(cube_type t, int x, int y, int z);
cube_type get_cube(int x, int y, int z);
double radius_from_angle(double angle);
bool collides_with_cylinder(double cx, double cy, double cz, double rad, double h, int x, int y, int z);
void draw_cube(shader_program sp, cube_type t, int x, int y, int z);
void draw_world(shader_program sp);
