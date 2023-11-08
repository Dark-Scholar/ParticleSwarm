#include "Swarm.h"

namespace vtech {
	Swarm::Swarm() {
		particles = new Particle[N_PARTICLES];
	}

	Swarm::~Swarm() {
		delete[] particles;
	}

	void Swarm::update() {
		for (int i = 0; i < Swarm::N_PARTICLES; i++) {
			particles[i].update();
		}
	}
};