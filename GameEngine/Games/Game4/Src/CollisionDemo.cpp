#include <Games/Game4/Header/CollisionDemo.hpp>

namespace Games::Game4 {
	CollisionDemo::CollisionDemo() : GameBase()
	{

	}
	
	CollisionDemo::~CollisionDemo()
	{

	}

	void CollisionDemo::initGame()
	{
	}

	void CollisionDemo::handleInput(double p_dt)
	{
	}

	void CollisionDemo::updatePhysic(double p_dt)
	{
	}

	void CollisionDemo::updateFrame()
	{
	}

	void CollisionDemo::narrowPhaseCollisions(std::vector<std::vector<PhysicEngine::Collisions::Collider*>>& p_possibleCollisions)
	{
		for (int i = 0; i < p_possibleCollisions.size(); i++)
		{
			std::vector<PhysicEngine::Collisions::Collider*> colliders = p_possibleCollisions[i];
			for (int j = 0; j < colliders.size(); j++)
			{
				for (int k = j+1; k < colliders.size(); k++)
				{
					PhysicEngine::Collisions::CollisionData collisionData;
					// Check if the two colliders are collected and resolve the collision
					bool collided = colliders[j]->resolveCollision(*colliders[k], &collisionData);
					if (collided)
					{
						_collisionsData.push_back(collisionData);
					}
				}
			}
		}
	}
}
