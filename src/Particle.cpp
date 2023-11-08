#include <stdlib.h>

#include "Particle.h"

namespace vtech {
	Particle::Particle() {
		// range -1 to +1
		x = ((2.0 * rand())/RAND_MAX) -1;
		y = ((2.0 * rand())/RAND_MAX) -1;
	}

	Particle::~Particle() {}
};