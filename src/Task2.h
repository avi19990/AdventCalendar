#pragma once

#include <iostream>
#include <fstream>
#include <vector>

struct Command
{
	std::string command;
	int value;
};

std::vector<Command> readCommandsData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return std::vector<Command>();
	}

	std::vector<Command> commands;
	while (!input.eof())
	{
		Command command;
		input >> command.command >> command.value;

		commands.push_back(command);
	}

	return commands;
}

int calculateDestinationMultiplied(std::vector<Command> commands)
{
	int horizontalPosition = 0, depth = 0;
	for (Command command : commands)
	{
		if (command.command == "forward")
			horizontalPosition += command.value;
		else if (command.command == "down")
			depth += command.value;
		else if (command.command == "up")
			depth -= command.value;
	}

	return horizontalPosition * depth;
}

int calculateDestinationMultipliedWithAim(std::vector<Command> commands)
{
	int horizontalPosition = 0, depth = 0, aim = 0;
	for (Command command : commands)
	{
		if (command.command == "forward")
		{
			horizontalPosition += command.value;
			depth += aim * command.value;
		}
		else if (command.command == "down")
			aim += command.value;
		else if (command.command == "up")
			aim -= command.value;
	}

	return horizontalPosition * depth;
}

void Task2(std::string filename)
{
	std::vector<Command> commands = readCommandsData(filename);
	if (commands.size() == 0)
		return;

	std::cout << "Solution to task 1 (part1): " << calculateDestinationMultiplied(commands) << std::endl;
	std::cout << "Solution to task 1 (part2): " << calculateDestinationMultipliedWithAim(commands) << std::endl;
}