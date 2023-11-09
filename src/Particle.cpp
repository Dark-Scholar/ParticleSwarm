#include <stdlib.h>
#include <math.h>

#include "Particle.h"
#include "Math.h"

namespace vtech {
	Particle::Particle(): x(0), y(0) {
		direction = (2 * M_PI * rand()/RAND_MAX);
		velocity = (universalConstant * rand())/RAND_MAX;
	}

	Particle::~Particle() {}

	void Particle::update(int interval) {
		double velocityX = velocity * cos(direction);
		double velocityY = velocity * sin(direction);

		x += velocityX * interval;
		y += velocityY * interval;
	}
};