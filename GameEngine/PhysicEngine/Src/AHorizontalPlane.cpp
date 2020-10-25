#include <PhysicEngine/Header/AHorizontalPlane.hpp>

namespace PhysicEngine {
	AHorizontalPlane::AHorizontalPlane(Vector3 p_center, float p_length, float p_width)
	{
		_center = p_center;
		_length = p_length;
		_width = p_width;
	}

	float AHorizontalPlane::getHeight()
	{
		return _center._y;
	}

	bool AHorizontalPlane::isAboveOrUnder(Vector3 p_position)
	{
		/*return p_position._x >= _bottomLeftCorner._x && p_position._x <= _bottomLeftCorner._x + _length
			&& p_position._z <= _bottomLeftCorner._z && p_position._z >= _bottomLeftCorner._z + _width;*/
		return p_position._x <= _center._x + _length / 2 && p_position._x >= _center._x - _length / 2
			&& p_position._z >= _center._z - _width / 2 && p_position._z <= _center._z + _width / 2;
	}
}