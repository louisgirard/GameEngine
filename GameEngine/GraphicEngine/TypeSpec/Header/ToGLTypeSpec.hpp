#ifndef _GRAPHIC_ENGINE_TO_GL_TYPE_INFOS
#define _GRAPHIC_ENGINE_TO_GL_TYPE_INFOS

#include <glm/glm.hpp>

#include <GraphicEngine/Header/GraphicEnum.hpp>

namespace GraphicEngine {

	/* 
	* Info about a specific openGL type
	* Spec associated with the  GlType enum, used to get the C++ type as an enumerated value of an OpenGL type.
	*/
	template <typename T>
	struct ToGlTypeSpec
	{
		/*
		* Determines whether the provided type is compatible with the GlType enumeration.
		* @return true is the type is compatible, else false
		*/
		static constexpr bool isValid() { return false; }

		/*
		* Gets the GlType equivalent to the associated C++ type
		* @return GLType associated with T
		*/
		static constexpr GlType glType() { return GlType(GL_NONE); }
	};

	/* Spec for a float */
	template <>
	struct ToGlTypeSpec<float>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::Float; }
	};

	/* Spec for a double */
	template <>
	struct ToGlTypeSpec<double>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::Double; }
	};

	/* Spec for a char */
	template <>
	struct ToGlTypeSpec<char>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::Byte; }
	};

	/* Spec for an unsigned char */
	template <>
	struct ToGlTypeSpec<unsigned char>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::UnsignedByte; }
	};

	/* Spec for a short */
	template <>
	struct ToGlTypeSpec<short>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::Short; }
	};

	/* Spec for an unsigned short */
	template <>
	struct ToGlTypeSpec<unsigned short>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::UnsignedShort; }
	};

	/* Spec for an int */
	template <>
	struct ToGlTypeSpec<int>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::Int; }
	};

	/* Spec for an unsigned int */
	template <>
	struct ToGlTypeSpec<unsigned int>
	{
		static constexpr bool isValid() { return true; }
		static constexpr GlType glType() { return GlType::UnsignedInt; }
	};
}

#endif // !_GRAPHIC_ENGINE_TO_GL_TYPE_INFOS
