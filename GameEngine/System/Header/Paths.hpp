#ifndef _SYSTEM_PATHS_HPP_
#define _SYSTEM_PATHS_HPP_

#include <string>

namespace System {
	class Paths
	{
	public:
		/*
		* Gets path of an executable directory
		* @return path to the executable directory*/
		static ::std::string executable();

	};
}
#endif // !_SYSTEM_PATHS_HPP_



