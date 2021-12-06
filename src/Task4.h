#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct BingoBoard
{
	std::vector<int> numbers;
	std::vector<bool> completes;

	BingoBoard()
	{
		completes = std::vector<bool>(25, false);
	}
};

struct BingoSimulationData
{
	std::vector<int> numbers;
	std::vector<BingoBoard> boards;
};

struct WinningBingoBoard
{
	BingoBoard board;
	int winningNumber;
};

BingoSimulationData readBingoSimulationData(std::string filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return BingoSimulationData();
	}

	BingoSimulationData bingoSimData;

	std::string numbersString;
	input >> numbersString;

	std::stringstream ss(numbersString);
	std::string numberString;
	while (std::getline(ss, numberString, ','))
		bingoSimData.numbers.push_back(std::stoi(numberString));

	while (!input.eof())
	{
		BingoBoard board;
		for (int i = 0; i < 25; ++i)
		{
			int number;
			input >> number;

			board.numbers.push_back(number);
		}

		bingoSimData.boards.push_back(board);
	}

	return bingoSimData;
}

bool isBoardWinning(BingoBoard board)
{
	bool boardWon = false;

	for (int i = 0; i < 5; ++i)
	{
		bool lineWon = true;
		for (int j = 0; j < 5; ++j)
			if (!board.completes[j + i * 5])
			{
				lineWon = false;
				break;
			}

		if (lineWon)
		{
			boardWon = true;
			break;
		}

		lineWon = true;
		for (int j = 0; j < 5; ++j)
			if (!board.completes[i + j * 5])
			{
				lineWon = false;
				break;
			}

		if (lineWon)
		{
			boardWon = true;
			break;
		}
	}

	return boardWon;
}

WinningBingoBoard findBestBoard(BingoSimulationData bingoSimulation)
{
	for (int i = 0; i < bingoSimulation.numbers.size(); ++i)
	{
		for (BingoBoard& bingoBoard : bingoSimulation.boards)
		{
			for (int numberIndex = 0; numberIndex < bingoBoard.numbers.size(); ++numberIndex)
				if (bingoBoard.numbers[numberIndex] == bingoSimulation.numbers[i])
				{
					bingoBoard.completes[numberIndex] = true;
					break;
				}

			if (isBoardWinning(bingoBoard))
				return WinningBingoBoard{bingoBoard, bingoSimulation.numbers[i]};
		}
	}
}

WinningBingoBoard findWorstBoard(BingoSimulationData bingoSimulation)
{
	WinningBingoBoard worstWinningBoard;
	std::vector<bool> checkedBoards(bingoSimulation.boards.size(), false);

	for (int i = 0; i < bingoSimulation.numbers.size(); ++i)
	{
		for (int j = 0; j < bingoSimulation.boards.size(); ++j)
		{
			if (checkedBoards[j])
				continue;

			for (int numberIndex = 0; numberIndex < bingoSimulation.boards[j].numbers.size(); ++numberIndex)
				if (bingoSimulation.boards[j].numbers[numberIndex] == bingoSimulation.numbers[i])
				{
					bingoSimulation.boards[j].completes[numberIndex] = true;
					break;
				}

			if (isBoardWinning(bingoSimulation.boards[j]))
			{
				worstWinningBoard = WinningBingoBoard{ bingoSimulation.boards[j], bingoSimulation.numbers[i] };
				checkedBoards[j] = true;
			}
		}
	}

	return worstWinningBoard;
}

int getScore(WinningBingoBoard winningBoard)
{
	int uncompletedSum = 0;
	for (int i = 0; i < 25; ++i)
		if (winningBoard.board.completes[i] == false)
			uncompletedSum += winningBoard.board.numbers[i];

	return uncompletedSum * winningBoard.winningNumber;
}

void Task4(std::string filename)
{
	BingoSimulationData bingoSimulation = readBingoSimulationData(filename);
	if (bingoSimulation.boards.size() == 0 || bingoSimulation.numbers.size() == 0)
		return;

	WinningBingoBoard bestWinningBoard = findBestBoard(bingoSimulation);
	WinningBingoBoard worstWinningBoard = findWorstBoard(bingoSimulation);

	std::cout << "Solution to task 4 (part1): " << getScore(bestWinningBoard) << std::endl;
	std::cout << "Solution to task 4 (part2): " << getScore(worstWinningBoard) << std::endl;
}