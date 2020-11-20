#pragma once

#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Header/ARigidBody.hpp>
#include <GraphicEngine/Servers/Header/SceneServer.hpp>
#include <string>

namespace SceneGraph {
	class CCar : public CMeshObject
	{
	private:
		const static std::string CAR_MODEL;

		void computeRigidBodyProperties(float p_mass, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor);

	public:
		/*Object abstraction*/
		std::shared_ptr<PhysicEngine::ARigidBody> _abstraction;

		CCar(const PhysicEngine::Vector3& p_center, float p_mass);


		CCar(const PhysicEngine::Vector3& p_center, float p_mass, const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);

	};
}


