#pragma once

#include <vector>
#include <fstream>

struct Vent
{
	int x1, y1;
	int x2, y2;
};

std::vector<Vent> readVentsData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cout << "Can't open file: " << filename << std::endl;
		return std::vector<Vent>();
	}

	std::vector<Vent> vents;
	while (!input.eof())
	{
		Vent tempVent;
		input >> tempVent.x1 >> tempVent.y1 >> tempVent.x2 >> tempVent.y2;

		vents.push_back(tempVent);
	}

	input.close();

	return vents;
}

void chartVent(char* ventsMap, Vent vent, int width)
{
	if (ventsMap[vent.x1 + vent.y1 * width] < 2)
		ventsMap[vent.x1 + vent.y1 * width] += 1;

	while (vent.x1 != vent.x2 || vent.y1 != vent.y2)
	{
		int xDistance = vent.x2 - vent.x1;
		int yDistance = vent.y2 - vent.y1;

		if (xDistance > 0)
			vent.x1 += 1;
		else if (xDistance < 0)
			vent.x1 -= 1;

		if (yDistance > 0)
			vent.y1 += 1;
		else if (yDistance < 0)
			vent.y1 -= 1;

		if (ventsMap[vent.x1 + vent.y1 * width] < 2)
			ventsMap[vent.x1 + vent.y1 * width] += 1;
	}
}

int countVentsAboveThreshold(char* ventMap, int width, int heigth)
{
	int count = 0;
	for (int i = 0; i < width * heigth; ++i)
		if (ventMap[i] == 2)
			count += 1;

	return count;
}

int countDangerousVents(std::vector<Vent> vents, int width, int heigth, bool withDiagonals)
{
	char* ventsMap = new char[width * heigth]{};
	for (Vent vent : vents)
	{
		if (!withDiagonals && vent.x1 != vent.x2 && vent.y1 != vent.y2)
			continue;
		
		chartVent(ventsMap, vent, width);
	}

	int dangerousVentsCount = countVentsAboveThreshold(ventsMap, width, heigth);
	
	delete[] ventsMap;
	return dangerousVentsCount;
}

void Task5(std::string filename, int width, int heigth)
{
	std::vector<Vent> vents = readVentsData(filename);
	if (vents.size() == 0)
		return;

	std::cout << "Solution to task 5 (part1): " << countDangerousVents(vents, width, heigth, false) << std::endl;
	std::cout << "Solution to task 5 (part2): " << countDangerousVents(vents, width, heigth, true) << std::endl;
}