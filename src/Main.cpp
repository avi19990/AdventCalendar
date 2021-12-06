#include <iostream>

#include "Task1.h"
#include "Task5.h"

int main()
{
	int taskToSolve = 1;

	switch (taskToSolve)
	{
	case 1:
		Task1("data/Task1Data.txt");
		break;
	case 5:
		Task5("data/Task5Data.txt", 1000, 1000);
		break;
	}
}