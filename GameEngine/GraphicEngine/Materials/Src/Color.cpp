#include <GraphicEngine/Materials/Header/Color.hpp>

namespace GraphicEngine::Materials {

		Color::Color(float p_r, float p_g, float p_b, float p_a)
		{
			_color[0] = p_r;
			_color[1] = p_g;
			_color[2] = p_b;
			_color[3] = p_a;
		}

#pragma region GETTERS
		GLfloat* Color::getBuffer()
		{
			return _color;
		}

		const GLfloat* Color::getBuffer() const
		{
			return _color;
		}
#pragma endregion

#pragma region SETTERS
		void Color::set(float p_color[4])
		{
			for (int cpt = 0; cpt < 4; ++cpt)
			{
				_color[cpt] = p_color[cpt];
			}
		}
#pragma endregion

#pragma region OPERATOR
		Color Color::operator* (Color const& p_color) const{
			return Color(_color[0] * p_color._color[0], _color[1] * p_color._color[1], _color[2] * p_color._color[2], _color[3] * p_color._color[3]);
		}

		Color Color::operator* (float p_value) const{
			return Color(_color[0] * p_value, _color[1] * p_value, _color[2] * p_value, _color[3] * p_value);
		}

		Color Color::operator/ (Color const& p_color) const{
			return Color(_color[0] / p_color._color[0], _color[1] / p_color._color[1], _color[2] / p_color._color[2], _color[3] / p_color._color[3]);
		}

		Color Color::operator/ (float p_value) const{
			return Color(_color[0] / p_value, _color[1] / p_value, _color[2] / p_value, _color[3] / p_value);
		}

		Color Color::operator+ (Color const& p_color) const{
			return Color(_color[0] + p_color._color[0], _color[1] + p_color._color[1], _color[2] + p_color._color[2], _color[3] + p_color._color[3]);
		}
#pragma endregion

		Color lerp(Color const& p1, Color const& p2, float t)
		{
			return p1 * (1 - t) + p2 * t;
		}
}