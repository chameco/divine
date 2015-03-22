#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow *window;
GLFWwindow *initialize_window();
void finalize_window();
