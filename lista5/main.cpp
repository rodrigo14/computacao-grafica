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
	Resize_Mesh(&mesh);

	int indexPointA, indexPointB, indexPointC, trash;
	for (int i=0; i<mesh.nface; i++) {
		fscanf(fp, "%d %d %d %d", &trash, &indexPointA, &indexPointB, &indexPointC);
		mesh.list_faces[i].v1 = indexPointA;
		mesh.list_faces[i].v2 = indexPointB;
		mesh.list_faces[i].v3 = indexPointC;
	}

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