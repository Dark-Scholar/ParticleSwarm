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

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);

	if (renderer == NULL) {
		std::cout << "Unable to create renderer." << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}

	if (texture == NULL) {
		std::cout << "Unable to create texture." << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 4;
	}

	// Create a piece of memory to hold information on all pixels.
	// For each pixel we have 4bytes (RGBA) each consisting of 8bits
	// 4 * 8 = 32
	// So we need 32 bits of data (the equivalent of an int on most systems)
	Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


	// Calculate the total number of bytes for the buffer
	size_t bufferSizeInBytes = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32);
	memset(buffer, 255, bufferSizeInBytes);

	// Pitch is the amount of memory allocated to a single row of pixels
	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH*sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;

	while (!quit) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	delete[] buffer; // remember to deallocate pointers
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}