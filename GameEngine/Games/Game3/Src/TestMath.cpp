#include <Games/Game3/Header/TestMath.hpp>

namespace Games::Game3 {
	TestMath::TestMath() : GameBase()
	{
	}


	void TestMath::initGame()
	{
		std::cout << "Debug Matrix 3x3" << std::endl << std::endl;

		// test Contructor
		Matrix3x3 matrix1;
		Matrix3x3 matrix2(matrix1);

		Vector3 cols[3];
		cols[0] = Vector3(0.f, 2.f, 1.5f);
		cols[1] = Vector3(1.f, 3.f, 1.5f);
		cols[2] = Vector3(0.f, 2.f, 0.f);
		Matrix3x3 matrix3(cols);

		Matrix3x3 matrix4(1, 0, 0, 2, 0, 0, 0, 2, 3);

		Matrix3x3 matrix5(Matrix3x3::identity());

		std::cout << "Matrix 1 : " << matrix1;
		std::cout << "Matrix 2 : " << matrix2;
		std::cout << "Matrix 3 : " << matrix3;
		std::cout << "Matrix 4 : " << matrix4;
		std::cout << "Identity : " << matrix5;


		std::cout << "Component 4 of identity : " << matrix5[4] << std::endl;
		std::cout << "Component 5 of matrix 3 : " << matrix3[5] << std::endl;

		Vector3 axisX(1, 0, 0);
		Vector3 randomVec(5.f, 8.f, 9.f);

		std::cout << "Matrix 4 * axisX : " << matrix4 * axisX << std::endl;
		std::cout << "Matrix 3 * " << randomVec << " : " << matrix3 * randomVec << std::endl;

		std::cout << "Matrix 3 * Matrix 4 " << matrix3 * matrix4 << std::endl;

		Matrix3x3 matrix6(matrix3);
		std::cout << "Matrix 6" << matrix6;
		matrix6 *= matrix4;
		std::cout << "Matrix 6 *= Matrix 4" << matrix6 << std::endl;

		Matrix3x3 matrix7(12,2,0,0,3,4,0,5,4);
		std::cout << "Matrix 7 (inversible) : " << matrix7;
		std::cout << "get matrix 7 Inversion" << matrix7.getInversion() << std::endl;
		matrix7.invert();
		std::cout << "Invert matrix 6" << matrix7 << std::endl;

		std::cout << "Get matrix 4 transpose " << matrix4.getTranspose() << std::endl;
		matrix4.transpose();
		std::cout << "Transpose matrix 4 " << matrix4 << std::endl;

		glm::mat3 glmMat(0, 1, 2, 3, 4, 5, 6, 7, 8);
		Matrix3x3 matGLM(Matrix3x3::convertGlm(glmMat));
		glm::mat3 backToglmMat = Matrix3x3::toGlm(matGLM);

		std::cout << "Glm matrix : " << glmMat << std::endl;
		std::cout << "Convert glm matrix to Matrix3x3 : " << matGLM;
		std::cout << "Verify glm matrix (* axisX) : " << glmMat * glm::vec3(1, 0, 0) << std::endl;
		std::cout << "Convert back to glm " << backToglmMat << std::endl;
		std::cout << "Verify matrix * axisX : " << matGLM * axisX;


		/*std::cout << "Debug Matrix 3x4" << std::endl << std::endl;

		// test Contructor
		Matrix3x3 matrix1;
		Matrix3x3 matrix2(matrix1);

		Vector3 cols[3];
		cols[0] = Vector3(0.f, 2.f, 1.5f);
		cols[1] = Vector3(1.f, 3.f, 1.5f);
		cols[2] = Vector3(0.f, 2.f, 0.f);
		Matrix3x3 matrix3(cols);

		Matrix3x3 matrix4(1, 0, 0, 2, 0, 0, 0, 2, 3);

		Matrix3x3 matrix5(Matrix3x3::identity());

		std::cout << "Matrix 1 : " << matrix1;
		std::cout << "Matrix 2 : " << matrix2;
		std::cout << "Matrix 3 : " << matrix3;
		std::cout << "Matrix 4 : " << matrix4;
		std::cout << "Identity : " << matrix5;


		std::cout << "Component 4 of identity : " << matrix5[4] << std::endl;
		std::cout << "Component 5 of matrix 3 : " << matrix3[5] << std::endl;

		Vector3 axisX(1, 0, 0);
		Vector3 randomVec(5.f, 8.f, 9.f);

		std::cout << "Matrix 4 * axisX : " << matrix4 * axisX << std::endl;
		std::cout << "Matrix 3 * " << randomVec << " : " << matrix3 * randomVec << std::endl;

		std::cout << "Matrix 3 * Matrix 4 " << matrix3 * matrix4 << std::endl;

		Matrix3x3 matrix6(matrix3);
		std::cout << "Matrix 6" << matrix6;
		matrix6 *= matrix4;
		std::cout << "Matrix 6 *= Matrix 4" << matrix6 << std::endl;

		Matrix3x3 matrix7(12, 2, 0, 0, 3, 4, 0, 5, 4);
		std::cout << "Matrix 7 (inversible) : " << matrix7;
		std::cout << "get matrix 7 Inversion" << matrix7.getInversion() << std::endl;
		matrix7.invert();
		std::cout << "Invert matrix 6" << matrix7 << std::endl;

		std::cout << "Get matrix 4 transpose " << matrix4.getTranspose() << std::endl;
		matrix4.transpose();
		std::cout << "Transpose matrix 4 " << matrix4 << std::endl;

		glm::mat3 glmMat(0, 1, 2, 3, 4, 5, 6, 7, 8);
		Matrix3x3 matGLM(Matrix3x3::convertGlm(glmMat));
		glm::mat3 backToglmMat = Matrix3x3::toGlm(matGLM);

		std::cout << "Glm matrix : " << glmMat << std::endl;
		std::cout << "Convert glm matrix to Matrix3x3 : " << matGLM;
		std::cout << "Verify glm matrix (* axisX) : " << glmMat * glm::vec3(1, 0, 0) << std::endl;
		std::cout << "Convert back to glm " << backToglmMat << std::endl;
		std::cout << "Verify matrix * axisX : " << matGLM * axisX;*/
	}


	void TestMath::updatePhysic(double p_dt)
	{



	}

}
