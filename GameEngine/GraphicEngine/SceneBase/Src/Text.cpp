#include <GraphicEngine/SceneBase/Header/Text.hpp>

namespace GraphicEngine::SceneBase {
		std::stringstream* Text::s_out = new ::std::stringstream;

		void Text::display(GLfloat p_x, GLfloat p_y, const Materials::Color& p_color)
		{
			// Gets number of character per char
			int nbCharPerLine = glutGet(GLUT_WINDOW_WIDTH) / 12;
			// Init each line
			char* line = new char[nbCharPerLine + 1];
			// Write each line in openGL
			while (s_out->getline(line, nbCharPerLine + 1))
			{
				display(p_x, p_y, line, p_color);
				p_y += 12.0;
			}
			// Trick to reset the stringstream 
			delete s_out;
			s_out = new ::std::stringstream;

			// Release memory
			delete[] line;
		}

		void Text::display(GLfloat p_x, GLfloat p_y, const ::std::string& p_text, const Materials::Color& p_color = Materials::Color(0.0, 1.0, 0.5))
		{
			// Save and disable render option so that the text does not get affected by those 
			glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);

			// Set the projection view in orthographic mode 
			setOrthographicProjection();

			glPushMatrix();
			glLoadIdentity();
			// Write text at specified position (from the current mv matrix)
			glColor3f(p_color.getBuffer()[0], p_color.getBuffer()[1], p_color.getBuffer()[2]);
			glRasterPos2f(p_x, p_y);
			for (size_t cpt = 0; cpt < p_text.size(); ++cpt)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, p_text[cpt]);
			}

			// Gets back previous openGL configuration
			glPopMatrix();
			resetOrthographicProjection();
			glPopAttrib();
		}

#pragma region ORTHOGRAPHIC_MODE
		void Text::setOrthographicProjection()
		{
			// Bind the projection matrix
			glMatrixMode(GL_PROJECTION);
			// Push current projection matrix to save it
			glPushMatrix();
			// Reset matrix
			glLoadIdentity();
			// Sets the matrix in orthographic mode
			gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
			glScalef(1, -1, 1);
			glTranslatef(0.0f, (float)-glutGet(GLUT_WINDOW_HEIGHT), 0.0f);
			// Bind the MV matrix
			glMatrixMode(GL_MODELVIEW);
		}

		void Text::resetOrthographicProjection()
		{
			// Get back the current matrix
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
#pragma endregion

#pragma region GETTER
		::std::ostream& Text::getStream() {
			return *s_out;
		}
#pragma endregion
}