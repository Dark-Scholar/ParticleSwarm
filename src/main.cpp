#include <SDL.h>
#include <iostream>

#include "Screen.h"

int main(int argc, char *argv[]) {

	vtech::Screen screen;

	if (!screen.init()) {
		std::cout << "Error initialising SDL." << std::endl;
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

	screen.close();

	return 0;
}