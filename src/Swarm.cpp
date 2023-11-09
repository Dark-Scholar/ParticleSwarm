#include "Swarm.h"

namespace vtech {
	Swarm::Swarm(): lastTime(0) {
		particles = new Particle[N_PARTICLES];
	}

	Swarm::~Swarm() {
		delete[] particles;
	}

	void Swarm::update(int elapsed) {
		int interval = elapsed - lastTime;

		for (int i = 0; i < Swarm::N_PARTICLES; i++) {
			particles[i].update(interval);
		}

		lastTime = elapsed;
	}
};