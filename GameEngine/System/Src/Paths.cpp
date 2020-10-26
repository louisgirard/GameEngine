#include <System/Header/Paths.hpp>

#if defined(_WIN32) && !defined(WIN32)
#define WIN32
#endif

namespace System {

// There is a difference between windows and linux
#if defined WIN32 

#include <windows.h>

	::std::string Paths::executable()
	{
		char result[MAX_PATH];
		std::string res(result, GetModuleFileNameA(NULL, result, MAX_PATH));
		int index = (int)res.find_last_of('\\');
		return res.substr(0, index);
	}

#else

#include <limits.h>
#include <unistd.h>

	::std::string Paths::executable()
	{
		char result[PATH_MAX];
		ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
		std::string res = result;
		int index = res.find_last_of('/');
		return res.substr(0, index);
		//return std::string( result, (count > 0) ? count : 0 );
	}

#endif

	std::filesystem::path Paths::findFile(const std::filesystem::path& p_file) const
	{
		if (std::filesystem::exists(p_file)) { return p_file; }
		// Look through every path to find the correct one
		for (auto it = _paths.begin(), end = _paths.end(); it != end; ++it)
		{
			std::filesystem::path current = (*it);
			current /= p_file;
			if (std::filesystem::exists(current)) { return current; }
		}
		throw std::ios_base::failure("File: " + p_file.string() + " not found");
	}

#pragma region REGITER
	void Paths::registerPath(const std::filesystem::path& p_path)
	{
		_paths.push_back(p_path);
	}

	void Paths::pop()
	{
		assert(!_paths.empty());
		_paths.pop_back();
	}
#pragma endregion

#pragma region ITERATOR
	Paths::iterator Paths::begin() {
		return _paths.begin(); 
	}

	Paths::const_iterator Paths::begin() const {
		return _paths.begin(); 
	}

	Paths::iterator Paths::end() {
		return _paths.end();
	}

	Paths::const_iterator Paths::end() const {
		return _paths.end(); 
	}
#pragma endregion
}
