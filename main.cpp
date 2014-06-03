#include <GL/glut.h>	
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>

#include "CG.cpp"
#include "vec.h"

int main(int argc, char *argv[]) {
	Mesh mesh = New_Mesh();
	Load_Mesh(&mesh, fp);

	/*
	ShaderManager shader;
	shader.setVertexShader("vshader21.glsl");
	shader.setFragmentShader("fshader21.glsl");
	*/
	
	Calculate_NormalVector(&mesh);
	
	if (!createScreen(width, height)) {
		return -1;
	}

	while (1) {
		processEvents();
		Render_Mesh(mesh);
		SDL_GL_SwapBuffers();
	}


	return 0;
}