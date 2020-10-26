#ifndef _Games_GameBase_H
#define _Games_GameBase_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>

//Glew needs to be included before any other file that contains gl.h 
#include <GL/glew.h>

#include <Games/Header/PhysicEnabler.hpp>
#include <Games/Header/GraphicEnabler.hpp>
#include <Games/Header/SceneGraphEnabler.hpp>

#include <Games/Header/GameConfiguration.hpp>
#include <Games/Header/GameMenu.hpp>
#include <Games/Header/KeyboardStatus.hpp>
#include <Games/Header/MouseStatus.hpp>



/**Const used to define how to define a nanosecond**/
#define NANO_TO_SECOND 0.000000001;

namespace Games {
	class GameBase
	{
	private:
		/**Singleton used to ensure only one game is running at a time**/
		static GameBase* s_activeInstance;

		/**Variables used to keep track of initialisation step for the singleton's game**/
		static bool s_glutInitialized;
		static bool s_glewInitialized;

		/**Delta time between last and current frame**/
		double _dt;

		/**Time since last frame**/
		std::chrono::steady_clock::time_point _lastFrameTime;

		/**Boolean used to keep track of game states (Running or not)**/
		bool _running;
	
		/**
		* Compute delta time for current frame
		**/
		double computeDt();

#pragma region GAME_MAIN_LOOP

		/**
		* Display last computed frame on game window
		**/
		void displayLastFrame();

		/**
		* Run game without graphic background using the console to display information
		**/
		void runGameInConsole();
#pragma endregion

#pragma region GAME_INITIALISATION

		/**
		* Create a window for the game
		**/
		void createGameWindow();

		/**
		* Initialize openGL library
		**/
		void initializeOpenGL();

		/**
		* Initialize glew library
		**/
		void initializeGlew();
#pragma endregion

#pragma region GLUT_CALLBACK

		/**
		* Register every callback function in GLUT
		**/
		static void registerGLUTCallback();

		/**
		* Callback function used each time GLUT compute a new frame
		**/
		static void displayCallback();

		/**
		* Callback function used when the user reshape the game window
		* @param p_width : new window's width
		* @param p_height : new window's height
		**/
		static void reshapeCallback(GLint p_width, GLint p_height);

		/**
		* Callback function used when the user press a key and the cursor is inside the window
		* @param p_key : key that has been pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void keyboardCallback(unsigned char p_key, int p_x, int p_y);

		/**
		* Callback function used when the user release a key and the cursor is inside the window
		* @param p_key : key that has been released
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void keyboardUpCallback(unsigned char p_key, int p_x, int p_y);

		/**
		* Callback function used when the user press a special key and the cursor is inside the window.
		* Special keys are key that are not dealt with by <i>keyboardCallback</i> and registered as int in GLUT
		* @param p_key : key that has been pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void keyboardSpecialCallback(int p_key, int p_x, int p_y);

		/**
		* Callback function used when the user released a special key and the cursor is inside the window.
		* Special keys are key that are not dealt with by <i>keyboardCallback</i> and registered as int in GLUT
		* @param p_key : key that has been released
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void keyboardSpecialUpCallback(int p_key, int p_x, int p_y);

		/**
		* Callback function used to deal with mouse button event
		* @param p_button : button that changed state (either GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON) 
		* @param p_state : state of the button (GLUT_UP or GLUT_DOWN)
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void mouseCallback(int p_button, int p_state, int p_x, int p_y);

		/**
		* Callback function used to deal with mouse's motion when a mouse's button is pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void mouseMotionCallback(int p_x, int p_y);

		/**
		* Callback function used to deal with mouse's motion when no mouse's button is pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		static void mousePassiveMotionCallback(int p_x, int p_y);

		/**
		* Callback function called when a window is closed
		**/
		static void closeCallback();
#pragma endregion

	protected:

		/**ID of the game window in GLUT**/
		int _windowID;
		/**Current configuration for the game**/
		GameConfiguration _configuration;
		/**Registered function called when a window is closed**/
		::std::vector<::std::function<void()> > _onCloseFunctions;

		/**Current status of the keys on the keyboard**/
		KeyboardStatus _keyboard;
		/**Current mouse status**/
		MouseStatus _mouse;

		/**Root Menu in the Game **/
		GameMenu* _mainMenu;

		/**Game Camera**/
		Camera _camera;
		/**Speed used to compute camera's motion**/
		float _cameraSpeed, _cameraRotationSpeed;

#pragma region VIRTUAL_FUNCTION

		/**
		* Initialize the game configuration
		**/
		virtual void initGameConfig() {}

		/**
		* Initialize game state
		**/
		virtual void initGame() = 0;

		/**
		* Handle user's input callback
		**/
		virtual void handleInput(double p_dt);

		/**
		* Update game physics
		* @param p_dt : delta time since last frame
		**/
		virtual void updatePhysic(double p_dt) = 0;

		/**
		* Update game graphics
		**/
		virtual void updateFrame();

		/**
		* Function called when the user reshapes the game window
		* @param p_width : new window's width
		* @param p_height : new window's height
		**/
		virtual void reshape(GLint p_width, GLint p_height);

		/**
		* Function called when the user press a key and the cursor is inside the window
		* @param p_key : key that has been pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void keyPressed(unsigned char p_key, int p_x, int p_y);

		/**
		* Function called when the user release a key and the cursor is inside the window
		* @param p_key : key that has been released
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void keyReleased(unsigned char p_key, int p_x, int p_y);

		/**
		* Function called when the user press a special key and the cursor is inside the window.
		* Special keys are key that are not dealt with by <i>keyboardCallback</i> and registered as int in GLUT
		* @param p_key : key that has been pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void specialKeyPressed(unsigned char p_key, int p_x, int p_y);

		/**
		* Function called when the user released a special key and the cursor is inside the window.
		* Special keys are key that are not dealt with by <i>keyboardCallback</i> and registered as int in GLUT
		* @param p_key : key that has been released
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void specialKeyReleased(unsigned char p_key, int p_x, int p_y);

		/**
		* Function called to deal with mouse button event
		* @param p_button : button that changed state (either GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON)
		* @param p_state : state of the button (GLUT_UP or GLUT_DOWN)
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void mouse(int p_button, int p_state, int p_x, int p_y) {}

		/**
		* Function called to deal with mouse's motion when a mouse's button is pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void mouseMotion(int p_x, int p_y) {}

		/**
		* Function called to deal with mouse's motion when no mouse's button is pressed
		* @param p_x : position of the cursor in the window on the x axis
		* @param p_y : position of the cursor in the window on the y axis
		**/
		virtual void mousePassiveMotion(int p_x, int p_y){}

#pragma endregion

#pragma region GETTERS
		/**
		* Get the game currently running
		* @return the current running instance of a game
		**/
		static GameBase* getActiveApplication();
#pragma endregion 

	public:
	
		/*Default constructor*/
		GameBase();

		/*Default destructor*/
		virtual ~GameBase();

#pragma region GAME_INITIALISATION
		/**
		* Initialize GLUT library
		**/
		static void initializeGLUT(int& p_argc, char** p_argv);
#pragma endregion

#pragma region GETTERS
		/**
		* Get the delta time for the current frame
		* @return current delta time
		**/
		double getDt() const;

		/**
		* Get the game current configuration
		* @return the current configuration
		**/
		const GameConfiguration& getConfiguration() const;

		/**
		* Get the game root menu
		* @return the game root menu
		**/
		GameMenu* getMenu();
#pragma endregion
		
#pragma region EXTERNAL_ACTION
		/**
		* Launch an instance of the game
		**/
		void launch();

		/**
		* Quit the game
		**/
		void quit();

		/**
		* Add new actions for when the game will close
		**/
		void onClose(::std::function<void()> const& p_function);
#pragma endregion
	};
}

#endif