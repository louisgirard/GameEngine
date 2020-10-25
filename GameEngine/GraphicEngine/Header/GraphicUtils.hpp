#pragma once

#include <glm/matrix.hpp>

#include <GraphicEngine/Materials/Header/Color.hpp>

namespace GraphicEngine {

#pragma region TRANSFORM

	/*
	* Applies a transformation to a table of vertices
	* Please note that the perspective division is applied
	*
	* @param p_transform : The transform to apply
	* @param p_toTransform : Vertices that shoudl be transformed
	*/
	inline void applyTransform(const glm::mat4& p_transform, std::vector<glm::vec3>& p_toTransform)
	{
		for (auto it = p_toTransform.begin(), end = p_toTransform.end(); it != end; ++it)
		{
			// Apply transform
			glm::vec4 tmp = p_transform * glm::vec4(*it, 1.0f);
			//Apply perspective
			float invW = 1.0f / tmp.w;
			(*it) = glm::vec3(tmp) * glm::vec3(invW, invW, invW);
		}
	}

	/*
	* Applies a transformation to a table of vertices
	*
	* @param p_transform : The transform to apply
	* @param p_toTransform : Vertices that shoudl be transformed
	*/
	inline void applyTransform(const glm::mat4x3& p_transform, std::vector<glm::vec3>& p_toTransform)
	{
		for (auto it = p_toTransform.begin(), end = p_toTransform.end(); it != end; ++it)
		{
			// Apply transform
			(*it) = p_transform * glm::vec4(*it, 1.0f);
		}
	}

	/*
	* Applies a transformation to a table of vertices
	*
	* @param p_transform : The transform to apply
	* @param p_toTransform : Vertices that shoudl be transformed
	*/
	inline void applyTransform(const glm::mat3& p_transform, std::vector<glm::vec3>& p_toTransform)
	{
		for (auto it = p_toTransform.begin(), end = p_toTransform.end(); it != end; ++it)
		{
			(*it) = p_transform * (*it);
		}
	}
#pragma endregion
}

#pragma region PRINTERS

/*
* Print color in a stream
*
* @param p_out : the stream to print the color into
* @param p_color : the color to print
* @return a stream where the color is printed
*/
inline std::ostream& operator<<(::std::ostream& p_out, const GraphicEngine::Materials::Color& p_color)
{
	p_out << "(" << p_color.getBuffer()[0] << "," << p_color.getBuffer()[1] << "," << p_color.getBuffer()[2] << "," << p_color.getBuffer()[3] << ")";
	return p_out;
}

/*
* Print vec2 in a stream
*
* @param p_out : the stream to print the color into
* @param p_vec : the vector to print
* @return a stream where the vector is printed
*/
inline std::ostream& operator << (std::ostream& p_out, const glm::vec2& p_vec)
{
	std::cout << "(" << p_vec.x << ", " << p_vec.y << ")";
	return p_out;
}

/*
* Print vec3 in a stream
*
* @param p_out : the stream to print the color into
* @param p_vec : the vector to print
* @return a stream where the vector is printed
*/
inline std::ostream& operator << (std::ostream& p_out, const glm::vec3& p_vec)
{
	std::cout << "(" << p_vec.x << ", " << p_vec.y << ", " << p_vec.z << ")";
	return p_out;
}

/*
* Print vec4 in a stream
*
* @param p_out : the stream to print the color into
* @param p_vec : the vector to print
* @return a stream where the vector is printed
*/
inline std::ostream& operator << (std::ostream& p_out, const glm::vec4& p_vec)
{
	std::cout << "(" << p_vec.x << ", " << p_vec.y << ", " << p_vec.z << ", " << p_vec.w << ")";
	return p_out;
}

/*
* Print mat2 in a stream
*
* @param p_out : the stream to print the color into
* @param p_mat : the matrix to print
* @return a stream where the matrix is printed
*/
inline std::ostream& operator<<(std::ostream& p_out, glm::mat2 const& p_mat)
{
	std::cout << "[" << p_mat[0] << ", " << p_mat[1] << "]";
	return p_out;
}

/*
* Print mat3 in a stream
*
* @param p_out : the stream to print the color into
* @param p_mat : the matrix to print
* @return a stream where the matrix is printed
*/
inline std::ostream& operator<<(std::ostream& p_out, glm::mat3 const& p_mat)
{
	std::cout << "[" << p_mat[0] << ", " << p_mat[1] << ", " << p_mat[2] << "]";
	return p_out;
}

/*
* Print mat4 in a stream
*
* @param p_out : the stream to print the color into
* @param p_mat : the matrix to print
* @return a stream where the matrix is printed
*/
inline std::ostream& operator<<(std::ostream& p_out, glm::mat4 const& p_mat)
{
	std::cout << "[" << p_mat[0] << ", " << p_mat[1] << ", " << p_mat[2] << ", " << p_mat[3] << "]";
	return p_out;
}
#pragma endregion



