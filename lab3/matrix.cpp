#include "matrix.h"

Matrix * CreateMatrix(int i, int j)
{
	Matrix * result=new Matrix();
	result->m_maxRow = i;
	result->m_maxColumn = j;
	result->m_dataHashTable = HashTableCreate(result->m_maxColumn);
	return result;
}

void destroyMatrix(Matrix * _matrix)
{
	HashTableDestroy(_matrix->m_dataHashTable);
	delete _matrix;
}

int getDataFrom(Matrix * _matrix, int _row, int _col)
{
	HashTableGet(*_matrix->m_dataHashTable, *CreateKey(_row,_col) );
	return 0;
}

void writeData(Matrix * _matrix, int _row, int _col,int data)
{
	HashTableInsert(*_matrix->m_dataHashTable, *CreateKey(_row, _col),data);
}

void printMatrix(Matrix * _matrix, std::ostream &_ostr)
{
	for (int i = 0; i < _matrix->m_maxRow; i++)
	{
		for (int j = 0; j < _matrix->m_maxColumn; j++)
		{
			try
			{
				int res = HashTableGet(*_matrix->m_dataHashTable, *CreateKey(i, j));
				_ostr << res<<"\t";
			}
			catch (const char * ch)
			{
				_ostr << ch << "\t";
			}
		}
		_ostr << "\n";
	}
}

Matrix * MUL_Matrix(Matrix * _matrix1, Matrix * _matrix2)
{
	if ((_matrix1->m_maxColumn == _matrix2->m_maxColumn) && (_matrix1->m_maxRow == _matrix2->m_maxRow)
		&&(_matrix1->m_maxColumn==_matrix2->m_maxRow))
	{
		Matrix * newMatrix;
		newMatrix = CreateMatrix(_matrix1->m_maxRow, _matrix1->m_maxColumn);

		for (int i = 0; i < _matrix1->m_maxRow; i++)
		{
			for (int j = 0; j < _matrix1->m_maxColumn; j++)
			{
				int res = 0;
				
				for (int k = 0; k < _matrix1->m_maxColumn; k++)//_matrix1->m_maxColumn==_matrix2->m_maxRow
				{
					int a = 0, b = 0;
					try
					{
						a = HashTableGet(*_matrix1->m_dataHashTable, *CreateKey(i, k));
					}
					catch (const char * ch){}
				
					try
					{
						b = HashTableGet(*_matrix2->m_dataHashTable, *CreateKey(k, j));
					}
					catch (const char * ch) {}
					res += a*b;
				}
				
				if (res!=0)
					HashTableInsert(*newMatrix->m_dataHashTable, *CreateKey( i,j), res);
			}
		}
		return newMatrix;
	}
	else return nullptr;
}

Matrix * SUB_Matrix(Matrix * _matrix1, Matrix * _matrix2)
{
	if ((_matrix1->m_maxColumn == _matrix2->m_maxColumn) && (_matrix1->m_maxRow == _matrix2->m_maxRow))
	{
		Matrix * newMatrix;
		newMatrix = CreateMatrix(_matrix1->m_maxRow, _matrix1->m_maxColumn);

		for (int i = 0; i < _matrix1->m_maxRow; i++)
		{
			for (int j = 0; j < _matrix1->m_maxColumn; j++)
			{
				int a = 0, b = 0;
				try
				{
					a = HashTableGet(*_matrix1->m_dataHashTable, *CreateKey(i, j));
				}
				catch (const char * ch){}
				try
				{
					b = HashTableGet(*_matrix2->m_dataHashTable, *CreateKey(i, j));
				}
				catch (const char * ch) {}
				int res = a - b;
				if (res != 0)
					HashTableInsert(*newMatrix->m_dataHashTable, *CreateKey(i, j), res);
			}
		}
		return newMatrix;
	}
	else return nullptr;
}

Matrix * ADD_Matrix(Matrix * _matrix1, Matrix * _matrix2)
{
	if ((_matrix1->m_maxColumn == _matrix2->m_maxColumn) && (_matrix1->m_maxRow == _matrix2->m_maxRow))
	{
		Matrix * newMatrix;
		newMatrix = CreateMatrix(_matrix1->m_maxRow, _matrix1->m_maxColumn);

		for (int i = 0; i < _matrix1->m_maxRow; i++)
		{
			for (int j = 0; j < _matrix1->m_maxColumn; j++)
			{
				int a = 0, b = 0;
				try
				{
					a = HashTableGet(*_matrix1->m_dataHashTable, *CreateKey(i, j));
				}
				catch (const char * ch) {}
				try
				{
					b = HashTableGet(*_matrix2->m_dataHashTable, *CreateKey(i, j));
				}
				catch (const char * ch) {}
				int res = a + b;
				if (res!=0)
					HashTableInsert(*newMatrix->m_dataHashTable, *CreateKey( i,j), res);
			}
		}
		return newMatrix;
	}
	else return nullptr;
}

Matrix * transpositionMatrix(Matrix * _matrix)
{
	Matrix * newMatrix;
	newMatrix = CreateMatrix(_matrix->m_maxRow,_matrix->m_maxColumn);
	for (int i = 0; i < _matrix->m_maxRow; i++)
	{
		for (int j = 0; j < _matrix->m_maxColumn; j++)
		{
			try
			{
				int res = HashTableGet(*_matrix->m_dataHashTable, *CreateKey(i, j));
				HashTableInsert(*newMatrix->m_dataHashTable, *CreateKey(j, i), res);				
			}
			catch (const char * ch){}
		}
	}
	return newMatrix;
}
