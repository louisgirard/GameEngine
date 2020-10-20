#include <GraphicEngine/Shaders/Header/ShaderSource.hpp>

namespace GraphicEngine {
	namespace Shaders {
		ShaderSource::ShaderSource(const std::filesystem::path& p_filePath)
		{
			append(p_filePath);
		}

		void ShaderSource::addIncludePath(const std::filesystem::path& path)
		{
			_parser.addIncludePath(path);
		}

		void ShaderSource::append(const std::filesystem::path& p_filePath)
		{
			_source << _parser.load(p_filePath);
		}

		std::string ShaderSource::toString() const
		{
			return _source.str();
		}
	}
}

