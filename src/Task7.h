#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<unsigned int> readCrabPositionData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<unsigned int>();
	}

	std::vector<unsigned int> crabPositions;
	while (!input.eof())
	{
		int crabPosition;
		input >> crabPosition;

		crabPositions.push_back(crabPosition);
	}

	return crabPositions;
}

unsigned int shortestPathToAlignment(const std::vector<unsigned int>& crabPositions)
{
	unsigned int alignmentPosition = crabPositions[crabPositions.size() / 2];

	unsigned int sumFuel = 0;
	for (unsigned int crabPosition : crabPositions)
		sumFuel += abs((int)alignmentPosition - (int)crabPosition);

	return sumFuel;
}

unsigned int shortestPathToAlignmentWithIncreasingCost(const std::vector<unsigned int>& crabPositions)
{
	unsigned int sumPosition = 0;
	for (unsigned int crabPosition : crabPositions)
		sumPosition += crabPosition;
	unsigned int alignmentPosition = sumPosition / crabPositions.size();

	unsigned int sumFuel = 0;
	for (unsigned int crabPosition : crabPositions)
	{
		unsigned int distance = abs((int)alignmentPosition - (int)crabPosition);
		unsigned int fuel = (unsigned int)(((float)(distance + 1) / 2.0f) * distance);

		sumFuel += fuel;
	}

	return sumFuel;
}

void Task7(std::string filename)
{
	std::vector<unsigned int> crabPositions = readCrabPositionData(filename);
	if (crabPositions.size() == 0)
		return;

	std::sort(crabPositions.begin(), crabPositions.end());

	std::cout << "Solution to task 7 (part1): " << shortestPathToAlignment(crabPositions) << std::endl;
	std::cout << "Solution to task 7 (part2): " << shortestPathToAlignmentWithIncreasingCost(crabPositions) << std::endl;
}