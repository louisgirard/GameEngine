#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace PhysicEngine::Collisions {

	SphereCollider::SphereCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, float p_radius):
		Collider(p_flag, p_mask, p_owner, p_transform, SPHERE_CODE),_center(p_center), _radius(p_radius){}

	bool SphereCollider::insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) {

		// Gets the center transformed
		Vector3 transformedCenter = _transform->transformPoint(_center) ;
		
		// Gets box center and dimension
		Vector3 boxCenter = Vector3::convertGlm(p_region.center());
		Vector3 dimension = Vector3::convertGlm(p_region.extent());

		// Find the box's closest point to the sphere
		float x = std::max(boxCenter._x - dimension._x / 2.0f, std::min(transformedCenter._x, boxCenter._x + dimension._x / 2.0f));
		float y = std::max(boxCenter._y - dimension._y / 2.0f, std::min(transformedCenter._y, boxCenter._y + dimension._y / 2.0f));
		float z = std::max(boxCenter._z - dimension._z / 2.0f, std::min(transformedCenter._z, boxCenter._z + dimension._z / 2.0f));
		Vector3 closestPoint = Vector3(x, y, z);

		//compute distance between closest point and sphere center
		float distanceSquared = (closestPoint - transformedCenter).squaredMagnitude();
		
		return distanceSquared <= _radius * _radius;
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
		Vector3 transformedCenter = _transform->transformPoint(_center);

		// Check if point is on the same side of the normal
		float distance = (transformedCenter - p_boxCollider.getCenter()).scalarProduct(p_boxCollider.getNormal());
		if (distance < 0)
		{
			p_data->setPenetration(distance);
			p_data->setContactNormal(p_boxCollider.getNormal());
			p_data->setContactPoint(transformedCenter + p_boxCollider.getNormal() * (distance / 2.0));
			return true;
		}
		return false;
	}
}