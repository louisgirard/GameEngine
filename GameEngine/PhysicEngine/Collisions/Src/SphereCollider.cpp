#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace PhysicEngine::Collisions {

	SphereCollider::SphereCollider(GraphicEngine::SceneBase::BoundingBox p_boundingBox):_center(Vector3::convertGlm(p_boundingBox.center())), _transform(Matrix3x4::identity()){
		_radius = std::max(p_boundingBox.extent().r, std::max(p_boundingBox.extent().g, p_boundingBox.extent().b))/2.0f;
	}

	void SphereCollider::setTransform(Matrix3x4 p_newTransform) {
		_transform = p_newTransform;
	}

	bool SphereCollider::insideRegion(GraphicEngine::SceneBase::BoundingBox p_region) {

		// Gets the center transformed
		Vector3 transformedCenter = _transform.transformPoint(_center) ;
		
		// Gets box center and dimension
		Vector3 boxCenter = Vector3::convertGlm(p_region.center());
		Vector3 dimension = Vector3::convertGlm(p_region.extent());

		// Region is axis aligned then we only need to verify for each axis if a part of the sphere is inside the box  
		if ((std::abs(transformedCenter._x - boxCenter._x) - _radius) < (dimension._x/2.0f)) {
			return true;
		}
		else if ((std::abs(transformedCenter._y - boxCenter._y) - _radius) < (dimension._y / 2.0f)) {
			return true;
		}
		else if ((std::abs(transformedCenter._z - boxCenter._z) - _radius) < (dimension._z / 2.0f)) {
			return true;
		}
		
		// Then the only thing we need to know is if the the distance is inferior or equal to the radius to know if there is a collision between the sphere and the plane
		return false;
	}
}