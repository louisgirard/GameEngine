#include <SceneGraph/Header/CIrregularCube.hpp>

namespace SceneGraph {

	void CIrregularCube::computeRigidBodyProperties(const std::vector<PhysicEngine::Vector3> p_vertices, const std::vector<float>  p_massRepartition, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor) {
		
		assert((p_vertices.size() == p_massRepartition.size()) && "CIrregularObject::computeCenterOfMass Mass repartition should be of size 8");
		
		//Init
		p_centerOfMass = PhysicEngine::Vector3::ZERO;
		p_inverseMass = 0;

		//Compute
		for (int i = 0; i < p_vertices.size(); i++) {
			p_inverseMass += p_massRepartition[i];
			p_centerOfMass += p_vertices[i] * p_massRepartition[i];

		}

		//Compute inverse
		if (p_inverseMass == 0) { p_inverseMass = std::numeric_limits<float>::max(); }
		else {
			p_inverseMass = (1.f / p_inverseMass);
		}
		p_centerOfMass *= p_inverseMass;

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
		for (int i = 0; i < p_vertices.size(); i++) {

			float mass_i = p_massRepartition[i];
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

		std::cout << "Inertia Tensor before invertion" << p_invInertiaTensor << std::endl;
		//Compute inverse
		p_invInertiaTensor.invert();
		std::cout << "Inverse inertia tenseur computed" << p_invInertiaTensor << std::endl;
	}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition)
		:CIrregularCube(p_center, p_dimension, p_massRepartition, PhysicEngine::Vector3(1,0,0), PhysicEngine::Vector3(0,0,0)) {}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) :
		CIrregularCube(p_center, p_dimension, p_massRepartition, p_color, p_specularColor, 5, 0.1f, PhysicEngine::Vector3(0,1,0)) {}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor, int p_nbTrailComponent, float p_trailSize, const PhysicEngine::Vector3& p_trailColor):
		CIrregularCube(p_center, p_dimension, p_massRepartition,
			PhysicEngine::Quaternion::identity(), PhysicEngine::Vector3::ZERO, PhysicEngine::Vector3::ZERO, 0.99f, 0.99f,
			p_color, p_specularColor, p_nbTrailComponent, p_trailSize, p_trailColor) {}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Quaternion& p_orientation,
		const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping):
		CIrregularCube(p_center, p_dimension, p_massRepartition, p_orientation,
			p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping, PhysicEngine::Vector3(1, 0, 0), PhysicEngine::Vector3(0, 0, 0)) {}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Quaternion& p_orientation,
		const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) :
		CIrregularCube(p_center, p_dimension, p_massRepartition, p_orientation,
			p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping, p_color, p_specularColor, 5, 0.1f, PhysicEngine::Vector3(0, 1, 0)) {}

	CIrregularCube::CIrregularCube(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_dimension, const std::vector<float> p_massRepartition, const PhysicEngine::Quaternion& p_orientation,
		const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping,
		const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor, 
		int p_nbTrailComponent, float p_trailSize, const PhysicEngine::Vector3& p_trailColor) {

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

		float inverseMass;
		PhysicEngine::Vector3 centerOfMass;
		PhysicEngine::Matrix3x3 invInertiaTensor;
		computeRigidBodyProperties(vertices, p_massRepartition, centerOfMass, inverseMass, invInertiaTensor);
		std::cout << "Inverse inertia tenseur " << invInertiaTensor << std::endl;
		_abstraction = std::make_shared< PhysicEngine::ARigidBody>(inverseMass, invInertiaTensor, p_center, p_orientation, p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping);

		const PhysicEngine::Vector3 frontNWOrigin = frontNW - centerOfMass;
		const PhysicEngine::Vector3 frontNEOrigin = frontNE - centerOfMass;
		const PhysicEngine::Vector3 frontSWOrigin = frontSW - centerOfMass;
		const PhysicEngine::Vector3 frontSEOrigin = frontSE - centerOfMass;
		const PhysicEngine::Vector3 backNWOrigin = backNW - centerOfMass;
		const PhysicEngine::Vector3 backNEOrigin = backNE - centerOfMass;
		const PhysicEngine::Vector3 backSWOrigin = backSW - centerOfMass;
		const PhysicEngine::Vector3 backSEOrigin = backSE - centerOfMass;

		std::vector< PhysicEngine::Vector3> verticesFromOrigin = {
			frontNWOrigin, backNWOrigin, frontNEOrigin, backNEOrigin, frontSWOrigin, backSWOrigin, frontSEOrigin, backSEOrigin
		};

		_presentation = std::make_shared<GraphicEngine::PSceneGraph::PIrregularCube>(verticesFromOrigin, p_color, p_specularColor);

		/*Init Trail*/
		_trailOffset = 0;
		for (int i = 0; i < p_nbTrailComponent; i++) {
			_trails.push_back(std::make_shared< GraphicEngine::PSceneGraph::PParticle>(p_trailColor, p_trailSize));
			_trailPosition.push_back(centerOfMass);
		}

	}

	void CIrregularCube::markOrigin() {
		_trailPosition[_trailOffset] = _abstraction->_position;
		_trailOffset += 1;
		_trailOffset %= _trailPosition.size();
	}

	void CIrregularCube::draw(std::string p_shaderName)
	{
		PhysicEngine::Matrix3x4 transform = _abstraction->_transformMatrix;
		/*std::cout << "mat" << glm::translate(glm::mat4(1.0), Vector3::toGlm(_abstraction->_position)) << std::endl;
		CMeshObject::draw(p_shaderName, glm::translate(glm::mat4(1.0), Vector3::toGlm(_abstraction->_position)));*/
		std::cout << "mat" << transform << std::endl;
		CMeshObject::draw(p_shaderName, Matrix3x4::toGlm(transform));
		for (int i = 0; i < _trails.size(); i++) {
			_trails[i]->draw(_trailPosition[i]);
		}
	}
}