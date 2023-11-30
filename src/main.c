#include <SDL2/SDL.h>
#include <math.h>

#define FOV 30.0
#define MOVE_SPEED 0.1

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


void initialize(SDL_Window **window, SDL_Renderer **renderer);
void handleEvents(SDL_Event *event, SDL_Window **window, int map[10][10]);
void handleKeyPress(SDL_Keycode key, int map[10][10]);
void cleanup(SDL_Window *window);
void renderScene(SDL_Renderer *renderer, int map[10][10]);
int checkCollision(float x, float y, int map[10][10]);

int cameraAngle = 0;
float playerX = 5.0;
float playerY = 5.0;
int renderMap = 1;


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

void handleEvents(SDL_Event *event, SDL_Window **window, int map[10][10]) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                cleanup(*window);
                break;
            case SDL_KEYDOWN:
                handleKeyPress(event->key.keysym.sym, map);
                break;
        }
    }
}

void handleKeyPress(SDL_Keycode key, int map[10][10]) {
    switch (key) {
        case SDLK_LEFT:
            cameraAngle -= 5;
            break;
        case SDLK_RIGHT:
            cameraAngle += 5;
            break;
        case SDLK_w:
            /**
             * Move Forward.
             */
            if (!checkCollision(playerX + cos(cameraAngle) * MOVE_SPEED, playerY + sin(cameraAngle) * MOVE_SPEED, map)) {
                playerX += cos(cameraAngle) * MOVE_SPEED;
                playerY += sin(cameraAngle) * MOVE_SPEED;
            }
            break;
        case SDLK_s:
            /**
             * Move Backward.
             */
            if (!checkCollision(playerX - cos(cameraAngle) * MOVE_SPEED, playerY - sin(cameraAngle) * MOVE_SPEED, map)) {
                playerX -= cos(cameraAngle) * MOVE_SPEED;
                playerY -= sin(cameraAngle) * MOVE_SPEED;
            }
            break;
        case SDLK_a:
            /**
             * Steer Left
             */
            if (!checkCollision(playerX + cos(cameraAngle + M_PI / 2) * MOVE_SPEED, playerY + sin(cameraAngle + M_PI / 2) * MOVE_SPEED, map)) {
                playerX += cos(cameraAngle + M_PI / 2) * MOVE_SPEED;
                playerY += sin(cameraAngle + M_PI / 2) * MOVE_SPEED;
            }
            break;
        case SDLK_d:
            /**
             * Steer Right
             */
            if (!checkCollision(playerX - cos(cameraAngle + M_PI / 2) * MOVE_SPEED, playerY - sin(cameraAngle + M_PI / 2) * MOVE_SPEED, map)) {
                playerX -= cos(cameraAngle + M_PI / 2) * MOVE_SPEED;
                playerY -= sin(cameraAngle + M_PI / 2) * MOVE_SPEED;
            }
            break;
        case SDLK_m:
            /**
             * Toggle map rendering
             */
            renderMap = !renderMap;
    }
}

void renderScene(SDL_Renderer *renderer, int map[10][10]) {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
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
        int wallColor = (map[(int)rayX][(int)rayY] == 1) ? 0xFF0000 : 0x00FF00;
        if (fmod(fabs(rayAngle), 360.0) < 90.0 || fmod(fabs(rayAngle), 360.0) > 270) {
            wallColor = 0xFF0000;
        } else {
            wallColor = 0x00FF00;
        }

        if (renderMap) {
            /** Draw  the map */
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    int mapColor = (map[i][j] == 1) ? 0xeeeeee : 0xaaaaaa;
                    SDL_SetRenderDrawColor(renderer, (mapColor >> 16) & 0xFF, (mapColor >> 8) & 0xFF, mapColor & 0xFF, 255);
                    SDL_RenderDrawPoint(renderer, i * 40, j * 40);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, (wallColor >> 16) & 0xFF, (wallColor >> 8) & 0xFF, wallColor & 0xFF, 255);
        SDL_RenderDrawLine(renderer, x, 300 - wallHeight / 2, x, 300 + wallHeight / 2);
    }
}

int checkCollision(float x, float y, int map[10][10]) {
    return map[(int)x][(int)y] == 1;
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
        handleEvents(&event, &window, map);

        renderScene(renderer, map);

        SDL_RenderPresent(renderer);
	}

    SDL_DestroyRenderer(renderer);
    cleanup(window);

	return (0);
}
