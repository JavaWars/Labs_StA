#include "tests.h"
#include "Range.h"
#include <ctime>

void testRandomAddDeleteKeyFromSet1(int _operationCount, int _maxValue)
{
	srand(time(NULL));
	Set *set = SetCreate();
	for (int i = 0; i < _operationCount; i++)
	{
			int val= rand() % _maxValue + 1;
			SetInsertKey(*set, val);
			std::cout << val << " inserted to set :";
			SetPrint(*set);

	}
	std::cout << "====================\n";
	for (int i = 0; i < _operationCount; i++)
	{
		{
		int val = rand() % _maxValue + 1;
		SetDeleteKey(*set, val);
		std::cout << "delete "<<val << " from set. result:";
		SetPrint(*set);
		}
	}
	SetDestroy(set);
}

void testRandomAddDeleteKeyFromSet2(int _operationCount, int _maxValue)
{
	srand(time(NULL));
	Set *set = SetCreate();
	for (int i = 0; i < _operationCount; i++)
	{
		if (rand() % 2)
		{
			int val = rand() % _maxValue + 1;
			SetInsertKey(*set, val);
			std::cout << val << " inserted to set :";
			SetPrint(*set);

		}
		else
		{
			int val = rand() % _maxValue + 1;
			SetDeleteKey(*set, val);
			std::cout << "delete " << val << " from set. result:";
			SetPrint(*set);
		}
	}
	SetDestroy(set);
}

Set * CreateSet(int _size, int _maxVal)
{
	Set *set = SetCreate();
	for (int i = 0; i < _size; i++)
	{
		int val = rand() % _maxVal + 1;
		SetInsertKey(*set, val);
	}
	SetPrint(*set);
	return set;
}

void testOperationWithSet()
{
	srand(time(NULL));
	Set *set1 = CreateSet(10,15), 
		*set2 = CreateSet(10, 15),
		*set3 = CreateSet(10, 15);

	std::cout << "===============\n";
	std::cout << "1 unite with 2\n";
	Set *Unite12SetResult = SetCreate();
	SetUnite(*set1, *set2,*Unite12SetResult);
	SetPrint(*Unite12SetResult);

	std::cout << "1 unite with 3\n";
	Set *Unite13SetResult = SetCreate();
	SetUnite(*set1, *set3, *Unite13SetResult);
	SetPrint(*Unite13SetResult);

	std::cout << "===============\n";
	std::cout << "1 intersect with 2\n";
	Set *Intersect12SetResult = SetCreate();
	SetIntersect(*set1, *set2, *Intersect12SetResult);
	SetPrint(*Intersect12SetResult);

	std::cout << "1 intersect with 3\n";
	Set *Intersect13SetResult = SetCreate();
	SetIntersect(*set1, *set3, *Intersect13SetResult);
	SetPrint(*Intersect13SetResult);

	std::cout << "===============\n";
	std::cout << "difference 1 with 2\n";
	Set *Difference12SetResult = SetCreate();
	SetDifference(*set1, *set2, *Difference12SetResult);
	SetPrint(*Difference12SetResult);

	std::cout << "difference 1 with 3\n";
	Set *Difference13SetResult = SetCreate();
	SetDifference(*set1, *set3, *Difference13SetResult);
	SetPrint(*Difference13SetResult);
}
