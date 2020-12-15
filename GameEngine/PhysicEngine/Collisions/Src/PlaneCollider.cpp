#include <PhysicEngine/Collisions/Header/PlaneCollider.hpp>
#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace PhysicEngine::Collisions {

	PlaneCollider::PlaneCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, Vector3 p_normal) :
		Collider(p_flag, p_mask, p_owner, p_transform, PLANE_CODE),_center(p_center), _normal(p_normal){}

	const Vector3 PlaneCollider::getCenter() const {
		return _center;
	}

	const Vector3 PlaneCollider::getNormal() const {
		return _normal;
	}

	bool PlaneCollider::insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) {
	
		// Gets property transformed
		Vector3 transformedCenter = getCenter();
		Vector3 transformedNormal = getNormal();

		// Gets box center and dimension
		Vector3 boxCenter = Vector3::convertGlm(p_region.center());
		Vector3 dimension = Vector3::convertGlm(p_region.extent());

		// Project center onto plan
		Vector3 planToCenter = boxCenter - transformedCenter;
		float distance = planToCenter.scalarProduct(transformedNormal);
		Vector3 projectedPoint = boxCenter - transformedNormal *distance;

		// We test if closest point is inside box
		return (((transformedNormal._x != 0 && std::abs(boxCenter._x - projectedPoint._x) <= dimension._x / 2) || transformedNormal._x == 0)
			&& ((transformedNormal._y != 0 && std::abs(boxCenter._y - projectedPoint._y) <= dimension._y / 2) || transformedNormal._y == 0)
			&& ((transformedNormal._z != 0 && std::abs(boxCenter._z - projectedPoint._z) <= dimension._z / 2) || transformedNormal._z == 0));
	}

	bool PlaneCollider::resolveCollision(Collider& const p_collider, CollisionData* p_data) {

		if (!Collider::resolveCollision(p_collider, p_data)) return false;

		if (p_collider.getGeometryCode() == SPHERE_CODE) {
			SphereCollider& sphereCollider = dynamic_cast<SphereCollider&>(p_collider);
			return sphereCollider.resolvePlaneCollision(*this, p_data);
		}

		return false;
	}

}
