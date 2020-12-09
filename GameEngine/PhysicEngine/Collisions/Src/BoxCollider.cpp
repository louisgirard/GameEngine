#include <PhysicEngine/Collisions/Header/BoxCollider.hpp>

namespace PhysicEngine::Collisions {

	BoxCollider::BoxCollider(GraphicEngine::SceneBase::BoundingBox p_boundingBox){
		std::vector<glm::vec3> vertices = p_boundingBox.getVertices();

		for (int i = 0; i < vertices.size(); i++) {
			_vertices.push_back(Vector3::convertGlm(vertices[i]));
		}
	}

	void BoxCollider::setTransform(Matrix3x4 p_newTransform) {
		_transform = p_newTransform;
	}

	bool BoxCollider::resolvePlanCollision(Vector3 p_position, Vector3 p_normal, CollisionData p_data) {

		//Transform Vertices
		std::vector<Vector3> verticesTransformed = _vertices;
		for (int i = 0; i < verticesTransformed.size(); i++) {
			verticesTransformed[i] = _transform.transformPoint(verticesTransformed[i]);
		}

		//TODO 
	}
}