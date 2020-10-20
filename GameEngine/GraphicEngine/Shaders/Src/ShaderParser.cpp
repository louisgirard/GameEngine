#include <GraphicEngine/Shaders/Header/ShaderParser.hpp>

namespace GraphicEngine {
	namespace Shaders {
		void ShaderParser::addIncludePath(const std::filesystem::path& p_path)
		{
			_includePaths.push_back(p_path);
		}


		std::string ShaderParser::load(const std::filesystem::path& p_filePath) {

			// Get the path from which the file comes from to get a base path for include files 
			std::filesystem::path newPath = p_filePath;
			newPath.remove_filename();
			_includePaths.push_back(newPath);

			std::list<std::string> result;

			try
			{
				loadFile(p_filePath, std::back_inserter(result));
			}
			catch (const std::exception& error)
			{
				_includePaths.pop_back();
				throw error;
			}

			_includePaths.pop_back();
			std::stringstream output;
			for (std::list<std::string>::iterator it = result.begin(), end = result.end(); it != end; ++it)
			{
				output << *it;
			}
			return output.str();
		}

		std::string ShaderParser::trim(const std::string& p_str)
		{
			// Get string size
			int beginIndex = 0;
			int endIndex = p_str.size() - 1;

			//We remove every blank space from front and back of the string
			while (beginIndex < p_str.size() && std::isspace(p_str[beginIndex])) { ++beginIndex; }
			while (endIndex > 0 && std::isspace(p_str[endIndex])) { --endIndex; }

			//If the string is only blank space return empty string
			if (endIndex < beginIndex) { return ""; }

			//Remove blank space from the string and give it as a result
			return p_str.substr(beginIndex, endIndex - (int)beginIndex + (int)1);
		}

		bool ShaderParser::extractInclude(const std::string& p_line, std::filesystem::path& p_includePath)
		{
			//Remove blank space in the line's string
			std::string line = trim(p_line);

			std::string search = "#include";

			//If first command is an include command then we find its related path 
			if (search == line.substr(0, search.size()))
			{
				//Remove include command, eventual blank space 
				line = trim(line.substr(search.size(), line.size() - search.size()));
				//and  "\'\'" from the string to get path as given by the shader writer
				p_includePath = line.substr(1, line.size() - 2);

				return true;
			}

			return false;
		}

		void ShaderParser::loadFile(const std::filesystem::path& p_filePath,
			std::back_insert_iterator<std::list<std::string>> p_output) {

			std::cout << "Processing file " << p_filePath.string() << std::endl;
			verifyPath(p_filePath);

			std::ifstream input(p_filePath);
			while (!input.eof())
			{
				// Extract Line 
				std::string line;
				std::getline(input, line);

				//If line is an include command => extract file that correspond
				std::filesystem::path includePath;
				if (extractInclude(line, includePath))
				{
					loadFile(findFile(includePath), p_output);
				}

				//Save 
				else
				{
					(*p_output) = line + "\n";
					++p_output;
				}
			}
		}

		void ShaderParser::verifyPath(const std::filesystem::path& p_path) {

			if (!std::filesystem::exists(p_path))
				throw std::ios_base::failure(std::string("File  ") + p_path.string() + " not found.");

		}


		std::filesystem::path ShaderParser::findFile(const std::filesystem::path& p_path) {

			// If the path is linked to a file then we can return this path
			if (std::filesystem::exists(p_path)) { return p_path; }

			//Else iterate through any given directory to see if the file is not located there
			for (std::vector<::std::filesystem::path>::iterator it = _includePaths.begin(), end = _includePaths.end();
				it != end; ++it)
			{
				std::filesystem::path current = (*it) / p_path;
				if (std::filesystem::exists(current)) { return current; }
			}

			// If none of the directory contains this file, throw an error
			throw std::ios_base::failure(std::string("Include file ") + p_path.string() + " not found.");
		}
	}
}