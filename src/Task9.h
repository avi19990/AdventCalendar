#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>

std::vector<unsigned short int> readHeigthData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<unsigned short int>();
	}

	std::vector<unsigned short int> heightMap;
	while (!input.eof())
	{
		char heigth;
		input >> heigth;

		heightMap.push_back(heigth - '0');
	}

	return heightMap;
}

std::vector<unsigned int> getNeighbourIndexes(const unsigned int point, const unsigned int width, const unsigned int height)
{
	std::vector<unsigned int> neighbours;

	if ((int)(point % width) - 1 >= 0)
		neighbours.push_back(point - 1);
	if ((int)(point / width) - 1 >= 0)
		neighbours.push_back(point - width);
	if ((int)(point % width) + 1 < width)
		neighbours.push_back(point + 1);
	if ((int)(point / width) + 1 < height)
		neighbours.push_back(point + width);

	return neighbours;
}

bool isPointLow(const unsigned int point, const std::vector<unsigned short int>& heightMap, const unsigned int width, const unsigned int height)
{
	for (unsigned int neighbour : getNeighbourIndexes(point, width, height))
		if (heightMap[neighbour] <= heightMap[point])
			return false;

	return true;
}

std::vector<unsigned int> getLowPoints(const std::vector<unsigned short int>& heightMap, const unsigned int width, const unsigned int height)
{
	std::vector<unsigned int> lowPoints;
	for (unsigned int i = 0; i < width * height; ++i)
	{
		if (isPointLow(i, heightMap, width, height))
			lowPoints.push_back(i);
	}

	return lowPoints;
}

unsigned int calculateRiskLevel(const std::vector<unsigned short int>& heightMap, const std::vector<unsigned int>& lowPoints)
{
	unsigned int riskLevel = 0;
	for (unsigned int point : lowPoints)
	{
		riskLevel += heightMap[point] + 1;
	}

	return riskLevel;
}

std::vector<unsigned int> floodFillBasin(const unsigned int point, const std::vector<unsigned short int>& heightMap, const unsigned int width, const unsigned int height)
{
	std::vector<unsigned int> visited;
	visited.push_back(point);
	std::queue<unsigned int> frontier;
	frontier.push(point);

	while (frontier.size() != 0)
	{
		unsigned int current = frontier.front();
		frontier.pop();

		for (unsigned int neighbour : getNeighbourIndexes(current, width, height))
		{
			if (heightMap[neighbour] == 9 || std::find(visited.begin(), visited.end(), neighbour) != visited.end())
				continue;

			frontier.push(neighbour);
			visited.push_back(neighbour);
		}
	}

	return visited;
}

unsigned int largestBasinsMultiplied(const std::vector<unsigned short int>& heightMap, const std::vector<unsigned int>& lowPoints, const unsigned int width, const unsigned int height)
{
	std::vector<unsigned int> visited;

	unsigned int max[3] = {};
	for (int i = 0; i < lowPoints.size(); ++i)
	{
		if (std::find(visited.begin(), visited.end(), lowPoints[i]) != visited.end())
			continue;

		std::vector<unsigned int> basin = floodFillBasin(lowPoints[i], heightMap, width, height);
		visited.insert(visited.end(), basin.begin(), basin.end());

		if (basin.size() > max[0])
		{
			max[2] = max[1];
			max[1] = max[0];
			max[0] = basin.size();
		}
		else if (basin.size() > max[1])
		{
			max[2] = max[1];
			max[1] = basin.size();
		}
		else if (basin.size() > max[2])
		{
			max[2] = basin.size();
		}
	}

	return max[0] * max[1] * max[2];
}

void Task9(std::string filename, const unsigned int width, const unsigned int height)
{
	std::vector<unsigned short int> heightMap = readHeigthData(filename);
	if (heightMap.size() == 0)
		return;

	std::vector<unsigned int> lowPoints = getLowPoints(heightMap, width, height);

	std::cout << "Solution to task 9 (part1): " << calculateRiskLevel(heightMap, lowPoints) << std::endl;
	std::cout << "Solution to task 9 (part2): " << largestBasinsMultiplied(heightMap, lowPoints, width, height) << std::endl;
}