#pragma once

#include "render.h"

void initialize_player(render_context rc);
void move_player_forward();
void move_player_backward();
void move_player_left();
void move_player_right();
void move_player_up();
//void move_player_down();
void spin_player_left();
void spin_player_right();
void update_player_camera(render_context rc);
