#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Init Failed!" << std::endl;
		return 1;
	}

	std::cout << "SDL Init succeeded!" << std::endl;

	SDL_Quit();

	return 0;
}