#include <SDL.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "Screen.h"
#include "Swarm.h"
#include "Particle.h"

int main(int argc, char *argv[]) {

	srand(time(NULL));

	vtech::Swarm swarm;

	vtech::Screen screen;

	if (!screen.init()) {
		std::cout << "Error initialising SDL." << std::endl;
	}

	while (true) {
		/* We use this to get an interval to multiply our velocities
		   this ensures the amount we move a particle by on each update
			 is proportional to the amount the particle moved on the previous
			 update.*/
		int elapsed = SDL_GetTicks();

		screen.clear();
		swarm.update(elapsed);

		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001))) * 128;
		unsigned char red = (unsigned char)((1 + cos(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

		const vtech::Particle *const particles = swarm.getParticles();
		for (int i = 0; i < vtech::Swarm::N_PARTICLES; i++) {
			vtech::Particle particle = particles[i];

			int x = (particle.x + 1) * vtech::Screen::SCREEN_WIDTH / 2;
			int y = (particle.y * vtech::Screen::SCREEN_WIDTH / 2) + (vtech::Screen::SCREEN_HEIGHT / 2);

			screen.setPixel(x, y, red, green, blue);
		}

		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
};