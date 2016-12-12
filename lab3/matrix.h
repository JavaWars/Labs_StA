#ifndef _MATRIX_
#define _MATRIX_


#include <iostream>
#include "hash_table.hpp"

struct Matrix
{
	int m_maxRow, m_maxColumn;
	HashTable * m_dataHashTable;
};

Matrix * CreateMatrix(int i, int j);

void destroyMatrix(Matrix * _matrix);

int getDataFrom(Matrix * _matrix, int _row, int _col);

void writeData(Matrix * _matrix, int _row, int _col, int data);

void printMatrix(Matrix * _matrix, std::ostream & _ostr);

Matrix * MUL_Matrix(Matrix * _matrix1, Matrix * _matrix2);//*

Matrix * SUB_Matrix(Matrix * _matrix1, Matrix * _matrix2);//-

Matrix * ADD_Matrix(Matrix * _matrix1, Matrix * _matrix2);//+

Matrix * transpositionMatrix(Matrix * _matrix);

#endif // !_MATRIX_

