#include <PhysicEngine/Header/ARigidBody.hpp>

namespace PhysicEngine {

	ARigidBody::ARigidBody(float p_inverseMass, Matrix3x3 p_inverseInertiaTensor, Vector3 p_position, Quaternion p_orientation, 
		Vector3 p_velocity, Vector3 p_angularVelocity, float p_linearDamping, float p_angularDamping)
	{
		_inverseMass = p_inverseMass;
		_inverseInertiaTensor = p_inverseInertiaTensor;
		_position = p_position;
		_orientation = p_orientation;
		_velocity = p_velocity;
		_angularVelocity = p_angularVelocity;
		_linearDamping = p_linearDamping;
		_angularDamping = p_angularDamping;
		_transformMatrix = Matrix3x4();
		_inverseInertiaTensorWorld = Matrix3x3();

		calculateDerivedData();

		_forceAccum = Vector3::ZERO;
		_torqueAccum = Vector3::ZERO;
	}

	inline void ARigidBody::s_calculateTransformMatrix(Matrix3x4& p_transformMatrix, const Vector3& p_position, const Quaternion& p_orientation)
	{
		p_transformMatrix._values[0] = 1 - 2 * p_orientation._complex[1] * p_orientation._complex[1] - 2 * p_orientation._complex[2] * p_orientation._complex[2];
		p_transformMatrix._values[1] = 2 * p_orientation._complex[0] * p_orientation._complex[1] - 2 * p_orientation._r * p_orientation._complex[2];
		p_transformMatrix._values[2] = 2 * p_orientation._complex[0] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[1];
		p_transformMatrix._values[3] = p_position._x;

		p_transformMatrix._values[4] = 2 * p_orientation._complex[0] * p_orientation._complex[1] - 2 * p_orientation._r * p_orientation._complex[2];
		p_transformMatrix._values[5] = 1 - 2 * p_orientation._complex[0] * p_orientation._complex[0] - 2 * p_orientation._complex[2] * p_orientation._complex[2];
		p_transformMatrix._values[6] = 2 * p_orientation._complex[1] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[0];
		p_transformMatrix._values[7] = p_position._y;

		p_transformMatrix._values[0] = 2 * p_orientation._complex[0] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[1];
		p_transformMatrix._values[1] = 2 * p_orientation._complex[1] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[0];
		p_transformMatrix._values[2] = 1 - 2 * p_orientation._complex[0] * p_orientation._complex[0] - 2 * p_orientation._complex[1] * p_orientation._complex[1];
		p_transformMatrix._values[3] = p_position._z;

	}

	void ARigidBody::calculateDerivedData() {
		_orientation.normalize();

		//calculate the body's transformation matrix
		s_calculateTransformMatrix(_transformMatrix, _position, _orientation);

		//calculate the body's inverse inertia tensor in world space;
		s_transformInertiaTensor(_inverseInertiaTensorWorld, _inverseInertiaTensor, _transformMatrix);
	}

	void ARigidBody::SetInertiaTensor(Matrix3x3 p_inertiaTensor)
	{
		_inverseInertiaTensor = p_inertiaTensor.getInversion();
	}

	inline void ARigidBody::s_transformInertiaTensor(Matrix3x3& p_iitWorld, const Matrix3x3& p_iitBody, const Matrix3x4& p_rotmat) {
		float t4 = p_rotmat._values[0] * p_iitBody._values[0] + p_rotmat._values[1] * p_iitBody._values[3] + p_rotmat._values[2] * p_iitBody._values[6];
		float t9 = p_rotmat._values[0] * p_iitBody._values[1] + p_rotmat._values[1] * p_iitBody._values[4] + p_rotmat._values[2] * p_iitBody._values[7];
		float t14 = p_rotmat._values[0] * p_iitBody._values[2] + p_rotmat._values[1] * p_iitBody._values[5] + p_rotmat._values[2] * p_iitBody._values[8];
		float t28 = p_rotmat._values[4] * p_iitBody._values[0] + p_rotmat._values[5] * p_iitBody._values[3] + p_rotmat._values[6] * p_iitBody._values[6];
		float t33 = p_rotmat._values[4] * p_iitBody._values[1] + p_rotmat._values[5] * p_iitBody._values[4] + p_rotmat._values[6] * p_iitBody._values[7];
		float t38 = p_rotmat._values[4] * p_iitBody._values[2] + p_rotmat._values[5] * p_iitBody._values[5] + p_rotmat._values[6] * p_iitBody._values[8];
		float t52 = p_rotmat._values[8] * p_iitBody._values[0] + p_rotmat._values[9] * p_iitBody._values[3] + p_rotmat._values[10] * p_iitBody._values[6];
		float t57 = p_rotmat._values[8] * p_iitBody._values[1] + p_rotmat._values[9] * p_iitBody._values[4] + p_rotmat._values[10] * p_iitBody._values[7];
		float t62 = p_rotmat._values[8] * p_iitBody._values[2] + p_rotmat._values[9] * p_iitBody._values[5] + p_rotmat._values[10] * p_iitBody._values[8];
		p_iitWorld._values[0] = t4 * p_rotmat._values[0] + t9 * p_rotmat._values[1] + t14 * p_rotmat._values[2];
		p_iitWorld._values[1] = t4 * p_rotmat._values[4] + t9 * p_rotmat._values[5] + t14 * p_rotmat._values[6];
		p_iitWorld._values[2] = t4 * p_rotmat._values[8] + t9 * p_rotmat._values[9] + t14 * p_rotmat._values[10];
		p_iitWorld._values[3] = t28 * p_rotmat._values[0] + t33 * p_rotmat._values[1] + t38 * p_rotmat._values[2];
		p_iitWorld._values[4] = t28 * p_rotmat._values[4] + t33 * p_rotmat._values[5] + t38 * p_rotmat._values[6];
		p_iitWorld._values[5] = t28 * p_rotmat._values[8] + t33 * p_rotmat._values[9] + t38 * p_rotmat._values[10];
		p_iitWorld._values[6] = t52 * p_rotmat._values[0] + t57 * p_rotmat._values[1] + t62 * p_rotmat._values[2];
		p_iitWorld._values[7] = t52 * p_rotmat._values[4] + t57 * p_rotmat._values[5] + t62 * p_rotmat._values[6];
		p_iitWorld._values[8] = t52 * p_rotmat._values[8] + t57 * p_rotmat._values[9] + t62 * p_rotmat._values[10];
	}
	void ARigidBody::addForce(const Vector3& p_force)
	{
		_forceAccum += p_force;
	}

	void ARigidBody::addForceAtPoint(const Vector3& p_force, const Vector3& p_point)
	{
		Vector3 pt = p_point - _position;
		_forceAccum += p_force;
		_torqueAccum += pt.vectorProduct(p_force);
	}

	void ARigidBody::addForceAtLocalPoint(const Vector3& p_force, const Vector3& p_point)
	{
		//going from local coordinates to world coordinates
		Vector3 pt = _transformMatrix.getInversion().transformPoint(p_point);

		addForceAtPoint(p_force, pt);
	}

	void ARigidBody::clearAccumulators()
	{
		_forceAccum = Vector3::ZERO;
		_torqueAccum = Vector3::ZERO;
	}

	void ARigidBody::integrate(double p_dt)
	{
		//linear acceleration
		Vector3 acceleration = _forceAccum * _inverseMass;

		//angular acceleration
		Vector3 angularAcceleration = _inverseInertiaTensorWorld * _torqueAccum;

		//update velocity
		_velocity += acceleration * p_dt;

		//update angular velocity
		_angularVelocity += angularAcceleration * p_dt;

		//drag
		_velocity *= pow(_linearDamping, p_dt);
		_angularVelocity *= pow(_angularDamping, p_dt);

		//update position
		_position += _velocity * p_dt;

		//update orientation
		_orientation.rotateFromVector(_angularVelocity * p_dt);

		//update matrices and normalize orientation
		calculateDerivedData();

		clearAccumulators();
	}
}