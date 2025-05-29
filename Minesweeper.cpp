#include "Minesweeper.h"
#include <cstdlib>;
#include <ctime>;
#include <array>
#include <vector>


bool field::getIs_bomb() { return 0; }

bool field::getIs_revealed() { return is_revealed; }

std::string field::getUnrevealed_sign() { return unrevealed_sign; }

std::string field::getRevealed_sign() { return revealed_sign; }

std::string bomb::getRevealed_sign() { return " [X] "; }

bool bomb::getIs_bomb() { return 1; };

int field::getTouch_counter() { return touch_counter; }

void field::setTouch_counter(int count)
{ 
	touch_counter = count;
	updateRevealedSign();
}

void field::setRevealed_sign(std::string rsign) { revealed_sign = rsign; }

void field::setIsRevealed(bool revealed_c) { is_revealed = revealed_c; }

void field::updateRevealedSign() { revealed_sign = " [" + std::to_string(touch_counter) + "] "; }

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

	srand(time(0));
	int random_count;
	switch (d)
	{
	case 20:
		random_count = 45;
		break;
	case 10:
		random_count = 10;
		break;
	case 5:
		random_count = 2;
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
	std::cout << " ";
	for (int i = 0; i < d; ++i)
	{
		std::cout << "    " << i;
	}
	std::cout << "\n  ";
	for (int i = 0; i < d; ++i)
	{
		std::cout << "_____";
	}
	std::cout << "\n0 |";
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (!matrix[i][j]->getIs_revealed())
				std::cout << matrix[i][j]->getUnrevealed_sign();
			else
				std::cout << matrix[i][j]->getRevealed_sign();
		}
		if (i < d - 1)
		{
			std::cout << "\n  |\n";
			std::cout << i + 1 << " |";
		}
	}
}

field*** reveal_matrix(field*** matrix, int d, int x, int y)
{
	if (!matrix[x][y]->getIs_revealed())
	{
		matrix[x][y]->setIsRevealed(1);
	}
	return matrix;
}

