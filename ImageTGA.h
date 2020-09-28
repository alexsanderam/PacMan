/*
 * ImageTCA.h
 *
 *  Created on: Jul 30, 2010
 *      Author: marcelozamith
 */

#ifndef IMAGETCA_H_
#define IMAGETCA_H_
#include <GL/glew.h>
#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

typedef	struct										// Create A Structure
{
	GLubyte	*imageData;								// Image Data (Up To 32 Bits)
	GLuint	bpp;									// Image Color Depth In Bits Per Pixel
	GLuint	width;									// Image Width
	GLuint	height;									// Image Height
	GLuint	texID;									// Texture ID Used To Select A Texture
} TextureImage;										// Structure Name


bool LoadTGA(TextureImage *texture, const char *filename)	;

#endif /* IMAGETCA_H_ */
