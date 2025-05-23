#include "Minesweeper.h"
#include <cstdlib>;
#include <ctime>;

bool field::getIs_bomb() { return is_bomb; };

std::string field::getRevealed_sign() { return revealed_sign; }

std::string bomb::getRevealed_sign() { return revealed_sign; }

void fill()
{
	field* array[10][10];
	int random_counter = 0;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			array[i][j] = new field();
		}
	}

	for (int j = 0; j < 6; ++j)
	{
			srand(time(0));
			int random_i = rand() % 10;
			int random_j = rand() % 10;

			if (!(array[random_i][random_j]->getIs_bomb()))
			{
				delete array[random_i][random_j];
				array[random_i][random_j] = new bomb();
			}
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << array[i][j]->getRevealed_sign();
		}
		std::cout << "\n" << "\n";
	}

}
