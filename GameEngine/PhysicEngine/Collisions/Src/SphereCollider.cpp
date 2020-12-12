#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace PhysicEngine::Collisions {

	SphereCollider::SphereCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Vector3 p_center, float p_radius):
		Collider(p_flag, p_mask, p_owner, SPHERE_CODE),_center(p_center), _radius(p_radius){}

	bool SphereCollider::insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) {

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

	bool SphereCollider::resolveCollision(Collider& const p_collider, CollisionData* p_data) {
		
		if (!Collider::resolveCollision(p_collider, p_data)) return false;

		if (p_collider.getGeometryCode() == PLANE_CODE) {
			PlaneCollider& planeCollider = dynamic_cast<PlaneCollider&>(p_collider);
			return resolvePlaneCollision(planeCollider, p_data);
		}

		return false;
	}

	bool SphereCollider::resolvePlaneCollision(const PlaneCollider& p_boxCollider, CollisionData* p_data) {
		// Gets the center transformed
		Vector3 transformedCenter = _transform.transformPoint(_center);

		// Check if point is on the same side of the normal
		float side = (transformedCenter - p_boxCollider.getCenter()).scalarProduct(p_boxCollider.getNormal());
		if (side < 0)
		{
			// TODO, fill CollisionData information
			return true;
		}
		return false;
	}
}