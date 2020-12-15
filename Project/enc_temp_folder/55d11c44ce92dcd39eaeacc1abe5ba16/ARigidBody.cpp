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

	Vector3 ARigidBody::getPosition() const
	{
		return _position;
	}

	void ARigidBody::setPosition(const Vector3& p_position)
	{
		_position = p_position;
	}

	void ARigidBody::setPosition(const float p_x, const float p_y, const float p_z)
	{
		_position._x = p_x;
		_position._y = p_y;
		_position._z = p_z;
	}

	Vector3 ARigidBody::getVelocity() const
	{
		return _velocity;
	}

	void ARigidBody::setVelocity(const Vector3& p_velocity)
	{
		_velocity = p_velocity;
	}

	void ARigidBody::setVelocity(const float p_x, const float p_y, const float p_z)
	{
		_velocity._x = p_x;
		_velocity._y = p_y;
		_velocity._z = p_z;
	}

	float ARigidBody::getLinearDamping() const
	{
		return _linearDamping;
	}

	void ARigidBody::setLinearDamping(const float p_linearDamping)
	{
		_linearDamping = p_linearDamping;
	}

	float ARigidBody::getAngularDamping() const
	{
		return _angularDamping;
	}

	void ARigidBody::setAngularDamping(const float p_angularDamping)
	{
		_angularDamping = p_angularDamping;
	}

	float ARigidBody::getInverseMass() const
	{
		return _inverseMass;
	}

	void ARigidBody::setInverseMass(const float p_inverseMass)
	{
		_inverseMass = p_inverseMass;
	}

	float ARigidBody::getMass() const
	{
		if (_inverseMass == 0) {
			return std::numeric_limits<float>::max();
		}
		else {
			return 1.0f / _inverseMass;
		}
	}

	void ARigidBody::setMass(const float p_mass)
	{
		if (p_mass == 0) {
			_inverseMass = INFINITY;
		}
		else {
			_inverseMass = 1.0f / p_mass;
		}
	}

	inline void ARigidBody::s_calculateTransformMatrix(Matrix3x4& p_transformMatrix, const Vector3& p_position, const Quaternion& p_orientation)
	{
		p_transformMatrix._values[0] = 1 - 2 * p_orientation._complex[1] * p_orientation._complex[1] - 2 * p_orientation._complex[2] * p_orientation._complex[2];
		p_transformMatrix._values[1] = 2 * p_orientation._complex[0] * p_orientation._complex[1] - 2 * p_orientation._r * p_orientation._complex[2];
		p_transformMatrix._values[2] = 2 * p_orientation._complex[0] * p_orientation._complex[2] + 2 * p_orientation._r * p_orientation._complex[1];
		p_transformMatrix._values[3] = p_position._x;

		p_transformMatrix._values[4] = 2 * p_orientation._complex[0] * p_orientation._complex[1] + 2 * p_orientation._r * p_orientation._complex[2];
		p_transformMatrix._values[5] = 1 - 2 * p_orientation._complex[0] * p_orientation._complex[0] - 2 * p_orientation._complex[2] * p_orientation._complex[2];
		p_transformMatrix._values[6] = 2 * p_orientation._complex[1] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[0];
		p_transformMatrix._values[7] = p_position._y;

		p_transformMatrix._values[8] = 2 * p_orientation._complex[0] * p_orientation._complex[2] - 2 * p_orientation._r * p_orientation._complex[1];
		p_transformMatrix._values[9] = 2 * p_orientation._complex[1] * p_orientation._complex[2] + 2 * p_orientation._r * p_orientation._complex[0];
		p_transformMatrix._values[10] = 1 - 2 * p_orientation._complex[0] * p_orientation._complex[0] - 2 * p_orientation._complex[1] * p_orientation._complex[1];
		p_transformMatrix._values[11] = p_position._z;
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
		std::cout << "Diff " << pt << std::endl;
		_forceAccum += p_force;
		_torqueAccum += pt.vectorProduct(p_force);
	}

	void ARigidBody::addForceAtLocalPoint(const Vector3& p_force, const Vector3& p_point)
	{
		std::cout << "Point given " << p_point << std::endl;

		//going from local coordinates to world coordinates
		Vector3 pt = _transformMatrix.transformPoint(p_point);

		std::cout << "Point transform " << pt << std::endl;

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
		//std::cout << "Start Angular velocity " << _angularVelocity << std::endl;
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
		_orientation.updateByAngularVelocity(_angularVelocity, p_dt);

		/*std::cout << "Force" << _forceAccum << std::endl;
		std::cout << "Acceleration " << acceleration << std::endl;
		std::cout << "DT" << p_dt << std::endl;
		std::cout << "Velocity " << _velocity << std::endl;*/
		std::cout << "Angular velocity " << _angularVelocity << std::endl;
		std::cout << "Orientation " << _orientation << std::endl;
		std::cout << "Torque " << _torqueAccum << std::endl << std::endl;


		//update matrices and normalize orientation
		calculateDerivedData();

		clearAccumulators();
	}
}