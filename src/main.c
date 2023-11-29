#include <SDL2/SDL.h>
#include <math.h>

#define FOV 60.0


void initialize(SDL_Window **window, SDL_Renderer **renderer);
void handleEvents(SDL_Event *event, SDL_Window **window);
void handleKeyPress(SDL_Keycode key);
void cleanup(SDL_Window *window);
void renderScene(SDL_Renderer *renderer, int map[10][10]);

int cameraAngle = 0;
float playerX = 5.0;
float playerY = 5.0;


void initialize(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_VIDEO);
	*window = SDL_CreateWindow(
			"Raycasting Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
			0);
	*renderer = SDL_CreateRenderer(
			*window,
			-1,
			SDL_RENDERER_ACCELERATED);
}

void handleEvents(SDL_Event *event, SDL_Window **window) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                cleanup(*window);
                break;
            case SDL_KEYDOWN:
                handleKeyPress(event->key.keysym.sym);
                break;
        }
    }
}

void handleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_LEFT:
            cameraAngle -= 5;
            break;
        case SDLK_RIGHT:
            cameraAngle += 5;
            break;
    }
}

void renderScene(SDL_Renderer *renderer, int map[10][10]) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < 800; x++) {
        float rayAngle = (cameraAngle - FOV / 2) + ((float)x / 800) * FOV;
        float rayX = playerX;
        float rayY = playerY;
        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);

        while (map[(int)rayX][(int)rayY] == 0) {
            rayX += rayDirX;
            rayY += rayDirY;
        }

        int wallHeight = (int)(600 / sqrt((rayX - playerX) * (rayX - playerX) + (rayY - playerY) * (rayY - playerY)));
        int wallColor = (map[(int)rayX][(int)rayY] == 1) ? 0 : 255;

        SDL_SetRenderDrawColor(renderer, wallColor, wallColor, wallColor, 255);
        SDL_RenderDrawLine(renderer, x, 300 - wallHeight / 2, x, 300 + wallHeight / 2);
    }
}

void cleanup(SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_Event event;

    initialize(&window, &renderer);

    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

	while (1) {
        handleEvents(&event, &window);

        renderScene(renderer, map);

        SDL_RenderPresent(renderer);
	}

    cleanup(window);

	return (0);
}
