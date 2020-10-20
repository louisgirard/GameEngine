#ifndef _GRAPHIC_ENGINE_SHADER_SOURCE_HPP_
#define _GRAPHIC_ENGINE_SHADER_SOURCE_HPP_

#include <GraphicEngine/Shaders/Header/ShaderParser.hpp>

namespace GraphicEngine  {
	namespace Shaders {
		class ShaderSource
		{
		protected:

			/* Parser retrieving the code in a source file */
			ShaderParser _parser;
			/* Source code for the shader*/
			std::stringstream _source;

		public:

			/*
			* Constructor
			* Initialize the ShaderSource to contain the source code located in the provided file
			* @param p_filePath : Path to the file containing the source code
			*/
			ShaderSource(const std::filesystem::path& p_filePath);

			/* Adds and include path to the parser.
			* @param p_path : The path to add
			*/
			void addIncludePath(const std::filesystem::path& path);

			/*
			* Adds the include paths to the parser in the range [begin;end[
			* @param p_begin : The begin iterator
			* @param p_end : The end iterator
			*/
			template <typename iterator>
			void addIncludePath(iterator p_begin, iterator p_end)
			{
				for (auto it = p_begin; it != p_end; ++it)
				{
					addIncludePath(*it);
				}
			}

			/*
			* Append the code of a file to the source code
			* @param p_filePath : The path to the file containing the code
			*/
			void append(const std::filesystem::path& p_filePath);

			/*
			* Convert the source code to a string
			* @return the source code as a string
			*/
			std::string toString() const;

		};
	}
}

#endif // !_GRAPHIC_ENGINE_SHADER_SOURCE_HPP_



