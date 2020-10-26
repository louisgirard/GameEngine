#include <Games/Demo/Header/Demo.hpp>

namespace Games {

#pragma region INITIALIZATION
	 const std::string Demo::FILTER = "Filter";
	 const std::string Demo::GAUSSIAN = "Gaussian";

	 void Demo::initGame()
	 {
		// 0 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
			ShaderServer::getSingleton()->loadAndRegisterShader(GraphicEngine::ShaderProgramType::VFX, FILTER, "filter.vert", "filter.frag");
			ShaderServer::getSingleton()->loadAndRegisterShader(GraphicEngine::ShaderProgramType::VFX, GAUSSIAN, "filter.vert", "gauss.frag");
		}

		// 2 - We load the meshes
		{
			std::cout << "Init 2 - Loading Mesh " << std::endl;
			std::filesystem::path meshPath = Games::dataPath() / "lake"  / "lake.dae";
			_sceneRoot->addSon(SceneServer::getSingleton()->load(meshPath, true));
		}

		// 3 - We modify the parameters of the camera based on the bounding box
		std::cout << "Init 3 - Computing scene bounding box " << std::endl;
		BoundingBox envBB = _sceneRoot->computeSceneBoundingBox();
		glm::vec3 cameraPosition = glm::vec3(envBB.min().x + envBB.extent().x * 0.5, envBB.min().y + envBB.extent().y * 0.5, envBB.max().z);
		_camera.setPosition(cameraPosition);
		_cameraSpeed = glm::length(glm::vec2(envBB.extent())) / 40.0f;

		// 4 - We initialize multi-pass rendering
		std::cout << "Init 4 - Initialising multi-rendering " << std::endl;
		std::cout << "Filter shader" << std::endl;
		std::vector<std::tuple<FBOAttachment, FBOAttachmentType, TextureInternalFormat>> configuration;
		configuration.push_back(std::tuple(FBOAttachment::colorAttachment0, FBOAttachmentType::texture, TextureInternalFormat::rgba));
		configuration.push_back(std::tuple(FBOAttachment::depthAttachment, FBOAttachmentType::texture, TextureInternalFormat::depth));
		ShaderServer::getSingleton()->initVFX(FILTER, configuration, getConfiguration().getWindowWidth(), getConfiguration().getWindowHeight());

		std::cout << "Gaussian shader" << std::endl;
		std::vector<std::tuple<FBOAttachment, FBOAttachmentType, TextureInternalFormat>> configuration2;
		configuration2.push_back(std::tuple(FBOAttachment::colorAttachment0, FBOAttachmentType::texture, TextureInternalFormat::rgba));
		ShaderServer::getSingleton()->initVFX(GAUSSIAN, configuration2, getConfiguration().getWindowWidth(), getConfiguration().getWindowHeight());

		// 5 - We create a sub menu for the clipping distance
		std::cout << "Init 5 - Creating menu " << std::endl;
		GameMenu* menu = new GameMenu("Clipping distance");
		float extent = glm::length(envBB.extent());
		menu->addItem("10% extent", [this, extent]() {_clippingDistance = 0.1f * extent; });
		menu->addItem("20% extent", [this, extent]() {_clippingDistance = 0.2f * extent; });
		menu->addItem("30% extent", [this, extent]() {_clippingDistance = 0.3f * extent; });
		menu->addItem("40% extent", [this, extent]() {_clippingDistance = 0.4f * extent; });
		menu->addItem("50% extent", [this, extent]() {_clippingDistance = 0.5f * extent; });
		menu->addItem("60% extent", [this, extent]() {_clippingDistance = 0.6f * extent; });
		menu->addItem("70% extent", [this, extent]() {_clippingDistance = 0.7f * extent; });
		menu->addItem("80% extent", [this, extent]() {_clippingDistance = 0.8f * extent; });
		menu->addItem("90% extent", [this, extent]() {_clippingDistance = 0.9f * extent; });
		menu->addItem("100% extent", [this, extent]() {_clippingDistance = extent; });
		getMenu()->addSubMenu(menu);
		_clippingDistance = extent;
	}
#pragma endregion

	 void Demo::reshape(GLint p_width, GLint p_height) {
		 GameBase::reshape(p_width, p_height);
		 ShaderServer::getSingleton()->resizeScreen(p_width, p_height);
	 }

	 void Demo::handleInput(double p_dt) {
		 GameBase::handleInput(p_dt);
	 }

	 Demo::~Demo()
	 {
		 delete _sceneRoot;
		 ShaderServer::getSingleton()->clear();
		 SceneServer::getSingleton()->clear();
	 }

	 void Demo::updateFrame(){
		 GameBase::updateFrame();

		 ShaderProgram* currentShader = nullptr; 

		 // 0 - Matrices and initialisations
		 glm::mat4 projectionMatrix = glm::perspective(glm::radians<float>(90), (float)getConfiguration().getWindowWidth() / (float)getConfiguration().getWindowHeight(), 0.01f, _clippingDistance);
		 glm::mat4 viewMatrix = _camera.getInverseTransform();
		 // View matrix that only gets the rotation from the view 
		 glm::mat4 noTranslationMatrix = glm::mat4(glm::mat3(viewMatrix));
		
		 glm::vec3 lightDirection = glm::normalize(glm::vec3(0.4f, -0.3f, -1.0f));
		 glm::vec3 lightColor = glm::vec3(1, 1, 1);
		 GLenum textAttachment = GL_COLOR_ATTACHMENT0;


		 // 1 - Bind Frame Buffer to render
		 ShaderServer::getSingleton()->bindScreenTo(FILTER, FBOAttachment::colorAttachment0);

		 // 2 - We draw the skybox
		 ShaderServer::getSingleton()->renderSkybox(noTranslationMatrix, projectionMatrix);


		 // 3 - We draw the scene
		 {
			 std::string shaderUsed = ShaderServer::getSingleton()->getDefaultMeshShader();
			 ShaderServer::getSingleton()->use(shaderUsed, currentShader);
			 // We initialize the uniforms shared by every mesh
			 ((MeshShader*)currentShader)->setProjectionTransform(projectionMatrix);
			 ((MeshShader*)currentShader)->setViewTransform(viewMatrix);
			 ((MeshShader*)currentShader)->setViewPosition(_camera.getPosition());
			 ((MeshShader*)currentShader)->setLights(lightDirection, lightColor);
			 ((MeshShader*)currentShader)->setClippingDistance(_clippingDistance);
			 ((MeshShader*)currentShader)->setEnvTexture(ShaderServer::getSingleton()->getSkyboxTexture());
			 // We draw the mesh related to this shader 
			 _sceneRoot->draw(shaderUsed);
			 ShaderServer::getSingleton()->unuse(currentShader);
		 }

		 
		 // 4 - Binding Gaussian Frame Buffer
		 ShaderServer::getSingleton()->bindScreenTo(GAUSSIAN, FBOAttachment::colorAttachment0);

		 // 5 - Filter
		 const Texture2D* depthTexture;
		 {
			 ShaderServer::getSingleton()->use(FILTER, currentShader);
			 
			 currentShader -> trySetUniform("uni_degrade", 10.0f);
			 currentShader ->trySetUniform("uni_indice", 1.6f);
			 depthTexture = ((VFXShader*)currentShader)->renderScreen();

			 ShaderServer::getSingleton()->unuse(currentShader);
		 }

		 // 6 - Binding original Frame Buffer
		 ShaderServer::getSingleton()->unbindsScreen();

		 // 7 - Gaussian Filter
		 {
			 ShaderServer::getSingleton()->use(GAUSSIAN, currentShader);
			 
			 currentShader->trySetUniform("uni_width", 5);
			 ((VFXShader*)currentShader)->setDepthTexture(depthTexture);
			 ((VFXShader*)currentShader)->renderScreen();

			 ShaderServer::getSingleton()->unuse(currentShader);
		 }
	 }

}