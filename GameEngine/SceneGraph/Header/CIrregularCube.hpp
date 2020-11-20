#pragma once


#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Header/ARigidBody.hpp>
#include <GraphicEngine/SceneGraph/Header/PIrregularCube.hpp>
#include <GraphicEngine/SceneGraph/Header/PParticle.hpp>

namespace SceneGraph {
	class CIrregularCube : public CMeshObject
	{
	private:
		/*Object abstraction*/
		std::shared_ptr<PhysicEngine::ARigidBody> _abstraction;

		/*Trail*/
		std::vector <std::shared_ptr < GraphicEngine::PSceneGraph::PParticle>> _trails;
		int _trailOffset;
		std::vector<PhysicEngine::Vector3> _trailPosition;

		void computeRigidBodyProperties(const std::vector<PhysicEngine::Vector3> p_vertices, const std::vector<float>  p_massRepartition, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor);

	public:

		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition);

		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor);

		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition,
			const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor,
			int p_nbTrailComponent, float p_trailSize,  const PhysicEngine::Vector3& p_trailColor);

		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition,
			const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping);

		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Quaternion& p_orientation,
			const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping, 
			const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor);

		
		CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Quaternion& p_orientation,
			const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping,
			const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor,
			int p_nbTrailComponent, float p_trailSize, const PhysicEngine::Vector3& p_trailColor);
		

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

		/*Mark origin where it is now*/
		void markOrigin();

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);
	};
}


