#pragma once

#include <iostream>
#include <fstream>
#include <map>

std::map<unsigned int, unsigned long long int> readLanternfishData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::map<unsigned int, unsigned long long int>();
	}

	std::map<unsigned int, unsigned long long int> lanternfishTimers;
	while (!input.eof())
	{
		int lanternfishTimer;
		input >> lanternfishTimer;

		lanternfishTimers[lanternfishTimer] += 1;
	}

	return lanternfishTimers;
}

unsigned long long int lanternfishCountAfterNDays(std::map<unsigned int, unsigned long long int> lanternfishTimers, unsigned int days)
{
	for (unsigned int i = 0; i < days; ++i)
	{
		std::map<unsigned int, unsigned long long int> newLanternfishTimers;

		for (unsigned int j = 0; j < 9; ++j)
		{
			if (j == 6)
				newLanternfishTimers[j] += lanternfishTimers[0];

			newLanternfishTimers[j] += lanternfishTimers[(j + 1) % 9];
		}

		lanternfishTimers.clear();
		lanternfishTimers = newLanternfishTimers;
	}

	unsigned long long int sum = 0;
	for (unsigned int i = 0; i < 9; ++i)
		sum += lanternfishTimers[i];

	return sum;
}

void Task6(std::string filename)
{
	std::map<unsigned int, unsigned long long int> lanternfishTimers = readLanternfishData(filename);
	if (lanternfishTimers.size() == 0)
		return;

	std::cout << "Solution to task 6 (part1): " << lanternfishCountAfterNDays(lanternfishTimers, 80) << std::endl;
	std::cout << "Solution to task 6 (part2): " << lanternfishCountAfterNDays(lanternfishTimers, 256) << std::endl;
}