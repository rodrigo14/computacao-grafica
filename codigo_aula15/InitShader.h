#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>


#ifndef _INIT_SHADER
#define _INIT_SHADER

GLuint  InitShader(const char* vShaderFile, const char* fShaderFile);

#endif