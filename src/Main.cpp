#include <iostream>

#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"
#include "Task7.h"
#include "Task8.h"
#include "Task9.h"

int main()
{
	int taskToSolve = 9;

	switch (taskToSolve)
	{
	case 1:
		Task1("data/Task1Data.txt");
		break;
	case 2:
		Task2("data/Task2Data.txt");
		break;
	case 3:
		Task3("data/Task3Data.txt");
		break;
	case 4:
		Task4("data/Task4Data.txt");
		break;
	case 5:
		Task5("data/Task5Data.txt", 1000, 1000);
		break;
	case 6:
		Task6("data/Task6Data.txt");
		break;
	case 7:
		Task7("data/Task7Data.txt");
		break;
	case 8:
		Task8("data/Task8Data.txt");
		break;
	case 9:
		Task9("data/Task9Data.txt", 100, 100);
		break;
	}
}