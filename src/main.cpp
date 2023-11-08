#include <SDL.h>
#include <iostream>

#include "Screen.h"

int main(int argc, char *argv[]) {

	vtech::Screen screen;

	if (!screen.init()) {
		std::cout << "Error initialising SDL." << std::endl;
	}

	while (true) {
		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}