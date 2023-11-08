#include <SDL.h>
#include <iostream>

#include "Screen.h"

int main(int argc, char *argv[]) {

	vtech::Screen screen;

	if (!screen.init()) {
		std::cout << "Error initialising SDL." << std::endl;
	}

	while (true) {

		for (int y = 0; y < vtech::Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < vtech::Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, 128, 0, 255);
			}
		}

		screen.setPixel(400, 300, 255, 255, 255);

		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}