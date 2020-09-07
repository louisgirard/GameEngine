#include <iostream>
#include "Vector3.h"

int main(int argc, const char* argv[])
{
	Vector3 v1(2,3,1);
	Vector3 v2(4, 1, 0);
	std::cout << v1.scalarProduct(v2) << std::endl;
	std::cout << v1.x << std::endl;
	std::cout << v1.y << std::endl;
	std::cout << v1.z << std::endl;
}