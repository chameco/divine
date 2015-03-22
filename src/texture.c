#include "texture.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

GLuint load_texture(char *path, GLenum slot)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, tex);

	//int width, height;
	//unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	
	tex = SOIL_load_OGL_texture(path, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//SOIL_free_image_data(image);

	return tex;
}
