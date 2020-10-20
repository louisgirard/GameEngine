#ifndef _GRAPHIC_ENGINE_SHADER_PARSER_
#define _GRAPHIC_ENGINE_SHADER_PARSER_

#include <vector>

#include <filesystem>
#include <exception>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

namespace GraphicEngine {
	namespace Shaders {
		class ShaderParser
		{
		protected:

			std::vector<::std::filesystem::path> _includePaths;


			/* Loads a file into a string.
			* @param p_filePath : The path to the file to load
			*/
			void loadFile(const std::filesystem::path& p_filePath,
				std::back_insert_iterator<std::list<std::string>> p_output);

			/*
			* Verify if the file this path leads to exists
			* @param p_path : The path to verify
			*/
			void verifyPath(const std::filesystem::path& p_path);

			/*
			* Find the file location given the include path previously saved by the parser
			* @param p_path : A relative path to the file
			* @return the path to the file if it exists
			**/
			std::filesystem::path findFile(const std::filesystem::path& p_path);

			/*
			* Remove blank space from both end of the string
			* @param p_str : The string to trim
			* @return the string without blank space at it's start and end
			*/
			static std::string trim(const std::string& p_str);

			/*
			* Extract an include file from a command line
			* @param p_line : the line we are inspecting
			* @param (out) p_includePath : the result path to the include file
			*/
			static bool extractInclude(const std::string& p_line, std::filesystem::path& p_includePath);

		public:

			/* Default Constructor */
			ShaderParser() {}


			/* Adds and include path to the parser.
			* @param p_path : The path to add
			*/
			void addIncludePath(const std::filesystem::path& p_path);

			/*
			*  Adds the include paths in the range [begin;end[
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
			* Load a file and replace, include command by designated file
			* @param p_filePath : Path to the specified path
			*/
			std::string load(const std::filesystem::path& p_filePath);

		};
	
	}
}

#endif // !_GRAPHIC_ENGINE_SHADER_PARSER_