#include <SceneGraph/Header/CCube.hpp>

namespace SceneGraph {

	const int CCube::FLAG = 1;

	void CCube::computeRigidBodyProperties(const PhysicEngine::Vector3& p_centerOfMass, const std::vector<PhysicEngine::Vector3> p_vertices, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor) {

		// Tensor 
		//Init 
		float i00 = 0;
		float i01 = 0;
		float i02 = 0;
		float i10 = 0;
		float i11 = 0;
		float i12 = 0;
		float i20 = 0;
		float i21 = 0;
		float i22 = 0;

		//Compute
		float mass_i = p_inverseMass / p_vertices.size();
		for (int i = 0; i < p_vertices.size(); i++) {
			float x_i = p_vertices[i]._x - p_centerOfMass._x;
			float y_i = p_vertices[i]._y - p_centerOfMass._y;
			float z_i = p_vertices[i]._z - p_centerOfMass._z;

			/* Diagonal is mass * square distance from axe (we can use pythagore which give us the addition of the square distance from the two other axes) */
			i00 += mass_i * (y_i * y_i + z_i * z_i);
			i11 += mass_i * (x_i * x_i + z_i * z_i);
			i22 += mass_i * (x_i * x_i + y_i * y_i);

			/* Diagonal is mass* square distance from plan */
			i01 += mass_i * (x_i * y_i);
			i02 += mass_i * (x_i * z_i);
			i12 += mass_i * (y_i * z_i);
		}

		i10 = i01;
		i20 = i02;
		i21 = i12;

		p_invInertiaTensor._values[0] = i00;
		p_invInertiaTensor._values[1] = -i10;
		p_invInertiaTensor._values[2] = -i20;
		p_invInertiaTensor._values[3] = -i01;
		p_invInertiaTensor._values[4] = i11;
		p_invInertiaTensor._values[5] = -i21;
		p_invInertiaTensor._values[6] = -i02;
		p_invInertiaTensor._values[7] = -i12;
		p_invInertiaTensor._values[8] = i22;

		//Compute inverse
		if (p_inverseMass == 0) { p_inverseMass = std::numeric_limits<float>::max(); }
		else {
			p_inverseMass = (1.f / p_inverseMass);
		}
		p_invInertiaTensor.invert();
	}

	CCube::CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius)
		:CCube(p_center, p_dimension, p_mass, p_collidersRadius, PhysicEngine::Quaternion::identity(), PhysicEngine::Vector3::ZERO, PhysicEngine::Vector3::ZERO, 0.99f, 0.99f) {}

	CCube::CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius,
		const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity,
		float p_linearDamping, float p_angularDamping) : 
		CCube(p_center, p_dimension, p_mass, p_collidersRadius, p_orientation, p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping, PhysicEngine::Vector3::RIGHT, PhysicEngine::Vector3::ZERO) {}

	CCube::CCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, float p_mass, float p_collidersRadius, const PhysicEngine::Quaternion& p_orientation,
		const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping,
		const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) {

		float width = p_dimension[0];
		float height = p_dimension[1];
		float depth = p_dimension[2];

		const PhysicEngine::Vector3 frontNW(p_center._x - (width / 2), p_center._y + (height / 2), p_center._z + (depth / 2));
		const PhysicEngine::Vector3 frontNE(p_center._x + (width / 2), p_center._y + (height / 2), p_center._z + (depth / 2));
		const PhysicEngine::Vector3 frontSW(p_center._x - (width / 2), p_center._y - (height / 2), p_center._z + (depth / 2));
		const PhysicEngine::Vector3 frontSE(p_center._x + (width / 2), p_center._y - (height / 2), p_center._z + (depth / 2));
		const PhysicEngine::Vector3 backNW(p_center._x - (width / 2), p_center._y + (height / 2), p_center._z - (depth / 2));
		const PhysicEngine::Vector3 backNE(p_center._x + (width / 2), p_center._y + (height / 2), p_center._z - (depth / 2));
		const PhysicEngine::Vector3 backSW(p_center._x - (width / 2), p_center._y - (height / 2), p_center._z - (depth / 2));
		const PhysicEngine::Vector3 backSE(p_center._x + (width / 2), p_center._y - (height / 2), p_center._z - (depth / 2));

		std::vector< PhysicEngine::Vector3> vertices = {
			frontNW, backNW, frontNE, backNE, frontSW, backSW, frontNE, backSE
		};

		float inverseMass = p_mass;
		PhysicEngine::Matrix3x3 invInertiaTensor;
		computeRigidBodyProperties(p_center, vertices, inverseMass, invInertiaTensor);

		_abstraction = std::make_shared< PhysicEngine::ARigidBody>(inverseMass, invInertiaTensor, p_center, p_orientation, p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping);
		_presentation = std::make_shared<GraphicEngine::PSceneGraph::PIrregularCube>(vertices, p_color, p_specularColor);

		//Init Colliders
		for (std::vector< PhysicEngine::Vector3>::iterator it = vertices.begin(); it != vertices.end(); it++) { 
			_colliders.push_back(new PhysicEngine::Collisions::SphereCollider(FLAG, 2, this, &(_abstraction->_transformMatrix), *it, p_collidersRadius));
		}

	}

	void CCube::physicUpdate(float p_dt) {
		_abstraction->integrate(p_dt);
	}

	void CCube::draw(std::string p_shaderName)
	{
		PhysicEngine::Matrix3x4 transform = _abstraction->_transformMatrix;
		CMeshObject::draw(p_shaderName, PhysicEngine::Matrix3x4::toGlm(transform));
	}
}
