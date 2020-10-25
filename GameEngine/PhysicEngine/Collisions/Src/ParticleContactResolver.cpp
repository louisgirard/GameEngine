#include <PhysicEngine/Collisions/Header/ParticleContactResolver.hpp>

namespace PhysicEngine {
	namespace Collisions {
		ParticleContactResolver::ParticleContactResolver(int p_iterations)
		{
			_iterations = p_iterations;
		}

		void ParticleContactResolver::setIterations(unsigned p_iterations)
		{
			_iterations = p_iterations;
		}

		void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*> p_contactArray, double p_dt)
		{
			int i = 0;
			while (i < _iterations) {
				//finding max separating velocity
				float max = INFINITY;
				int maxIndex = (int)p_contactArray.size();
				for (int j = 0; j < (int)p_contactArray.size(); j++) {
					float sepVel = p_contactArray[j]->calculateSeparatingVelocity();
					if (sepVel < max && (sepVel < 0 || p_contactArray[j]->getPenetration() > 0)) {
						max = sepVel;
						maxIndex = j;
					}
				}

				//if the maxIndex hasn't changed, there are no more contacts that need solving
				if (maxIndex == (int)p_contactArray.size()) {
					return;
				}
				else {
					//resolve contact
					p_contactArray[maxIndex]->resolve((float)p_dt);
				}

				i++;
			}
		}
	}
}
