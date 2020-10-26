#ifndef _SYSTEM_PATHS_HPP_
#define _SYSTEM_PATHS_HPP_

#include <string>
#include <exception>
#include <cassert>
#include <vector>
#include <filesystem>

namespace System {
	class Paths
	{
	protected :

		/* Paths registered */
		::std::vector<std::filesystem::path> _paths;

	public:
		/*
		* Gets path of an executable directory
		* @return path to the executable directory*/
		static ::std::string executable();

		// Define type name
		using iterator = std::vector<std::filesystem::path>::iterator;
		using const_iterator = std::vector<std::filesystem::path>::const_iterator;

		/* Default constructor */
		Paths(){}

		/*
		* Finds the path of the provided file. If the . If the file exists in the current path, it is returned as it was provided.
		* An std::io_base::failure exception is throw if the file is not found.
		* 
		* @param p_file : The searched file
		* @return a path to the provided file
		*/
		std::filesystem::path findFile(const std::filesystem::path& p_file) const;

#pragma region REGITER
		/*
		* Register a search path
		* @param p_path : Path registered
		*/
		void registerPath(const std::filesystem::path& p_path);

		/*
		* Register search paths in the provided iterator range
		* @param p_begin : The begin iterator
		* @param p_end : The end iterator
		*/
		template <typename iterator>
		void registerPath(iterator p_begin, iterator p_end)
		{
			for (auto it = p_begin; it != p_end; ++it)
			{
				registerPath(*it);
			}
		}

		/*
		* Pops the last search path
		*/
		void pop();
#pragma endregion

#pragma region ITERATOR
		/*
		* Gets an iterator to the beginning of the paths
		* @return an iterator to the beginning of the paths
		*/
		iterator begin();

		/*
		* Gets an iterator to the beginning of the paths
		* @return an iterator to the beginning of the paths
		*/
		const_iterator begin() const;

		/*
		* Gets an iterator past the end of the paths
		* @return an iterator past the end of the paths
		*/
		iterator end();

		/*
		* Gets an iterator past the end of the paths
		* @return an iterator past the end of the paths
		*/
		const_iterator end() const;
#pragma endregion
	};
}
#endif // !_SYSTEM_PATHS_HPP_



