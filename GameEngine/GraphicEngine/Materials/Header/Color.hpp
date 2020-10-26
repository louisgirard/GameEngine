#pragma once

#include <iostream>

#include <GL/freeglut.h>

namespace GraphicEngine::Materials {
		class Color
		{
		private:

			/* Color component */
			GLfloat _color[4];

		public:

			/*
			* Constructor
			* @param p_r : Red component
			* @param p_g : Green component
			* @param p_b : Blue component
			* @param p_a : Alpha component
			*/
			Color(float p_r = 0.0f, float p_g = 0.0f, float p_b = 0.0f, float p_a = 1.0f);

#pragma region GETTERS
			/*
			* Gets the color as an array of GLFloat (compatible with OpenGL function)
			* @return an array of 4 GLFloat 
			*/
			GLfloat* getBuffer();

			/*
			* Gets the color as an array of GLFloat (compatible with OpenGL function)
			* @return an array of 4 GLFloat
			*/
			const GLfloat* getBuffer() const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets a color
			* @param p_color : the color to set
			*/
			void set(float p_color[4]);
#pragma endregion

#pragma region OPERATOR
			/*
			* Multiplication operator
			* @param p_color : the color to multiply this color with
			* @return the result of the multiplication
			*/
			Color operator* (Color const& p_color) const;

			/*
			* Multiplication operator
			* @param p_value : the scalar to multiply this color with
			* @return the result of the multiplication
			*/
			Color operator* (float p_value) const;

			/*
			* Division operator
			* @param p_color : the color to divide this color with
			* @return the result of the division
			*/
			Color operator/ (Color const& p_color) const;

			/*
			* Division operator
			* @param p_value : the scalar to divide this color with
			* @return the result of the division
			*/
			Color operator/ (float p_value) const;

			/*
			* Addition operator
			* @param p_color : the color to add 
			* @return the result of the addition
			*/
			Color operator+ (Color const& p_color) const;
#pragma endregion
		};

		/*
		* Linear interpolation beetween color
		*
		* @param p_c1 : First color
		* @param p_c2 : Second color
		* @param p_t : Interpolation coefficient in [0,1]
		* @return the interpolated colors
		*/
		inline Color lerp(Color const& p1, Color const& p2, float t);
}



