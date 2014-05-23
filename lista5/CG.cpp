#include <SDL/SDL.h>
#include <GL/gl.h>
#include <stdlib.h>

#include "CG.h"

void processEvents() {
    SDL_Event event;
    float t = 0;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_QUIT) {
    		exit(0);
    	}

    	if (event.type == SDL_KEYDOWN) {
    		t += 0.1;
    	}

		if (event.key.keysym.sym == SDLK_t) {
			if (event.key.state == SDL_PRESSED) {
				drawType = TRIANGLES;
			}
		}

		if (event.key.keysym.sym == SDLK_l) {
			if (event.key.state == SDL_PRESSED) {
				drawType = LINES;
			}
		}

		if (event.key.keysym.sym == SDLK_SPACE) {
			if (event.key.state == SDL_PRESSED) {
				drawType = (drawType + 1)%2;
			}

		}
	}
}

int createScreen(int width, int height) {
	SDL_Surface *screen;
	
	float ratio = 1.0*width/height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erro na inicializacao da SDL: %s\n", SDL_GetError());
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(width,height,16,SDL_OPENGL);
	
	if (screen == 0)
	{
		fprintf(stderr, "Erro na inicializacao do vídeo: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	return 1;
}

void coordenadas() {
	glBegin(LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(-1.0,0);
		glVertex2f(1.0,0);
		glVertex2f(0,-1.0);
		glVertex2f(0,1.0);
	glEnd();
}
