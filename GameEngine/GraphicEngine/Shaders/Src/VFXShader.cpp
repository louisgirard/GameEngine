#include <GraphicEngine/Shaders/Header/VFXShader.hpp>

namespace GraphicEngine::Shaders {

		const std::string VFXShader::TEXTURE0 = "uni_texture";
		const std::string VFXShader::TEXTURE1 = "uni_texture1";
		const std::string VFXShader::TEXTURE2 = "uni_texture2";
		const std::string VFXShader::TEXTURE3 = "uni_texture3";
		const std::string VFXShader::TEXTURE4 = "uni_texture4";
		const std::string VFXShader::TEXTURE5 = "uni_texture5";
		const std::string VFXShader::TEXTURE6 = "uni_texture6";
		const std::string VFXShader::TEXTURE7 = "uni_texture7";
	

		const std::string VFXShader::DEPTH_TEXTURE = "uni_depthTexture";
		const std::string VFXShader::STENCIL_TEXTURE = "uni_stencilTexture";
		const std::string VFXShader::DEPTH_STENCIL_TEXTURE = "uni_stencilDepthTexture";

#pragma region INITIALIZATION
		/* Init this shader */
		void VFXShader::initialise() {

			 _uniText0 = getUniformLocation(TEXTURE0);
			 _uniText1 = getUniformLocation(TEXTURE1);
			 _uniText2 = getUniformLocation(TEXTURE2);
			 _uniText3 = getUniformLocation(TEXTURE3);
			 _uniText4 = getUniformLocation(TEXTURE4);
			 _uniText5 = getUniformLocation(TEXTURE5);
			 _uniText6 = getUniformLocation(TEXTURE6);
			 _uniText7 = getUniformLocation(TEXTURE7);

			 _uniDepth = getUniformLocation(DEPTH_TEXTURE);
			 _uniStencil = getUniformLocation(STENCIL_TEXTURE);
			 _uniDepthStencil = getUniformLocation(DEPTH_STENCIL_TEXTURE);
		}


		VFXShader::VFXShader(const Shader& p_vertex, const Shader& p_fragment)
			: ShaderProgram(p_vertex, p_fragment), _framesBuffer(nullptr){
			initialise();
		}

		VFXShader::VFXShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath)
			: ShaderProgram(p_vertexPath, p_fragmentPath), _framesBuffer(nullptr) {
			initialise();
		}
#pragma endregion

		VFXShader::~VFXShader() {
			delete _framesBuffer;
		}

		const Textures::Texture2D* VFXShader::renderScreen() {
			// Binding texture and set as uniform
			if (_uniText0 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment0)->associateWithTextureUnit(0);
				setUniform(_uniText0, 0);
			}
			if (_uniText1 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment1)->associateWithTextureUnit(0);
				setUniform(_uniText1, 0);
			}
			if (_uniText2 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment2)->associateWithTextureUnit(0);
				setUniform(_uniText2, 0);
			}
			if (_uniText3 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment3)->associateWithTextureUnit(0);
				setUniform(_uniText3, 0);
			}
			if (_uniText4 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment4)->associateWithTextureUnit(0);
				setUniform(_uniText4, 0);
			}
			if (_uniText5 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment5)->associateWithTextureUnit(0);
				setUniform(_uniText5, 0);
			}
			if (_uniText6 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment6)->associateWithTextureUnit(0);
				setUniform(_uniText6, 0);
			}
			if (_uniText7 != -1) {
				_framesBuffer->getTexture(FBOAttachement::colorAttachment7)->associateWithTextureUnit(0);
				setUniform(_uniText7, 0);
			}

			// Render the screen
			glDisable(GL_DEPTH_TEST);
			SceneBase::ScreenRenderQuad::getSingleton()->render(0, 1);
			glEnable(GL_DEPTH_TEST);

			return _framesBuffer->getTexture(FBOAttachement::depthAttachment);
		}

#pragma region COPY
		VFXShader::VFXShader(VFXShader&& p_other) :ShaderProgram(std::move(p_other))
		{
			_uniText0 = p_other._uniText0;
			_uniText1 = p_other._uniText1;
			_uniText2 = p_other._uniText2;
			_uniText3 = p_other._uniText3;
			_uniText4 = p_other._uniText4;
			_uniText5 = p_other._uniText5;
			_uniText6 = p_other._uniText6;
			_uniText7 = p_other._uniText7;

			_uniDepth = p_other._uniDepth;
			_uniStencil = p_other._uniStencil;
			_uniDepthStencil = p_other._uniDepthStencil;

			_framesBuffer = p_other._framesBuffer;
		}

		VFXShader& VFXShader::operator= (VFXShader&& p_other)
		{
			ShaderProgram::operator=(std::move(p_other));

			if (isValid()) {
				_uniText0 = p_other._uniText0;
				_uniText1 = p_other._uniText1;
				_uniText2 = p_other._uniText2;
				_uniText3 = p_other._uniText3;
				_uniText4 = p_other._uniText4;
				_uniText5 = p_other._uniText5;
				_uniText6 = p_other._uniText6;
				_uniText7 = p_other._uniText7;

				_uniDepth = p_other._uniDepth;
				_uniStencil = p_other._uniStencil;
				_uniDepthStencil = p_other._uniDepthStencil;

				_framesBuffer = p_other._framesBuffer;
			}

			return (*this);
		}
#pragma endregion

#pragma region BUFFER_OPERATION
		void VFXShader::initFrameBuffer(std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> p_configuration, size_t p_width, size_t p_height) {
			_framesBuffer = new Buffers::FrameBuffer(p_configuration, p_width, p_height);
		}

		void  VFXShader::resize(size_t p_width, size_t p_height) {
			_framesBuffer->resize(p_width, p_height);
		}

		void VFXShader::bindScreenTo(FBOAttachement p_attachment) const {
			_framesBuffer->bind();
			GLenum attach = static_cast<GLenum>(p_attachment);
			glDrawBuffers(1, &attach);
			glFlush();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
#pragma endregion

#pragma region SETTERS
		void VFXShader::setDepthTexture(const Textures::Texture2D* p_texture) {
			if (_uniDepth != -1 && p_texture != nullptr) {
				p_texture->associateWithTextureUnit(8);
				setUniform(_uniDepth,8);
			}	
		}
#pragma endregion
}