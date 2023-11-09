#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

namespace vtech {
	class Swarm {
		public:
			const static int N_PARTICLES = 5000;
		private:
			Particle *particles;
			int lastTime;
		public:
			Swarm();
			virtual ~Swarm();

			const Particle *const getParticles() { return particles; }

			void update(int elapsed);
	};
};

#endif