#pragma once

#include <sstream>

#include <GraphicEngine/Materials/Header/Color.hpp>

namespace GraphicEngine::SceneBase {
		class Text
		{
		private:

			/* The output stream used to display strings in OpenGL rendering context */
			static ::std::stringstream* s_out;

			/*
			* Displays the provided string in openGL
			*
			* @param p_x : The x position of the text
			* @param p_y : The y position of the text
			* @param p_text : The text
			* @param p_color : The color of the text
			*/
			static void display(GLfloat p_x, GLfloat p_y, const ::std::string& p_text, const Materials::Color& p_color);

#pragma region ORTHOGRAPHIC_MODE
			/*
			* Sets in orthographic projection mode
			*/
			static void setOrthographicProjection();

			/*
			* Resets the orthographic projection mode
			*/
			static void resetOrthographicProjection();
#pragma endregion

		public:

			/*
			* Displays the content of the stream in the openGL rendering context
			*
			* @param p_x : The x coordinate where the displays starts
			* @param p_y : The y coordinate where the displays starts
			* @param p_color : The font color
			*/
			static void display(GLfloat p_x, GLfloat p_y, const Materials::Color& p_color = Materials::Color(0.0, 1.0, 0.5));

#pragma region GETTERS
			/*
			* Gets the output stream
			* @return the output stream for the text
			*/
			static ::std::ostream& getStream();
#pragma endregion

		};
}



