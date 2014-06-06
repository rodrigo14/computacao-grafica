#ifndef VEC_H
#define VEC_H

#include <GL/glut.h>	
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <GL/glew.h>

typedef struct _point3D {
        float x, y, z;
} point3D;

typedef struct _Shader {
	const char *filename;
	GLenum type;
	Glchar *source;
	GLuinit a;

	Shader(){}

	Shader(const char *_filename, GLenum _type, Glchar *_source) {
		filename = _filename;
		type = _type;
		source = _source;
	}
	
} Shader;
/*
*/

#endif

