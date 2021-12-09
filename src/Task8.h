#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

struct DisplayDebugData
{
	std::vector<std::string> digits;
	std::vector<std::string> output;
};

std::vector<DisplayDebugData> readDisplayDebugData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<DisplayDebugData>();
	}

	std::vector<DisplayDebugData> displayDebugLogs;
	while (!input.eof())
	{
		std::string displayDebugLog;
		std::getline(input, displayDebugLog);
		std::stringstream displayDebugLogStream(displayDebugLog);

		DisplayDebugData displayDebugData;

		bool isReadingOutput = false;
		std::string displayDebugLogDigit;
		while (displayDebugLogStream >> displayDebugLogDigit)
		{
			std::sort(displayDebugLogDigit.begin(), displayDebugLogDigit.end());

			if (displayDebugLogDigit == "|")
				isReadingOutput = true;
			else if (isReadingOutput)
				displayDebugData.output.push_back(displayDebugLogDigit);
			else
				displayDebugData.digits.push_back(displayDebugLogDigit);
		}

		displayDebugLogs.push_back(displayDebugData);
	}

	return displayDebugLogs;
}

unsigned int count1478Digits(const std::vector<DisplayDebugData>& displayDebugLogs)
{
	unsigned int digitCount = 0;
	for (const DisplayDebugData& displayDebugLog : displayDebugLogs)
		for (const std::string& digit : displayDebugLog.output)
		{
			unsigned int digitLength = digit.size();

			if (digitLength == 2 || digitLength == 4 || digitLength == 3 || digitLength == 7)
				digitCount += 1;
		}

	return digitCount;
}

std::vector<std::string> findDigitsOfLength(const std::vector<std::string>& digits, int length)
{
	std::vector<std::string> digitsOfLength;
	for (const std::string& digit : digits)
	{
		if (digit.size() == length)
			digitsOfLength.push_back(digit);
	}

	return digitsOfLength;
}

unsigned int countAppearingDigits(const std::string& digit, const std::string& lookedFor)
{
	unsigned int count = 0;
	for (char c : lookedFor)
	{
		if (digit.find(c) != std::string::npos)
			count += 1;
	}

	return count;
}

std::map<int, std::string> mapDigits(const std::vector<std::string>& digits)
{
	std::map<int, std::string> digitMap;

	digitMap[1] = findDigitsOfLength(digits, 2)[0];
	digitMap[4] = findDigitsOfLength(digits, 4)[0];
	digitMap[7] = findDigitsOfLength(digits, 3)[0];
	digitMap[8] = findDigitsOfLength(digits, 7)[0];

	std::vector<std::string> digitsOfLength5 = findDigitsOfLength(digits, 5);
	for (std::string digit : digitsOfLength5)
		if (countAppearingDigits(digit, digitMap[4]) == 2)
		{
			digitMap[2] = digit;
			break;
		}

	for (std::string digit : digitsOfLength5)
	{
		unsigned int appearences = countAppearingDigits(digit, digitMap[2]);
		if (appearences == 3)
			digitMap[5] = digit;
		else if (appearences == 4)
			digitMap[3] = digit;
	}

	std::vector<std::string> digitsOfLength6 = findDigitsOfLength(digits, 6);
	for (std::string digit : digitsOfLength6)
		if (countAppearingDigits(digit, digitMap[4]) == 4)
		{
			digitMap[9] = digit;
			break;
		}

	for (std::string digit : digitsOfLength6)
	{
		unsigned int appearences = countAppearingDigits(digit, digitMap[1]);
		if (appearences == 2 && digit != digitMap[9])
			digitMap[0] = digit;
		else if (appearences == 1)
			digitMap[6] = digit;
	}

	return digitMap;
}

unsigned long long int sumDisplayOutputs(const std::vector<DisplayDebugData>& displayDebugLogs)
{
	unsigned long long int sumResult = 0;

	for (const DisplayDebugData& displayDebugLog : displayDebugLogs)
	{
		std::map<int, std::string> digitMap = mapDigits(displayDebugLog.digits);

		unsigned int result = 0;
		unsigned int mul = 1000;
		for (const std::string& digit : displayDebugLog.output)
		{
			for (int i = 0; i < 10; ++i)
				if (digit == digitMap[i])
				{
					result += i * mul;
					break;
				}

			mul /= 10;
		}

		sumResult += result;
	}

	return sumResult;
}

void Task8(std::string filename)
{
	std::vector<DisplayDebugData> displayDebugLogs = readDisplayDebugData(filename);
	if (displayDebugLogs.size() == 0)
		return;

	std::cout << "Solution to task 8 (part1): " << count1478Digits(displayDebugLogs) << std::endl;
	std::cout << "Solution to task 8 (part2): " << sumDisplayOutputs(displayDebugLogs) << std::endl;
}