#ifndef _GRAPHIC_ENGINE_GL_TYPE_INFOS
#define _GRAPHIC_ENGINE_GL_TYPE_INFOS

#include <glm/glm.hpp>

#include <GraphicEngine/Header/GraphicEnum.hpp>

namespace GraphicEngine {

	/* 
	* Info about a specific openGL type
	* Default struct, every type not compatible will be assigned with this values
	*/
	template <GlType T>
	struct GlTypeSpec
	{
		/*
		* Determines whether this enumerated value is valid for the spec.
		* @return true if this type is valid, else false
		*/
		static constexpr bool isValid() { return false; }

		/*
		* The equivalent C++ type.
		*/
		using CppType = void;
	};

	/* Spec for a float */
	template <>
	struct GlTypeSpec<GlType::Float>
	{
		static constexpr bool isValid() { return true; }
		using CppType = float;
	};

	/* Spec for a double */
	template <>
	struct GlTypeSpec<GlType::Double>
	{
		static constexpr bool isValid() { return true; }
		using CppType = double;
	};

	/* Spec for an int */
	template <>
	struct GlTypeSpec<GlType::Int>
	{
		static constexpr bool isValid() { return true; }
		using CppType = int;
	};

	/* Spec for an unsigned int */
	template <>
	struct GlTypeSpec<GlType::UnsignedInt>
	{
		static constexpr bool isValid() { return true; }
		using CppType = unsigned int;
	};

	/* Spec for a byte */
	template <>
	struct GlTypeSpec<GlType::Byte>
	{
		static constexpr bool isValid() { return true; }
		using CppType = char;
	};

	/* Spec for an unsigned byte */
	template <>
	struct GlTypeSpec<GlType::UnsignedByte>
	{
		static constexpr bool isValid() { return true; }
		using CppType = unsigned char;
	};

	/* Spec for a short */
	template <>
	struct GlTypeSpec<GlType::Short>
	{
		static constexpr bool isValid() { return true; }
		using CppType = short;
	};

	/* Spec for an unsigned short */
	template <>
	struct GlTypeSpec<GlType::UnsignedShort>
	{
		static constexpr bool isValid() { return true; }
		using CppType = unsigned short;
	};
}

#endif // !_GRAPHIC_ENGINE_GL_TYPE_INFOS
