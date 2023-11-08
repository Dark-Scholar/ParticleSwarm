#include <SDL.h>
#include <iostream>
#include <math.h>

#include "Screen.h"

int main(int argc, char *argv[]) {

	vtech::Screen screen;

	if (!screen.init()) {
		std::cout << "Error initialising SDL." << std::endl;
	}

	while (true) {
		int elapsed = SDL_GetTicks();

		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001))) * 128;
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

		for (int y = 0; y < vtech::Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < vtech::Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, red, green, blue);
			}
		}

		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}