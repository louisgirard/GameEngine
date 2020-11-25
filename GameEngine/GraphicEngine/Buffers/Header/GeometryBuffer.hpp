#ifndef _GRAPHIC_ENGINE_GEOMETRY_BUFFER_HPP_
#define _GRAPHIC_ENGINE_GEOMETRY_BUFFER_HPP_

#include <GraphicEngine/Buffers/Header/FrameBuffer.hpp>
#include <vector>

namespace GraphicEngine::Buffers {
		class GeometryBuffer : public FrameBuffer
		{
			/* Color attachment 0 : positions (usually in world coordinates)  [RGB32F] */
			const Textures::Texture2D* _positions;
			/* Color attachment 1 : normals (usually in world coordinates) [RGB32F] */
			const Textures::Texture2D* _normals;
			/* Color attachment 2 : diffuse color [RGBA] */
			const Textures::Texture2D* _diffuse;
			/* Color attachment 3 : specular color [RGBA] */
			const Textures::Texture2D* _specular;
			/* Color attachment 4 : z value [R32F] */
			const Textures::Texture2D* _depth;
			/* depth attachment : render buffer de type z buffer  */
			const RenderBuffer* _zbuffer;

			/*
			* Gets default buffer configuration
			* @return default buffer configuration
			*/
			static std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> configuration();

			/*
			* Update intern buffers attachments
			*/
			void updateAttachments();

		public:

			/*
			* Default constructor
			* Warning this shader is invalide
			*/
			GeometryBuffer():FrameBuffer(), _positions(nullptr), _normals(nullptr), _diffuse(nullptr), _specular(nullptr), _depth(nullptr), _zbuffer(nullptr){}

			/*
			* Constructor
			* @param p_width : Width of the screen
			* @param p_height : Height of the screen
			*/
			GeometryBuffer(size_t p_width, size_t p_height);

			/*
			* Resize the geometry buffer
			* @param p_width : New width
			* @param p_height : New height
			*/
			virtual void resize(size_t width, size_t height) override;

#pragma region COPY
			/*
			* Move constructor
			* @param p_other : buffer to move
			*/
			GeometryBuffer(GeometryBuffer&& p_other);

			/*
			*  Move assignment
			*  @param p_other : buffer to move
			*/
			virtual GeometryBuffer& operator= (GeometryBuffer&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Gets the position texture
			* @return position texture
			*/
			const Textures::Texture2D* getPositions() const;

			/*
			* Gets the normals texture
			* @return normals texture
			*/
			const Textures::Texture2D* getNormals() const;

			/*
			* Gets the diffuse texture
			* @return diffuse texture
			*/
			const Textures::Texture2D* getDiffuse() const;

			/*
			* Gets the specular texture
			* @return specular texture
			*/
			const Textures::Texture2D* getSpecular() const;

			/*
			* Gets the depth texture (warning, it has to be written)
			* @return depth texture
			*/
			const Textures::Texture2D* getDepth() const;

			/*
			* Gets z buffer
			* @return z buffer
			*/
			const RenderBuffer* getZBuffer() const;
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_GEOMETRY_BUFFER_HPP_



