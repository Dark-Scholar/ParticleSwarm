#include <stdlib.h>

#include "Particle.h"

namespace vtech {
	Particle::Particle() {
		// range -1 to +1
		x = ((2.0 * rand())/RAND_MAX) -1;
		y = ((2.0 * rand())/RAND_MAX) -1;

		velocityX = universalConstant * (((2.0 * rand())/RAND_MAX) - 1);
		velocityY = universalConstant * (((2.0 * rand())/RAND_MAX) - 1);
	}

	Particle::~Particle() {}

	void Particle::update() {
		x += velocityX;
		y += velocityY;

		if (x <= -1.0 || x >= 1.0) {
			x = -x;
		}

		if (y <= -1.0 || x >= 1.0) {
			y = -y;
		}
	}
};