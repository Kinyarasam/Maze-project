#include <SDL2/SDL.h>

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
			"Raycasting Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
			0);
	renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED);

	int map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	while (1) {
		/**/
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}
