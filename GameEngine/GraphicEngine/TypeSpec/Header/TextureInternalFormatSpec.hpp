#ifndef _GRAPHIC_ENGINE_TEXTURE_INTERNAL_SPEC_HPP_
#define _GRAPHIC_ENGINE_TEXTURE_INTERNAL_SPEC_HPP_

#include <glm/glm.hpp>

#include <GraphicEngine/Header/GraphicEnum.hpp>

namespace GraphicEngine {

	/*
	* Info about a specific texture format 
	* Default struct, every type not compatible will be assigned with this values
	*/
	template <TextureInternalFormat T>
	struct TextureInternalFormatSpec
	{
		/*
		* Determines whether the provided enumerated value is valid for type spec.
		* @return true if this format is valid, els false
		*/
		static constexpr bool isValid() { return false; }

		/*
		* Gets the base internal format associated with the provided format (useful for glTexImage2D for instance)
		* @return base internal format associated with this format
		*/
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat(GL_NONE); }

		/*
		* Gets the base element type associated with the base internal format (useful for glTexImage2D for instance)
		* @return the base element type associated with T
		*/
		static constexpr GlType baseElementType() { return GlType(GL_NONE); }
	};

#pragma region DEPTH
	/* Spec for depth */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::depth>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::depth; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for depth16 */
	template<>
	struct TextureInternalFormatSpec<TextureInternalFormat::depth16> : public TextureInternalFormatSpec<TextureInternalFormat::depth>
	{};

	/* Spec for depth32 */
	template<>
	struct TextureInternalFormatSpec<TextureInternalFormat::depth32> : public TextureInternalFormatSpec<TextureInternalFormat::depth>
	{};

	/* Spec for depthStencil */
	template<>
	struct TextureInternalFormatSpec<TextureInternalFormat::depthStencil>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::depthStencil; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};
#pragma endregion

#pragma region COLOR
	/* Spec for red */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::red>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::red; }
		static constexpr GlType baseElementType() { return GlType::UnsignedByte; }
	};

	/* Spec for rg */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rg>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rg; }
		static constexpr GlType baseElementType() { return GlType::UnsignedByte; }
	};

	/* Spec for rgb */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgb>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgb; }
		static constexpr GlType baseElementType() { return GlType::UnsignedByte; }
	};

	/* Spec for rgba */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgba>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgba; }
		static constexpr GlType baseElementType() { return GlType::UnsignedByte; }
	};
#pragma endregion

#pragma region FLOAT16
	/* Spec for r16f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::r16f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::red; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rg16f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rg16f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rg; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rgb16f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgb16f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgb; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rgba16f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgba16f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgba; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

#pragma endregion

#pragma region FLOAT32
	/* Spec for r32f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::r32f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::red; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rg32f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rg32f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rg; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rgb32f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgb32f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgb; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};

	/* Spec for rgba32f */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgba32f>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgba; }
		static constexpr GlType baseElementType() { return GlType::Float; }
	};
#pragma endregion

#pragma region UNSIGNED_INT32
	/* Spec for r32ui */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::r32ui>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::red; }
		static constexpr GlType baseElementType() { return GlType::UnsignedInt; }
	};

	/* Spec for rg32ui */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rg32ui>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rg; }
		static constexpr GlType baseElementType() { return GlType::UnsignedInt; }
	};

	/* Spec for rgb32ui */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgb32ui>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgb; }
		static constexpr GlType baseElementType() { return GlType::UnsignedInt; }
	};

	/* Spec for rgba32ui */
	template <>
	struct TextureInternalFormatSpec<TextureInternalFormat::rgba32ui>
	{
		static constexpr bool isValid() { return true; }
		static constexpr TextureInternalFormat baseInternalFormat() { return TextureInternalFormat::rgba; }
		static constexpr GlType baseElementType() { return GlType::UnsignedInt; }
	};
#pragma endregion
}

#endif 
