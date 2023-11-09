#ifndef PARTICLE_H
#define PARTICLE_H

namespace vtech {
	class Particle {
		public:
			// Ideally this would be private
			// but in simulations and games
			// we need to make concessions for efficiency
			// in this case we make x and y public as we access
			// them on every frame render.
			double x;
			double y;

			const double universalConstant = 0.0001;
			double direction;
			double velocity;

			Particle();
			virtual ~Particle();

			void update(int interval);
	};
};

#endif