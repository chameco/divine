#include "player.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "cube.h"
#include "linmath.h"
#include "render.h"

#define PI 3.141592654

double PLAYER_X = 5.0;
double PLAYER_Y = 5.0;
double PLAYER_Z = 5.0;
double PLAYER_FACING = 0;
double PLAYER_SPEED = 0.02;
double PLAYER_TURNRATE = 0.004;
bool PLAYER_ONFLOOR = false;
bool PLAYER_JUMPING = false;
double PLAYER_UPWARD_VELOCITY = 0.0;
double PLAYER_GRAVITY = -0.0003;

mat4x4 VIEW;
vec3 EYE = {5.0, 5.0, 5.0};
vec3 CENTER = {5.0, 0.0, 5.0};
vec3 UP = {0.0, 0.0, 1.0};

void initialize_player(render_context rc)
{
	mat4x4_look_at(VIEW, EYE, CENTER, UP);
	set_matrix(rc, "view", VIEW);
} 

int max(int x, int y)
{
	return x > y ? x : y;
}

int sign(double x)
{
	return x / fabs(x);
}

bool collisions_near_player(double tempx, double tempy, double tempz, vec3 *coords)
{
	for (int x = max((int) PLAYER_X - 3, 0); x < (int) PLAYER_X + 3; x++) {
		for (int y = max((int) PLAYER_Y - 3, 0); y < (int) PLAYER_Y + 3; y++) {
			for (int z = max((int) PLAYER_Z - 3, 0); z < (int) PLAYER_Z + 3; z++) {
				if (get_cube(x, y, z) && collides_with_cylinder(tempx, tempy, PLAYER_Z, 0.5, 2.0, x, y, z)) {
					if (coords != NULL) {
						(*coords)[0] = x;
						(*coords)[1] = y;
						(*coords)[2] = z;
					}
					return true;
				}
			}
		}
	}
	return false;
}

void move_player_forward()
{
	double tempx;
	double tempy;
	tempx = PLAYER_X - PLAYER_SPEED * cos(PI/2 - PLAYER_FACING);
	tempy = PLAYER_Y - PLAYER_SPEED * sin(PI/2 - PLAYER_FACING);
	if (!collisions_near_player(tempx, tempy, PLAYER_Z, NULL)) {
		PLAYER_X = tempx;
		PLAYER_Y = tempy;
	}
}

void move_player_backward()
{
	double tempx;
	double tempy;
	tempx = PLAYER_X + PLAYER_SPEED * cos(PI/2 - PLAYER_FACING);
	tempy = PLAYER_Y + PLAYER_SPEED * sin(PI/2 - PLAYER_FACING);
	if (!collisions_near_player(tempx, tempy, PLAYER_Z, NULL)) {
		PLAYER_X = tempx;
		PLAYER_Y = tempy;
	}
}

void move_player_left()
{
	double tempx;
	double tempy;
	tempx = PLAYER_X + PLAYER_SPEED * cos(-PLAYER_FACING);
	tempy = PLAYER_Y + PLAYER_SPEED * sin(-PLAYER_FACING);
	if (!collisions_near_player(tempx, tempy, PLAYER_Z, NULL)) {
		PLAYER_X = tempx;
		PLAYER_Y = tempy;
	}
}

void move_player_right()
{
	double tempx;
	double tempy;
	tempx = PLAYER_X - PLAYER_SPEED * cos(-PLAYER_FACING);
	tempy = PLAYER_Y - PLAYER_SPEED * sin(-PLAYER_FACING);
	if (!collisions_near_player(tempx, tempy, PLAYER_Z, NULL)) {
		PLAYER_X = tempx;
		PLAYER_Y = tempy;
	}
}

void move_player_up()
{
	if (PLAYER_ONFLOOR) {
		double tempz = PLAYER_Z + PLAYER_SPEED;
		vec3 coords;
		if (!collisions_near_player(PLAYER_X, PLAYER_Y, tempz, &coords)) {
			PLAYER_Z = tempz;
			PLAYER_ONFLOOR = false;
			PLAYER_JUMPING = true;
			PLAYER_UPWARD_VELOCITY = 0.05;
		} else {
			PLAYER_Z = coords[2] - 0.9;
		}
	}
}

/*void move_player_down()
{
	if (!PLAYER_ONFLOOR) {
		double tempz = PLAYER_Z - PLAYER_SPEED;
		vec3 coords;
		if (!collisions_near_player(PLAYER_X, PLAYER_Y, tempz, &coords)) {
			PLAYER_Z = tempz;
		} else {
			PLAYER_Z = coords[2] + 0.9;
			PLAYER_ONFLOOR = true;
		}
	}
}*/

void spin_player_left()
{
	PLAYER_FACING = fmod(PLAYER_FACING - PLAYER_TURNRATE, 2 * PI);
}

void spin_player_right()
{
	PLAYER_FACING = fmod(PLAYER_FACING + PLAYER_TURNRATE, 2 * PI);
}

void update_player_camera(render_context rc)
{
	if (!PLAYER_ONFLOOR) {
		PLAYER_UPWARD_VELOCITY += PLAYER_GRAVITY;
		double tempz = PLAYER_Z + PLAYER_UPWARD_VELOCITY;
		vec3 coords;
		if (!collisions_near_player(PLAYER_X, PLAYER_Y, tempz, &coords)) {
			PLAYER_Z = tempz;
		} else {
			if (PLAYER_UPWARD_VELOCITY > 0) {
				PLAYER_Z = coords[2] - 1;
				PLAYER_ONFLOOR = false;
			} else {
				PLAYER_Z = coords[2] + 0.9;
				PLAYER_ONFLOOR = true;
			}
			PLAYER_UPWARD_VELOCITY = 0.0;
		}
	} else {
		if (!collisions_near_player(PLAYER_X, PLAYER_Y, PLAYER_Z - 0.5, NULL)) {
			PLAYER_ONFLOOR = false;
		}
	}

	EYE[0] = PLAYER_X;
	EYE[1] = PLAYER_Y;

	CENTER[0] = EYE[0] - 10 * cos(PI/2 - PLAYER_FACING);
	CENTER[1] = EYE[1] - 10 * sin(PI/2 - PLAYER_FACING);
	CENTER[2] = EYE[2] = PLAYER_Z + 0.2;
	mat4x4_look_at(VIEW, EYE, CENTER, UP);
	set_matrix(rc, "view", VIEW);
}
