#ifndef _TEST_
#define _TEST_
#include <iostream>

#include "matrix.h"
void test()
{
	Matrix * matrix;
	matrix = CreateMatrix(3,3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int k = j + i * 3;
			if (i!=j)
				writeData(matrix, i, j, k);
		}
			
	}
	printMatrix(matrix,std::cout);
	
	std::cout << "===========transposition:\n";
	Matrix * newMatrix;
	newMatrix=transpositionMatrix(matrix);
	printMatrix(newMatrix, std::cout);
	
	std::cout << "===========SUB:\n";
	Matrix *SubMatrixResult;
	SubMatrixResult = SUB_Matrix(matrix, newMatrix);
	printMatrix(SubMatrixResult, std::cout);

	std::cout << "===========ADD:\n";
	Matrix *AddMatrixResult;
	AddMatrixResult = ADD_Matrix(matrix, newMatrix);
	printMatrix(AddMatrixResult,std::cout);

	std::cout << "MUL:\n";
	Matrix *MULMatrixResult;
	MULMatrixResult = MUL_Matrix(matrix, newMatrix);
	printMatrix(MULMatrixResult, std::cout);
}

#endif
