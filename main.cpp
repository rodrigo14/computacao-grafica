#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>	
#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "CG.cpp"
#include "mesh.cpp"
// #include "Shader.cpp"
// #include "vec.h"

using namespace std;

int main(int argc, char *argv[]) {

	Mesh mesh = New_Mesh();
	Load_Mesh(&mesh, fp);

	Calculate_NormalVector(&mesh);
	
	if (!createScreen(width, height)) {
		return -1;
	}

	while (1) {
		processEvents();
		Render_Mesh(mesh);
		SDL_GL_SwapBuffers();
	}
	/*
	*/
	
	// glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	// glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// glewInit();

	// Mesh mesh = New_Mesh();
	// Load_Mesh(&mesh, fp);

	// ShaderManager shader;
	// shader.setVertexShader("vshader21.glsl");
	// shader.setFragmentShader("fshader21.glsl");
	// shader.setVertex(mesh.list_vertex);
	// shader.setIndice(mesh.list_faces);

	// GLuinit program = shader.initShader();
	// cout << "OK" << endl;
	// glUseProgram(program);
	// glClearColor(1,1,1,1);

	// shader.criarVertexArray();
	// shader.criarBufferDeVertex();
	// shader.criarBufferDeIndex();
	// shader.renderizarCena();

	// SDL_Window* janela;
	// SDL_GL_SwapWindow(janela);
	// if (!createScreen(width, height)) {
	// 	return -1;
	// }
	// SDL_Delay(2000);
	// SDL_Quit();

	return 0;
}