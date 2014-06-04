/*
Desenho de um triângulo na tela usando shaders

*/
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include "InitShader.h"

SDL_Window* displayWindow;

GLuint VBO;


struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f()
    {
    }

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
	SDL_GL_SwapWindow(displayWindow);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

//----------------------------------------------------------------------------
void Display_InitGL()
{
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );					   
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
    
 }

 
 /* Laço principal */
int main(int argc, char *argv[])
{

		
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer* displayRenderer;

	int flags = SDL_WINDOW_OPENGL;

	atexit(SDL_Quit);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	

	SDL_CreateWindowAndRenderer(800, 600, flags,&displayWindow, &displayRenderer);
	SDL_GL_CreateContext(displayWindow);
    glViewport( 0, 0, 800, 600 );

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		exit(1);
	}
	printf("Versao OpenGL: %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	CreateVertexBuffer();
    Display_InitGL();

	while (1){
		RenderSceneCB();
		SDL_Delay(50);
	}
    
	
    return 0;
}