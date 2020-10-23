#include <PhysicEngine/Header/AHorizontalPlane.hpp>

namespace PhysicEngine {
	AHorizontalPlane::AHorizontalPlane(Vector3 p_bottomLeftCorner, float p_length, float p_width)
	{
		_bottomLeftCorner = p_bottomLeftCorner;
		_length = p_length;
		_width = p_width;
	}

	float AHorizontalPlane::getHeight()
	{
		return _bottomLeftCorner._y;
	}

	bool AHorizontalPlane::isAboveOrUnder(Vector3 p_position)
	{
		return p_position._x >= _bottomLeftCorner._x && p_position._x <= _bottomLeftCorner._x + _length
			&& p_position._z <= _bottomLeftCorner._z && p_position._z >= _bottomLeftCorner._z + _width;
	}
}