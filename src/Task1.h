#pragma once

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> readDepthMeasurementsData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<int>();
	}

	std::vector<int> measurements;
	while (!input.eof())
	{
		int measurement;
		input >> measurement;

		measurements.push_back(measurement);
	}

	return measurements;
}

int depthMeasurementIncreaseCount(std::vector<int> measurements, int windowSize)
{
	int increasesCount = 0;
	for (int i = 0; i < measurements.size() - windowSize; ++i)
	{
		int windowASum = 0;
		for (int a = i; a < i + windowSize; ++a)
			windowASum += measurements[a];

		int windowBSum = 0;
		for (int b = i + 1; b < i + windowSize + 1; ++b)
			windowBSum += measurements[b];

		if (windowASum < windowBSum)
			increasesCount += 1;
	}

	return increasesCount;
}

void Task1(std::string filename)
{
	std::vector<int> measurements = readDepthMeasurementsData(filename);
	if (measurements.size() == 0)
		return;

	std::cout << "Solution to task 1 (part1): " << depthMeasurementIncreaseCount(measurements, 1) << std::endl;
	std::cout << "Solution to task 1 (part2): " << depthMeasurementIncreaseCount(measurements, 3) << std::endl;
}