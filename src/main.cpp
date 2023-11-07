#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Init Failed!" << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"Particle Swarm",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		SDL_Quit();
		std::cout << "Could not create window: \n" << SDL_GetError() << std::endl;
		return 2;
	}

	SDL_Event event;
	bool quit = false;

	while (!quit) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}