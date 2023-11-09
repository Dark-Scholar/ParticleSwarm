#ifndef PARTICLE_H
#define PARTICLE_H

#include <chrono>

namespace vtech {
	class Particle {
		public:
			std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
			// Ideally this would be private
			// but in simulations and games
			// we need to make concessions for efficiency
			// in this case we make x and y public as we access
			// them on every frame render.
			double x;
			double y;

			double expansionSpeed = 0.0002;
			double direction;
			double velocity;


			Particle();
			virtual ~Particle();

			void update(int interval);
		private:
			void init();
	};
};

#endif