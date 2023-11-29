#include <SDL2/SDL.h>

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_Event event;

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

	while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < 800; x++) {
            for (int y = 0; y < 10; y++) {
                int wallHeight = 100;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderDrawLine(renderer, x, 300 - wallHeight / 2, x, 300 + wallHeight / 2);
            }
        }
        SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}
