#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "init.h"
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "player.h"
#include "render.h"

#define PI 3.141592654

int main()
{

	window window = initialize_window();
	initialize_world();

	shader vertex_shader = load_shader("shaders/vert", GL_VERTEX_SHADER);
	shader fragment_shader = load_shader("shaders/frag", GL_FRAGMENT_SHADER);

	shader_program sp = make_shader_program("our_color");
	attach_shader(sp, vertex_shader);
	attach_shader(sp, fragment_shader);
	compile_shader_program(sp);
	use_shader_program(sp);

	render_context rc = make_render_context(window, sp, 8);
	activate_render_context(rc);

	set_attribute(rc, "position", 3, 0);
	set_attribute(rc, "color", 3, 3);
	set_attribute(rc, "tex_coord", 2, 6);

	initialize_player(rc);

	mat4x4 model, proj, r;
	mat4x4_identity(r);
	mat4x4_rotate(model, r, 0.0, 0.0, 1.0, 3.1415926);
	mat4x4_perspective(proj, PI/3, PI/2, 0.1, 20.0);

	set_matrix(rc, "proj", proj);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 1; z++) {
				create_cube(CUBE_TYPE_WATER, x, y, z);
			}
		}
	}

	/*for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			for (int z = 0; z < 10; z++) {
				if (x == 0 || x == 9 || y == 0 || y == 9 || z == 0 || z == 4 ) {
					create_cube(CUBE_TYPE_STONEFLOOR, x, y, z);
				} else {
					create_cube(CUBE_TYPE_VOID, x, y, z);
				}
			}
		}
	}*/

	create_cube(CUBE_TYPE_VOID, 4, 4, 4);
	create_cube(CUBE_TYPE_VOID, 4, 5, 4);
	create_cube(CUBE_TYPE_VOID, 5, 4, 4);
	create_cube(CUBE_TYPE_VOID, 5, 5, 4);
	create_cube(CUBE_TYPE_SHRUB, 1, 8, 6);

	while(!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_A)) {
			move_player_left();
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			move_player_right();
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			move_player_forward();
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			move_player_backward();
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			move_player_up();
		}
		/*if (glfwGetKey(window, GLFW_KEY_X)) {
			move_player_down();
		}*/
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			spin_player_left();
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			spin_player_right();
		}

		activate_render_context(rc);
		update_player_camera(rc);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_world(sp);

		blit_render_context(rc);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	finalize_window();
}
