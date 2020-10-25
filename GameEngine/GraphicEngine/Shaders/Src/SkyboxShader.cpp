#include <GraphicEngine/Shaders/Header/SkyboxShader.hpp>

namespace GraphicEngine::Shaders {
		const std::string SkyboxShader::CUBE_MAP = "uni_skybox";
		const std::string SkyboxShader::VIEW = "uni_mat_view";
		const std::string SkyboxShader::PROJECTION = "uni_mat_projection";

#pragma region INITIALIZATION
		/* Init this shader */
		void SkyboxShader::initialise() {

			_uniViewMatrix = getUniformLocation(VIEW);
			_uniProjectionMatrix = getUniformLocation(PROJECTION);
	
			_uniskybox = getUniformLocation(CUBE_MAP);
		}

		SkyboxShader::SkyboxShader() : ShaderProgram(defaultSkyboxVertex(), defaultSkyboxFragment()) {
			initialise();
			_texture = new Textures::CubeMap(defaultSkyboxTextures());
		}

		SkyboxShader::SkyboxShader(const Shader& p_vertex, const Shader& p_fragment)
			: ShaderProgram(p_vertex, p_fragment) {
			initialise();
			_texture = new Textures::CubeMap(defaultSkyboxTextures());
		}

		SkyboxShader::SkyboxShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath)
			: ShaderProgram(p_vertexPath, p_fragmentPath) {
			initialise();
			_texture = new Textures::CubeMap(defaultSkyboxTextures());
		}
#pragma endregion
		SkyboxShader::~SkyboxShader() {
			delete _texture;
		}

		void SkyboxShader::render() {
			_texture->associateWithTextureUnit(0);
			if (_uniskybox != -1) setUniform(_uniskybox, 0);
			SceneBase::SkyboxGeometry::getSingleton()->render(0);
		}

#pragma region COPY
		SkyboxShader::SkyboxShader(SkyboxShader&& p_other) :ShaderProgram(std::move(p_other))
		{

			_uniViewMatrix = p_other._uniViewMatrix;
			_uniProjectionMatrix = p_other._uniProjectionMatrix; 
			_uniskybox = p_other._uniskybox;

			_texture = p_other._texture;
		}

		SkyboxShader& SkyboxShader::operator= (SkyboxShader&& p_other)
		{
			ShaderProgram::operator=(std::move(p_other));

			if (isValid()) {
				_uniViewMatrix = p_other._uniViewMatrix;
				_uniProjectionMatrix = p_other._uniProjectionMatrix;
				_uniskybox = p_other._uniskybox;

				_texture = p_other._texture;
			}

			return (*this);
		}
#pragma endregion

#pragma region GETTERS
		Textures::CubeMap* SkyboxShader::getTexture() const {
			return _texture;
		}
#pragma endregion

#pragma region SETTERS
		void SkyboxShader::setTransforms(const glm::mat4& p_view, const glm::mat4& p_projection) {
			if (_uniViewMatrix != -1) { setUniform(_uniViewMatrix, p_view); }
			if (_uniProjectionMatrix != -1) { setUniform(_uniProjectionMatrix, p_projection); }
		}

		void SkyboxShader::setTexture(Textures::CubeMap* p_texture) {
			delete _texture;
			_texture = p_texture;
		}
#pragma endregion
}