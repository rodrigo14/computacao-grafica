#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

struct _point2 {
	int x;
	int y;
}point2;

void divide_triangle(point2 a, point2 b, point2 x, int k)
{
	if (k > 0)
	{
		point2 ab = (a+b)/2.0;
		point2 ac = (a+c)/2.0;
		point2 bc = (b+c)/2.0;

		divide_triangle(a, ab, ac, k-1);
		divide_triangle(c, ac, bc, k-1);
		divide_triangle(b, bc, ab, k-1);
	}
	else triangle(a,b,c);
}

int main ()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen = SDL_SetVideoMode(800,600,16,SDL_SWSURFACE);


	point2 a;
	a.x = 0;
	point2 a.y = 0;
	point2 b.x = 10;
	point2 b.y = 10;
	point2 c.x = 20;
	point2 c.y = 0;

	divide_triangle(a, b, c, 50);

	SDL_Delay(3000);
	SDL_Quit(); //Fecha SDL

}
