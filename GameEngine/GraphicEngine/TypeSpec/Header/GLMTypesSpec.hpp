#ifndef _GRAPHIC_ENGINE_GLM_TYPE_INFOS
#define _GRAPHIC_ENGINE_GLM_TYPE_INFOS

#include <glm/glm.hpp>

#include <GraphicEngine/Header/GraphicEnum.hpp>

namespace GraphicEngine {

	/* Info about a specific glm type 
	* Default struct, every type not compatible will be assigned with this values
	*/
	template <class T>
	struct GLMTypesSpec
	{
		
		/* The primitive type of the elements contained in the GLM data structure */
		using primitiveType = void;

		/*
		* Determines whether the provided type is compatible with this type specification.
		* @return true if the type T is compatible with this specification, else false
		*/
		static constexpr bool isCompatible() { return false; }

		/*
		* Returns the OpenGL type (enumerated value) corresponding to the primitiveType 
		* @returns openGL type for this primitive
		*/
		static constexpr GlType glType() { return GlType(GL_NONE); }

		/*
		* Number of elements in the data structure T.
		* @return the number of element in T
		*/
		static constexpr size_t size() { return 0; }

		/*
		* Returns the number of rows in the data structure T.
		* @return number of rows in T
		*/
		static constexpr size_t rows() { return 0; }

		/*
		* Returns the number of columns in the data structure T.
		* @return number of columns in T
		*/
		static constexpr size_t columns() { return 0; }

		/*
		* Determines whether the type T is a scalar.
		* @return true if T is a scalar, else false
		*/
		static constexpr bool isScalar() { return false; }

		/*
		* Determines whether the type T is a vector.
		* @return true if T is a vector, else otherwise
		*/
		static constexpr bool isVector() { return false; }

		/*
		* Determines whether the type T is a matrix.
		* @return true if T is a matrix, else false
		*/
		static constexpr bool isMatrix() { return false; }

		/*
		* Returns the texture internal format compatible with the type T.
		* @return compatible format with T
		*/
		static constexpr TextureInternalFormat glTextureFormat() { return TextureInternalFormat(GL_NONE); }
	};

	/* Spec for a GLfloat */
	template <>
	struct GLMTypesSpec<GLfloat>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 1; }
		static constexpr size_t rows() { return 1; }
		static constexpr size_t columns() { return 1; }
		static constexpr bool isScalar() { return true; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return false; }
		static constexpr TextureInternalFormat glTextureFormat() { return TextureInternalFormat::r32f; }
	};

#pragma region Vector
	/* Spec for a vec2 */
	template <>
	struct GLMTypesSpec<glm::vec2>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 2; }
		static constexpr size_t rows() { return 2; }
		static constexpr size_t columns() { return 1; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return true; }
		static constexpr bool isMatrix() { return false; }
		static constexpr TextureInternalFormat glTextureFormat() { return TextureInternalFormat::rg32f; }
	};

	/* Spec for a vec3 */
	template <>
	struct GLMTypesSpec<glm::vec3>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 3; }
		static constexpr size_t rows() { return 3; }
		static constexpr size_t columns() { return 1; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return true; }
		static constexpr bool isMatrix() { return false; }
		static constexpr TextureInternalFormat glTextureFormat() { return TextureInternalFormat::rgb32f; }
	};

	/* Spec for a vec4 */
	template <>
	struct GLMTypesSpec<glm::vec4>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 4; }
		static constexpr size_t rows() { return 4; }
		static constexpr size_t columns() { return 1; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return true; }
		static constexpr bool isMatrix() { return false; }
		static constexpr TextureInternalFormat glTextureFormat() { return TextureInternalFormat::rgba32f; }
	};
#pragma endregion

#pragma region MATRIX
	/* Spec for a mat2x2 */
	template <>
	struct GLMTypesSpec<glm::mat2x2>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 4; }
		static constexpr size_t rows() { return 2; }
		static constexpr size_t columns() { return 2; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat2x3 */
	template <>
	struct GLMTypesSpec<glm::mat2x3>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 6; }
		static constexpr size_t rows() { return 3; }
		static constexpr size_t columns() { return 2; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat2x4 */
	template <>
	struct GLMTypesSpec<glm::mat2x4>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 8; }
		static constexpr size_t rows() { return 4; }
		static constexpr size_t columns() { return 2; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat3x2 */
	template <>
	struct GLMTypesSpec<glm::mat3x2>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 6; }
		static constexpr size_t rows() { return 2; }
		static constexpr size_t columns() { return 3; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat3x3 */
	template <>
	struct GLMTypesSpec<glm::mat3x3>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 9; }
		static constexpr size_t rows() { return 3; }
		static constexpr size_t columns() { return 3; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat3x4 */
	template <>
	struct GLMTypesSpec<glm::mat3x4>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 12; }
		static constexpr size_t rows() { return 4; }
		static constexpr size_t columns() { return 3; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat4x2 */
	template <>
	struct GLMTypesSpec<glm::mat4x2>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 8; }
		static constexpr size_t rows() { return 2; }
		static constexpr size_t columns() { return 4; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat4x3 */
	template <>
	struct GLMTypesSpec<glm::mat4x3>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 12; }
		static constexpr size_t rows() { return 3; }
		static constexpr size_t columns() { return 4; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};

	/* Spec for a mat4x4 */
	template <>
	struct GLMTypesSpec<glm::mat4x4>
	{
		using primitiveType = GLfloat;

		static constexpr bool isCompatible() { return true; }

		static constexpr GlType glType() { return GlType::Float; }
		static constexpr size_t size() { return 16; }
		static constexpr size_t rows() { return 4; }
		static constexpr size_t columns() { return 4; }
		static constexpr bool isScalar() { return false; }
		static constexpr bool isVector() { return false; }
		static constexpr bool isMatrix() { return true; }
	};
#pragma endregion
}

#endif // !_GRAPHIC_ENGINE_GLM_TYPE_INFOS
