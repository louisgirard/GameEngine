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

		/*Object abstraction*/
		std::shared_ptr<PhysicEngine::ARigidBody> _abstraction;

		void computeRigidBodyProperties(float p_mass, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor);

	public:

		CCar(const PhysicEngine::Vector3& p_center, float p_mass);


		CCar(const PhysicEngine::Vector3& p_center, float p_mass, const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping);

		//updates internal data (transformMatrix, world space inertia tensor)
		void calculateDerivedData();


		void SetInertiaTensor(PhysicEngine::Matrix3x3 p_inertiaTensor);

		/*Adds a force at the center of mass of the rigidbody (no torque)
		* @param p_force: the force to apply
		*/
		void addForce(const PhysicEngine::Vector3& p_force);

		/*
		* Adds a force at a given point of the body in world space coordinates
		* @param p_force: the force to apply (world coordinates)
		* @param p_point: the point to apply the force at (world coordinates)
		*/
		void addForceAtPoint(const PhysicEngine::Vector3& p_force, const PhysicEngine::Vector3& p_point);

		/*
		* Adds a force at a given point of the body in local space coordinates
		* @param p_force: the force to apply (world coordinates)
		* @param p_point: the point to apply the force at (local coordinates)
		*/
		void addForceAtLocalPoint(const PhysicEngine::Vector3& p_force, const PhysicEngine::Vector3& p_point);

		//Clears the force and torque accumulators
		void clearAccumulators();

		void integrate(double p_dt);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);

	};
}


