#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Collisions/Header/Collider.hpp>

namespace PhysicEngine::Collisions {

	const int Collider::PLANE_CODE = 0;
	const int Collider::SPHERE_CODE = 1;

	Collider::Collider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, int p_geometryCode): _flag(p_flag), _mask(p_mask), _owner(p_owner),_geometryCode(p_geometryCode), _transform(Matrix3x4::identity()) {}

	const int Collider::getFlag() const{
		return _flag;
	}

	const int Collider::getGeometryCode() const{
		return _geometryCode;
	}

	const SceneGraph::CMeshObject* Collider::getOwner() const {
		return _owner;
	}

	void Collider::setTransform(const Matrix3x4& p_newTransform) {
		_transform = p_newTransform;
	}

	bool Collider::resolveCollision(Collider& const p_collider, CollisionData* p_data) {
		if ((_mask & p_collider.getFlag()) == 0) return false;
		return true;
	}
}