#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum LifeSupportComponent { OxygenGeneratorRating, CO2ScrubberRating };

std::vector<std::string> readDiagnosticsData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<std::string>();
	}

	std::vector<std::string> diagnostics;
	while (!input.eof())
	{
		std::string diagnostic;
		input >> diagnostic;

		diagnostics.push_back(diagnostic);
	}

	return diagnostics;
}

int getPowerConsumption(std::vector<std::string> diagnostics)
{
	int diagnosticLength = diagnostics[0].size();

	int* zerosCount = new int[diagnosticLength] {};
	int* onesCount = new int[diagnosticLength] {};

	for (std::string diagnostic : diagnostics)
		for (int i = 0; i < diagnosticLength; ++i)
		{
			if (diagnostic[i] == '0')
				zerosCount[i] += 1;
			else
				onesCount[i] += 1;
		}

	std::string gammaResult;
	for (int i = 0; i < diagnosticLength; ++i)
	{
		if (zerosCount[i] > onesCount[i])
			gammaResult += '0';
		else
			gammaResult += '1';
	}

	std::string epsilonResult;
	for (int i = 0; i < diagnosticLength; ++i)
	{
		if (gammaResult[i] == '0')
			epsilonResult += '1';
		else
			epsilonResult += '0';
	}

	int gamma = std::stoi(gammaResult, 0, 2);
	int epsilon = std::stoi(epsilonResult, 0, 2);

	return gamma * epsilon;
}

int getLifeSupportComponentRating(std::vector<std::string> diagnostics, LifeSupportComponent component)
{
	int diagnosticLength = diagnostics[0].size();

	for (int i = 0; i < diagnosticLength; ++i)
	{
		if (diagnostics.size() == 1)
			return std::stoi(diagnostics[0], 0, 2);

		int zeros = 0, ones = 0;
		for (std::string diagnostic : diagnostics)
			if (diagnostic[i] == '0')
				zeros += 1;
			else
				ones += 1;

		char controlValue;
		if (component == LifeSupportComponent::OxygenGeneratorRating)
			controlValue = zeros > ones ? '0' : '1';
		else
			controlValue = ones < zeros ? '1' : '0';

		std::vector<std::string> filteredDiagnostics;
		for (std::string diagnostic : diagnostics)
		{
			if (diagnostic[i] == controlValue)
				filteredDiagnostics.push_back(diagnostic);
		}

		diagnostics.clear();
		diagnostics = filteredDiagnostics;
	}
}

int getLifeSupportRating(std::vector<std::string> diagnostics)
{
	return getLifeSupportComponentRating(diagnostics, LifeSupportComponent::OxygenGeneratorRating) * getLifeSupportComponentRating(diagnostics, LifeSupportComponent::CO2ScrubberRating);
}

void Task3(std::string filename)
{
	std::vector<std::string> diagnostics = readDiagnosticsData(filename);
	if (diagnostics.size() == 0)
		return;

	std::cout << "Solution to task 3 (part1): " << getPowerConsumption(diagnostics) << std::endl;
	std::cout << "Solution to task 3 (part2): " << getLifeSupportRating(diagnostics) << std::endl;
}