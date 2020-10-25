#pragma once

#include <GraphicEngine/SceneBase/Header/ScreenRenderQuad.hpp>
#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>
#include <GraphicEngine/Buffers/Header/FrameBuffer.hpp>

namespace GraphicEngine::Shaders {
		class VFXShader : public ShaderProgram
		{
		protected:

			Buffers::FrameBuffer* _framesBuffer;

			/* Save the attribute default name for a vfx shader */
			static const std::string TEXTURE0, TEXTURE1, TEXTURE2, TEXTURE3, TEXTURE4, TEXTURE5, TEXTURE6, TEXTURE7;
			static const std::string DEPTH_TEXTURE, STENCIL_TEXTURE, DEPTH_STENCIL_TEXTURE;

			/* Saves the attribute identifier */
			GLint _uniText0, _uniText1, _uniText2, _uniText3, _uniText4, _uniText5, _uniText6, _uniText7;
			GLint _uniDepth, _uniStencil, _uniDepthStencil;

#pragma region INITIALIZATION
			/* Init this shader */
			void initialise();
#pragma endregion

		public:
#pragma region INITIALIZATION
			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertex : Vertex shader to attach to this program
			* @param p_fragment : Fragment shader to attach to this program
			*/
			VFXShader(const Shader& p_vertex, const Shader& p_fragment);

			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertexPath : Path to the vertex shader to attach to this program
			* @param p_fragmentPath : Path ot the fragment shader to attach to this program
			*/
			VFXShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath);
#pragma endregion

			/* Destructor */
			~VFXShader();

			/*
			* Render screen 
			* @return the depth texture rendered in this pass if there is any, a null pointer else
			*/
			const Textures::Texture2D* renderScreen();

#pragma region COPY
			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			VFXShader(VFXShader&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			virtual VFXShader& operator= (VFXShader&& p_other);

#pragma endregion

#pragma region BUFFER_OPERATION
			/*
			* Initialise the frame buffer
			* @param p_configuration : The configuration of each channel of the frame buffer
			* @param p_width : Width of the buffer
			* @param p_height : Height of the buffer
			*/
			void initFrameBuffer(std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> p_configuration, size_t p_width, size_t p_height);

			/*
			* Resize the frame buffer
			* @param p_width :New width
			* @param p_height : New height
			*/
			void resize(size_t p_width, size_t p_height);

			/*
			* Binds the screen to an attachment of the frame buffer
			* @param p_attachment : The attachment of the frame buffer to bind to
			*/
			void bindScreenTo(FBOAttachement p_attachment) const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the buffer texture
			* Buffer texture must have been filled prior to this operation
			* @param p_texture : New depth texture
			*/
			void setDepthTexture(const Textures::Texture2D* p_texture);
#pragma endregion
		};
}


