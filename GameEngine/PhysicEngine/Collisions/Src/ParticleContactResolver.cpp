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

		void ParticleContactResolver::resolveContacts(ParticleContact* p_contactArray, int p_numContacts, double p_dt)
		{
			int i = 0;
			while (i < _iterations) {
				//finding max separating velocity
				float max = INFINITY;
				int maxIndex = p_numContacts;
				for (int j = 0; j < p_numContacts; j++) {
					float sepVel = p_contactArray[j].calculateSeparatingVelocity();
					if (sepVel < max && (sepVel < 0 || p_contactArray[j].getPenetration()>0)) {
						max = sepVel;
						maxIndex = j;
					}
				}

				//if the maxIndex hasn't changed, there are no more contacts that need solving
				if (maxIndex == p_numContacts) {
					return;
				}
				else {
					//resolve contact
					p_contactArray[maxIndex].resolve(p_dt);
				}

				i++;
			}
		}
	}
}
