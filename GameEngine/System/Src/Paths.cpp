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
		int index = res.find_last_of('\\');
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

}
