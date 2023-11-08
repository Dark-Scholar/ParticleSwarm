#include "Swarm.h"

namespace vtech {
	Swarm::Swarm() {
		particles = new Particle[N_PARTICLES];
	}

	Swarm::~Swarm() {
		delete[] particles;
	}
};