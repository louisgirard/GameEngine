#pragma once

#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Header/ARigidBody.hpp>
#include <GraphicEngine/Servers/Header/SceneServer.hpp>
#include <Math/Header/Vector3.hpp>
#include <string>

namespace SceneGraph {
	class CCar : public EmptyNode
	{
	private:
		const static std::string CAR_MODEL;

		/*
		* Compute every rigidBody properties needed 
		* @param p_mass :total mass
		* @param p_center : model center
		* @param p_centerOfMass : center of mass (out)
		* @param p_inverseMass : inverse mass (out)
		* @param p_invInertiaTensor : inverse inertia tensor of the model (out)
		*/
		void computeRigidBodyProperties(float p_mass, const PhysicEngine::Vector3& p_center, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor);

		Math::Vector3 _dim;
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

		Math::Vector3 getDim()
		{
			return _dim;
		}

	};
}


