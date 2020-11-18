#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>

#include <PhysicEngine/Header/CParticle.hpp>

#include <PhysicEngine/Forces/Header/ParticleForceRegistry.hpp>
#include <PhysicEngine/Forces/Header/ParticleGravity.hpp>

namespace Games {

	using Vector3 = PhysicEngine::Vector3;
	using Matrix3x3 = PhysicEngine::Matrix3x3;
	using Matrix3x4 = PhysicEngine::Matrix3x4;
	using Quaternion = PhysicEngine::Quaternion;

	using Particle = PhysicEngine::CParticle;

	using ForceRegistry = PhysicEngine::Forces::ParticleForceRegistry;
	using Gravity = PhysicEngine::Forces::ParticleGravity;
}