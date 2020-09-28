#include <Games/Header/GameBase.hpp>

namespace Games
{
	GameBase* GameBase::s_activeInstance = nullptr;
	bool GameBase::s_glutInitialized = false;
	bool GameBase::s_glewInitialized = false;

	GameBase::GameBase():_configuration(),_dt(0.0),_lastFrameTime(), _running(false) {

		initGameConfig();
		//We only want one game to run at a time
		if (s_activeInstance != nullptr) {
			std::cout << "ERROR : you are trying to launch an instance of a game while another is already running " << std::endl;
			exit(-1);
		}
		s_activeInstance = this;
		if (_configuration.graphicEnabled()) {
			//if glut is not initialized the game can't be launched
			if (!s_glutInitialized)
			{
				::std::cerr << "You can't create a instane of GameBase before initiating GLUT with Games::GameBase" << ::std::endl;
				exit(-1);
			}
			createGameWindow();
			//Initialize Open GL related library
			initializeGlew();
			initializeOpenGL();
			//Register function that will be use in glut window
			registerGLUTCallback();

			_mainMenu = new GameMenu("Main menu");
			_mainMenu->activate(GLUT_RIGHT_BUTTON);

			//Bind basic key
			_keyboard.bindActionToKey(KeyAction::QUIT, 27);

			_keyboard.bindActionToSpecialKey(KeyAction::MOVEFRONT, GLUT_KEY_UP);
			_keyboard.bindActionToSpecialKey(KeyAction::MOVEBACK, GLUT_KEY_DOWN);
			_keyboard.bindActionToSpecialKey(KeyAction::MOVERIGHT, GLUT_KEY_RIGHT);
			_keyboard.bindActionToSpecialKey(KeyAction::MOVELEFT, GLUT_KEY_LEFT);
			_keyboard.bindActionToKey(KeyAction::MOVEUP, 'a');
			_keyboard.bindActionToKey(KeyAction::MOVEDOWN, 'e');

			_keyboard.bindActionToKey(KeyAction::ROTATERIGHT, 'd');
			_keyboard.bindActionToKey(KeyAction::ROTATELEFT, 'q');
			_keyboard.bindActionToKey(KeyAction::ROTATEUP, 'z');
			_keyboard.bindActionToKey(KeyAction::ROTATEDOWN, 's');

			//Init Camera
			_camera.setPosition(glm::vec3(0.0f, 0.0f, 0.5f));
			_cameraSpeed = 10.0f;
			_cameraRotationSpeed = (float)(PhysicEngine::PI / 5.0);

			onClose([this]() {	
				// We destroy the current window
				//glutDestroyWindow(_windowID) ;
				// We destroy the menus
				delete _mainMenu ;
				//Force reinit glut
				s_glutInitialized = false;
			} ) ;
			
		}
	}

	GameBase* GameBase::getActiveApplication()
	{
		return s_activeInstance;
	}

	const GameConfiguration& GameBase::getConfiguration() const
	{
		return _configuration;
	}

	GameMenu* GameBase::getMenu(){ return _mainMenu; }

	GameBase::~GameBase() {
		//As this instance die there is no more running instance
		s_activeInstance = nullptr;
	}

	void GameBase::launch() {
		initGame();

		_lastFrameTime = std::chrono::steady_clock::now();

		if (!_configuration.graphicEnabled()) {
			std::cout << "Launch console thread" << std::endl;
			_running = true;
			std::thread run (&GameBase::runGameInConsole, this);

			while (_running) {
				char command;
				std::cin >> command;
				if (command == 's') {
					_running = false;
				}
			}
			run.join();
		}
		else {
			//launch GLUT main loop
			glutMainLoop();
		}
	}

	void GameBase::quit()
	{
		// We ask to leave the main loop
		glutLeaveMainLoop();
		// Forces re-intialization of GLUT
		s_glutInitialized = false;
	}

	void GameBase::onClose(::std::function<void()> const& function)
	{
		_onCloseFunctions.push_back(function);
	}

	double  GameBase::getDt() const {
		return _dt;
	}

	double GameBase::computeDt() {
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		double dt = std::chrono::duration_cast<std::chrono::nanoseconds> (current - _lastFrameTime).count() * NANO_TO_SECOND;
		_lastFrameTime = current;
		return dt;
	}

	void GameBase::displayLastFrame() {
		// Get time passed between current and past frame
		_dt = computeDt();
		
		// Clears frame and z buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Reinit frame transformation
		glLoadIdentity();
		// Get Input event for this frame
		handleInput();
		// Update Game Physics
		updatePhysic(_dt);
		//Update Game Graphics
		updateFrame();
		// We ensure that no shader program is binded (Apparently could cause some issue
		glUseProgram(0);
		// Swaps rendering buffers, display this frame and prepare for the next
		glutSwapBuffers();
		// Asks for redisplay, which mean that in next iteration of the Glut main loop the displayCallback will be called
		glutPostRedisplay();
	}

	void GameBase::runGameInConsole() {
		while (_running)
		{
			_dt = computeDt();
			updatePhysic(_dt);
		}
	}

	void GameBase::handleInput() {

		glm::vec3 xAxis(1.0, 0.0, 0.0);
		glm::vec3 yAxis(0.0, 1.0, 0.0);

		// If we press escape, we close this game
		// ie: 27 is the unsigned char value of escape but if you want to use a more common letter
		// for instance e you could use _keyboard.isPressed('e').
		if (_keyboard.isPressed(KeyAction::QUIT)) {
			quit();
		}

		//Key Related to Translation Movement
		if (_keyboard.isPressed(KeyAction::MOVEFRONT)) {_camera.translateFront(_cameraSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::MOVEBACK)) {_camera.translateFront(-_cameraSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::MOVERIGHT)) { _camera.translateRight(_cameraSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::MOVELEFT)) { _camera.translateRight(-_cameraSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::MOVEUP)) { _camera.translateUp(_cameraSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::MOVEDOWN)) { _camera.translateUp(-_cameraSpeed * _dt); }

		//Key Related to Rotation Movement
		if (_keyboard.isPressed(KeyAction::ROTATELEFT)) { _camera.rotateLocal(yAxis, _cameraRotationSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::ROTATERIGHT)) { _camera.rotateLocal(yAxis, -_cameraRotationSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::ROTATEUP)) { _camera.rotateLocal(xAxis, _cameraRotationSpeed * _dt); }
		if (_keyboard.isPressed(KeyAction::ROTATEDOWN)) { _camera.rotateLocal(xAxis, -_cameraRotationSpeed * _dt); }
	}

	void GameBase::updateFrame() {
		// 1 - Update Camera
		// For now 
		glm::vec3 up = _camera.up();
		glm::vec3 position = _camera.getPosition();
		glm::vec3 referencePoint = position + _camera.lookingAt();

		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(&(_camera.getInverseTransform()[0][0]));
	}

	/*
	* Needs to call this function before creating a game 
	*/
	void GameBase::initializeGLUT(int& p_argc, char** p_argv) {
		if (!s_glutInitialized) {
			//from GLUT Library, freeglut file
			//Init connexion between GLUT and Windows
			glutInit(&p_argc, p_argv);
			//Tell GLUT to return from the main loop when the window is closed 
			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
			s_glutInitialized = true;
		}
	}
	
	void GameBase::initializeGlew() {
		if (!s_glewInitialized) {
			GLenum stateResult = glewInit();
			if (GLEW_OK != stateResult)
			{
				//Problem: glewInit failed, something is seriously wrong. 
				::std::cerr << "Failed to initializeGLUT GLEW: " << glewGetErrorString(stateResult) << ::std::endl;
				exit(-1);
			}
			s_glewInitialized = true;
		}
	}

	void GameBase::initializeOpenGL() {
		
		//Is not done once cause this parameter could be overwrite during a games to fit needs
		glEnable(GL_DEPTH_TEST); // Enables depth buffer
		glShadeModel(GL_SMOOTH); // Enables smooth shading model
		glEnable(GL_LIGHTING); // Enables lights
		glEnable(GL_CULL_FACE); // enables back face culling
		glCullFace(GL_BACK); // Specifies culling side (here back side)
		glFrontFace(GL_CCW); // Specifies polygon front face (here counter clock wise) 
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Specifies that the interpolation when correcting perspective should use the highest quality method
		glEnable(GL_NORMALIZE); // Enable normalizing normal vector automatically
		glLoadIdentity();

		glEnable(GL_COLOR_MATERIAL);
	}

	void GameBase::createGameWindow() {
		//from GLUT, freeglut class
		//Initialize a window of dimension given in the configuration variable
		glutInitWindowSize(_configuration.getWindowWidth(), _configuration.getWindowHeight());
		//Init a window displaying 
		glutInitDisplayMode(_configuration.getDisplayMode());
		//Create a window, get its ID and set its name from configuration
		_windowID = glutCreateWindow(_configuration.getName().c_str());
	}

	void GameBase::registerGLUTCallback() {
		//Register function used to display a frame
		glutDisplayFunc(displayCallback);
		//Register function used when the user reshape the game window
		glutReshapeFunc(reshapeCallback);
		//Register function to track keyboard and mouse event in the game
		glutKeyboardFunc(keyboardCallback); // function called when a key has been pressed 
		glutKeyboardUpFunc(keyboardUpCallback); // function called when a key has been released
		glutSpecialFunc(keyboardSpecialCallback); // Function called for special key
		glutSpecialUpFunc(keyboardSpecialUpCallback);
		glutMouseFunc(mouseCallback);
		glutPassiveMotionFunc(mousePassiveMotionCallback);
		//Register function called when the game is closed
		glutCloseFunc(closeCallback);

		
	}

	void GameBase::displayCallback()
	{
		s_activeInstance->displayLastFrame();
	}

	void GameBase::reshapeCallback(GLint width, GLint height)
	{
		s_activeInstance->reshape(width, height);
	}

	void GameBase::keyboardCallback(unsigned char key, int x, int y)
	{
		s_activeInstance->keyPressed(key, x, y);
	}

	void GameBase::keyboardUpCallback(unsigned char key, int x, int y)
	{
		s_activeInstance->keyReleased(key, x, y);
	}

	void GameBase::keyboardSpecialCallback(int key, int x, int y)
	{
		s_activeInstance->specialKeyPressed(key, x, y);
	}

	void GameBase::keyboardSpecialUpCallback(int key, int x, int y)
	{
		s_activeInstance->specialKeyReleased(key, x, y);
	}

	void GameBase::mouseCallback(int button, int state, int x, int y)
	{
		s_activeInstance->mouse(button, state, x, y);
	}

	void GameBase::mouseMotionCallback(int x, int y)
	{
		s_activeInstance->mouseMotion(x, y);
	}

	void GameBase::mousePassiveMotionCallback(int x, int y)
	{
		s_activeInstance->mousePassiveMotion(x, y);
	}

	void GameBase::closeCallback()
	{
		for (unsigned int cpt = 0; cpt < s_activeInstance->_onCloseFunctions.size(); ++cpt)
		{
			s_activeInstance->_onCloseFunctions[cpt]();
		}
	}

	void GameBase::reshape(GLint width, GLint height)
	{
		// Updates the view port size
		glViewport(0, 0, width, height);
		// Update Projection Matrix
		glMatrixMode(GL_PROJECTION); //Specifies the subsequent operation will affect the projection matrix
		glLoadIdentity(); // Replace current projection matrix by an identity matrix
		gluPerspective(_configuration.getFOV(), (float)width / height, _configuration.getNearPlane(), _configuration.getFarPlane()); //Create a new perspective projection matrix from our configuration frustum
		glMatrixMode(GL_MODELVIEW); //We come back to model matrix
		// Updates the configuration
		_configuration.setWindowDimension(width, height); 
	}
	
	void GameBase::keyPressed(unsigned char key, int x, int y) {
		_keyboard.press(key);
	}

	void GameBase::keyReleased(unsigned char key, int x, int y)
	{
		_keyboard.release(key);
	}

	void GameBase::specialKeyPressed(unsigned char key, int x, int y) 
	{
		_keyboard.pressSpecialKey(key);
	}

	void GameBase::specialKeyReleased(unsigned char key, int x, int y) 
	{
		_keyboard.releaseSpecialKey(key);
	}

}
