#ifndef _Games_GameBase_H
#define _Games_GameBase_H

#include <iostream>
#include <thread>
#include <Games/Header/GameConfiguration.h>
#include <chrono>

#define NANO_TO_SECOND 0.000000001;

namespace Games {
	class GameBase
	{
	
	private:
		static GameBase* s_activeInstance;
		std::chrono::steady_clock::time_point _lastFrameTime;
		double _dt;
		bool _running;
	
		double computeDt();

		/**
		* Display last computed frame
		*
		**/
		void displayLastFrame();

		void runGameInConsole();

	protected:

		GameConfiguration _configuration;

		void virtual initGame() = 0;

		void virtual update(double p_dt) = 0;

	public:
	
		GameBase(GameConfiguration const& p_configuration = GameConfiguration());

		virtual ~GameBase();

		void launch();

		/*private:

		static bool s_initialized;
		static Base * s_activeInstance;
		tbb::tick_count m_lastFrameTime;
		double m_dt;


		static void displayCallback();

		static void reshapeCallback(GLint width, GLint height);

		static void keyboardCallback(unsigned char key, int x, int y);

		static void keyboardUpCallback(unsigned char key, int x, int y);

		static void mouseCallback(int button, int state, int x, int y);

		static void mouseMotionCallback(int x, int y);

		static void mousePassiveMotionCallback(int x, int y);

		static void closeCallback();

		static void registerCallbacks();

		void createWindow();

		static void initializeGLEW();

		void initializeOpenGL();


	private:

		void display();

	public:

		struct Configuration
		{
			typedef enum { FpsMax = 0, Fps60 = 1, Fps30 = 2 } FPS;

			/// \brief	Name of the window.
			::std::string m_windowName;
			/// \brief	The display mode, default is GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE.
			GLuint m_displayMode;
			/// \brief	The width of the window
			unsigned int width;
			/// \brief	The height of the window
			unsigned int height;
			/// \brief	Targetted frame rate. The frame rate will never be greater than the provided value (see FPS enum type).
			FPS m_fps;
			/// \brief	Distance of the near clipping plane.
			GLfloat m_nearPlane;
			/// \brief	Distance of the far clipping plane.
			GLfloat m_farPlane;
			/// \brief	Angle of the field of view.
			GLfloat m_fovy;

			Configuration()
				: m_windowName("OpenGL Application"), m_displayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE),
				width(Config::defaultWindowWidth), height(Config::defaultWindowHeight), m_fps(FpsMax),
				m_nearPlane(Config::defaultNearPlane), m_farPlane(Config::defaultFarPlane), m_fovy(Config::defaultFovy)
			{}
		};

	protected:
		Configuration m_configuration;
		int m_windowId;
		unsigned int m_lastTime;
		/// \brief Frame per second
		float m_fps;
		/// \brief	true to draw FPS.
		bool m_drawFPS;
		/// \brief	The main menu.
		Menu * m_mainMenu;
		/// \brief	The FPS menu.
		Menu * m_fpsMenu;
		/// \brief Functions that should be called when the window closes.
		::std::vector<::std::function<void()> > m_onCloseFunctions;


		static Base * getActiveApplication()
		{
			return s_activeInstance;
		}


		virtual void initializeRendering() = 0;

		virtual void render(double dt) = 0;


		virtual void keyPressed(unsigned char key, int x, int y) {}

		virtual void keyReleased(unsigned char key, int x, int y) {}

		virtual void mouse(int button, int state, int x, int y) {}

		virtual void mouseMotion(int x, int y) {}

		virtual void mousePassiveMotion(int x, int y) {}

		virtual void reshape(GLint width, GLint height);

	public:
		static void initializeGLUT(int & argc, char ** argv);

		Base(Configuration const & configuration = Configuration());

		virtual ~Base();

		void run();

		void quit()
		{
			// We ask to leave the main loop
			glutLeaveMainLoop();
			// Forces re-intialization of GLUT
			s_initialized = false;
		}

		void drawFPS(bool draw) { m_drawFPS = draw; }

		Menu * getMenu() { return m_mainMenu; }

		void onClose(::std::function<void()> const & function)
		{
			m_onCloseFunctions.push_back(function);
		}


		double getDt() const
		{
			return m_dt;
		}

		const Configuration & getConfiguration() const
		{
			return m_configuration;
		}*/
	};
}

#endif