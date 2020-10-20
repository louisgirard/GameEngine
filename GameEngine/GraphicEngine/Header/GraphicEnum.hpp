#pragma once

#include <GL/glew.h>

namespace GraphicEngine {


	/*
	* Update frequency of usages for this buffer
	*/
	enum class BufferUpdate : GLenum {
		/*The vertex buffer is never updated*/
		staticDraw = GL_STATIC_DRAW,
		/*The vertex buffer is not frequently updated*/
		dynamicDraw = GL_DYNAMIC_DRAW,
		/*The vertex buffer is updated at every frame*/
		streamDraw = GL_STREAM_DRAW
	};

	/* Type of a shader */
	enum class ShaderType : GLenum {
		/* A vertex shader */
		vertexShader = GL_VERTEX_SHADER,
		/* A fragment shader */
		fragmentShader = GL_FRAGMENT_SHADER,
		/* A geometry shader */
		geometryShader = GL_GEOMETRY_SHADER
	};

	/*
	* Mapping of the OpenGL scalar type.
	* Spec related to this type is found via a GLMTypeSpec. 
	*/
	enum class GlType : GLenum {
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT
	};

	/*
	* The texture wrapping targer
	*/
	enum class TextureWrappingTarget : GLenum {
		/* The s texture coordinate */
		wrapS = GL_TEXTURE_WRAP_S,
		/* The t texture coordinate */
		wrapT = GL_TEXTURE_WRAP_T,
		/* The r texture coordinate */
		wrapR = GL_TEXTURE_WRAP_R
	};

	/*
	* The texture filter mode targets
	*/
	enum class TextureFilterTarget : GLenum {
		/* Texture minifying */
		minFilter = GL_TEXTURE_MIN_FILTER,
		/* Texture magnifying */
		magFilter = GL_TEXTURE_MAG_FILTER
	};

	/*
	* The texture wrapping modes
	*/
	enum class TextureWrappingMode : GLenum {
		/* Repeats the texture */
		repeat = GL_REPEAT,
		/* Repeats the texture but mirrored */
		mirroredRepeat = GL_MIRRORED_REPEAT,
		/* Clamps the texture on the edge */
		clampToEdge = GL_CLAMP_TO_EDGE,
		/* Clamps the texture on the edge and gives the border color */
		clampToBorder = GL_CLAMP_TO_BORDER
	};

	/*
	* Texture filter mode
	*/
	enum class TextureFilterMode : GLenum {
		/* Nearest pixel */
		nearest = GL_NEAREST,
		/* Linear pixel interpolation */
		linear = GL_LINEAR,
		/* Nearest pixel and nearest mipmap interpolation */
		nearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		/* Linear pixel and nearest mipmap interpolation */
		linearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		/* Nearest pixel and linear mipmap interpolation */
		nearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		/* Linear pixel and linear mipmap interpolation */
		linearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
	};

	/*
	*  The internal texture formats 
	*/
	enum class TextureInternalFormat : GLenum {
		depth = GL_DEPTH_COMPONENT,
		depth16 = GL_DEPTH_COMPONENT16,
		depth32 = GL_DEPTH_COMPONENT32,
		depthStencil = GL_DEPTH_STENCIL,

		red = GL_RED,
		rg = GL_RG,
		rgb = GL_RGB,
		rgba = GL_RGBA,

		r16f = GL_R16F,
		rg16f = GL_RG16F,
		rgb16f = GL_RGB16F,
		rgba16f = GL_RGBA16F,

		r32f = GL_R32F,
		rg32f = GL_RG32F,
		rgb32f = GL_RGB32F,
		rgba32f = GL_RGBA32F,

		r32ui = GL_R32UI,
		rg32ui = GL_RG32UI,
		rgb32ui = GL_RGB32UI,
		rgba32ui = GL_RGBA32UI
	};



}