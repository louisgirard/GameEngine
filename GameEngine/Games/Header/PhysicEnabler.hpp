#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>

#include <PhysicEngine/Header/CParticle.hpp>

#include <PhysicEngine/Forces/Header/ParticleForceRegistry.hpp>
#include <PhysicEngine/Forces/Header/ParticleGravity.hpp>

namespace Games {

	using Vector3 = PhysicEngine::Vector3;

	using Particle = PhysicEngine::CParticle;

	using ForceRegistry = PhysicEngine::Forces::ParticleForceRegistry;
	using Gravity = PhysicEngine::Forces::ParticleGravity;
}