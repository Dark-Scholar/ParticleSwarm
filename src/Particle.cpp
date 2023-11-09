#include <stdlib.h>
#include <math.h>

#include "Particle.h"
#include "Math.h"

namespace vtech {
	Particle::Particle(): x(0), y(0) {
		init();
	}

	Particle::~Particle() {}

	void Particle::init() {
		x = 0;
	  y = 0;

		direction = -(2 * M_PI * rand()/RAND_MAX);

		velocity = (expansionSpeed * rand())/RAND_MAX;
		velocity *= velocity;

		startTime = std::chrono::steady_clock::now();
	}

	void Particle::update(int interval) {
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(
			currentTime - startTime
		);

		if (rand() / RAND_MAX > 0.5) {
			direction += interval * 0.0004;
		} else {
			direction -= interval * 0.0004;
		}

    if (elapsedTime.count() >= 3.0) {
      expansionSpeed = 0.023;
    }

		velocity = (expansionSpeed * rand()) / RAND_MAX;
		velocity *= velocity;

		double velocityX = velocity * cos(direction);
		double velocityY = velocity * sin(direction);

		x += velocityX * interval;
		y += velocityY * interval;

		if (x <= -1.0 || x >= 1.0 || y <= -1.0 || y >= 1.0) {
      init();
    }
	}
};