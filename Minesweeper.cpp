#include "Minesweeper.h"
#include <cstdlib>;
#include <ctime>;
#include <array>
#include <vector>


bool field::getIs_bomb() { return is_bomb; };

std::string field::getUnrevealed_sign() { return unrevealed_sign; }

std::string field::getRevealed_sign() { return revealed_sign; }

std::string bomb::getRevealed_sign() { return revealed_sign; }

field*** fill(int d)
{
	field*** matrix = new field * *[d];
	for (int i = 0; i < d; ++i)
	{
		matrix[i] = new field * [d];
		for (int j = 0; j < d; ++j)
		{
			matrix[i][j] = new field();
		}
	}

	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
			matrix[i][j] = new field();
	}

	srand(time(0));
	int random_count;
	switch (d)
	{
	case 20:
		random_count = 16;
		break;
	case 10:
		random_count = 7;
		break;
	case 5:
		random_count = 3;
		break;
	}

	for (int j = 0; j < random_count; ++j)
	{
			int random_i = rand() % d;
			int random_j = rand() % d;

			if (!(matrix[random_i][random_j])->getIs_bomb())
			{
				delete matrix[random_i][random_j];
				matrix[random_i][random_j] = new bomb();
			}
			else
				continue;
	}
	return matrix;
}

void print_matrix(field*** matrix, int d)
{
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			std::cout << matrix[i][j]->getRevealed_sign();
		}
		std::cout << "\n" << "\n";
	}
}

