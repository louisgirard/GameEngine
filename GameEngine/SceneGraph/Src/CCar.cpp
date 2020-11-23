#include <SceneGraph/Header/CCar.hpp>

namespace SceneGraph{

	const std::string CCar::CAR_MODEL = "Chevrolet_Camaro_SS_Low.obj";

	void CCar::computeRigidBodyProperties(float p_mass, PhysicEngine::Vector3& p_centerOfMass, float& p_inverseMass, PhysicEngine::Matrix3x3& p_invInertiaTensor) {
		//Init
		GraphicEngine::SceneBase::BoundingBox bb = computeSceneBoundingBox();
		p_centerOfMass = PhysicEngine::Vector3::ZERO;
		p_inverseMass = 0;

		std::vector<glm::vec3> vertices = bb.getVertices();
		//Compute
		for (int i = 0; i < vertices.size(); i++) {
			p_centerOfMass += PhysicEngine::Vector3::convertGlm(vertices[i]) * (p_mass / 8.f);
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
		for (int i = 0; i < vertices.size(); i++) {

			float mass_i = p_mass/8;
			PhysicEngine::Vector3 vec = PhysicEngine::Vector3::convertGlm(vertices[i]);
			float x_i = vec._x - p_centerOfMass._x;
			float y_i = vec._y - p_centerOfMass._y;
			float z_i = vec._z - p_centerOfMass._z;

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
		p_invInertiaTensor.invert();
	}

	CCar::CCar(const PhysicEngine::Vector3& p_center, float p_mass)
		:CCar(p_center, p_mass, PhysicEngine::Quaternion::identity(), PhysicEngine::Vector3::ZERO, PhysicEngine::Vector3::ZERO, 0.99f, 0.99f) {}


	CCar::CCar(const PhysicEngine::Vector3& p_center, float p_mass, const PhysicEngine::Quaternion& p_orientation, const PhysicEngine::Vector3& p_velocity, const PhysicEngine::Vector3& p_angularVelocity, float p_linearDamping, float p_angularDamping) {

		std::filesystem::path meshPath = Games::dataPath() / "car" / CAR_MODEL;
		addSon(GraphicEngine::Servers::SceneServer::getSingleton()->load(meshPath));

		float inverseMass;
		PhysicEngine::Vector3 centerOfMass;
		PhysicEngine::Matrix3x3 invInertiaTensor;
		computeRigidBodyProperties(p_mass, centerOfMass, inverseMass, invInertiaTensor);
		_abstraction = std::make_shared< PhysicEngine::ARigidBody>( inverseMass, invInertiaTensor, centerOfMass, p_orientation, p_velocity, p_angularVelocity, p_linearDamping, p_angularDamping);

		

	}

	void CCar::draw(std::string p_shaderName)
	{
		PhysicEngine::Matrix3x4 transform = _abstraction->_transformMatrix;
		CMeshObject::draw(p_shaderName, PhysicEngine::Matrix3x4::toGlm(transform));
	}

}