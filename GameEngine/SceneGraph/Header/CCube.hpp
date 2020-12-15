#pragma once

#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Header/ARigidBody.hpp>
#include <GraphicEngine/SceneGraph/Header/PIrregularCube.hpp>
#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace SceneGraph {
	class CCube : public CMeshObject
	{
	private:
		/*Object abstraction*/
		std::shared_ptr<PhysicEngine::ARigidBody> _abstraction;

		void computeRigidBodyProperties(const std::vector<PhysicEngine::Vector3> p_vertices, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor);
	public:

		static const int FLAG;
		
		CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius);

		CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius,
			const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity,
			float p_linearDamping, float p_angularDamping);

		CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius,
			const PhysicEngine::Quaternion& p_orientation,
			const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping,
			const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor);

		void physicUpdate(float p_dt);

		/* @return the abstraction of the cube*/
		PhysicEngine::ARigidBody* getRigidBody();

		/*
		* Adds a force at a given point of the body in local space coordinates
		* @param p_force: the force to apply (world coordinates)
		* @param p_point: the point to apply the force at (local coordinates)
		*/
		void addForceAtLocalPoint(const PhysicEngine::Vector3& p_force, const PhysicEngine::Vector3& p_point);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);
	};
}



