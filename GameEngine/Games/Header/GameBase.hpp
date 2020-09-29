#ifndef _Games_GameBase_H
#define _Games_GameBase_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>

//Glew needs to be included before any other file that contains gl.h 
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Games/Header/GameConfiguration.hpp>
#include <Games/Header/KeyboardStatus.hpp>
#include <Games/Header/GameMenu.hpp>
#include <Games/Header/KeyAction.hpp>
#include <GraphicEngine/Header/Camera.hpp>
#include <PhysicEngine/Header/MathConstant.hpp>
#include <Games/Header/MouseStatus.hpp>

#define NANO_TO_SECOND 0.000000001;

namespace Games {
	class GameBase
	{
	
	private:
		static GameBase* s_activeInstance;
		static bool s_glutInitialized;
		static bool s_glewInitialized;

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

		void createGameWindow();

		void initializeGlew();

		void initializeOpenGL();

		static void displayCallback();

		static void reshapeCallback(GLint width, GLint height);

		static void keyboardCallback(unsigned char key, int x, int y);

		static void keyboardUpCallback(unsigned char key, int x, int y);

		static void keyboardSpecialCallback(int key, int x, int y);

		static void keyboardSpecialUpCallback(int key, int x, int y);

		static void mouseCallback(int button, int state, int x, int y);

		static void mouseMotionCallback(int x, int y);

		static void mousePassiveMotionCallback(int x, int y);

		static void closeCallback();

		static void registerGLUTCallback();

	protected:

		int _windowID;
		GameConfiguration _configuration;
		/// Functions that should be called when the window closes.
		::std::vector<::std::function<void()> > _onCloseFunctions;

		KeyboardStatus _keyboard;
		MouseStatus _mouse;

		GameMenu* _mainMenu;

		GraphicEngine::Camera _camera;
		float _cameraSpeed, _cameraRotationSpeed;

		void virtual initGameConfig() {}

		void virtual initGame() = 0;

		void virtual handleInput();

		void virtual updatePhysic(double p_dt) = 0;

		void virtual updateFrame();

		virtual void reshape(GLint width, GLint height);

		virtual void keyPressed(unsigned char key, int x, int y);

		virtual void keyReleased(unsigned char key, int x, int y);

		virtual void specialKeyPressed(unsigned char key, int x, int y);

		virtual void specialKeyReleased(unsigned char key, int x, int y);

		virtual void mouse(int button, int state, int x, int y) {}

		virtual void mouseMotion(int x, int y) {}

		virtual void mousePassiveMotion(int x, int y);

		static GameBase* getActiveApplication();

	public:
	
		GameBase();

		virtual ~GameBase();

		static void initializeGLUT(int& p_argc, char** p_argv);

		void launch();

		void quit();

		void onClose(::std::function<void()> const& function);	

		double getDt() const;

		const GameConfiguration& getConfiguration() const;

		GameMenu* getMenu(); 
	};
}

#endif