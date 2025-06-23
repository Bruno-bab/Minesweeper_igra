#include "Minesweeper.h"
#include <limits>
#include <iostream>

int main()
{
	while (true)
	{
		std::cout << "\nEasy mode (2 bombs) -> 0\nNormal mode (10 bombs) -> 1\nHard mode (25 bombs) -> 2\nCustom game -> 3\n";
		int mode = game_mode();
		int size, bomb_c;

		switch (mode)
		{
		case 0:
			size = 5;
			bomb_c = 2;
			break;
		case 1:
			size = 10;
			bomb_c = 10;
			break;
		case 2:
			size = 15;
			bomb_c = 25;
			break;
		case 3:
			std::cout << "\nGame size: ";
			size = game_size();

			std::cout << "\nNumber of bombs: ";
			bomb_c = bomb_number(size);
		}

		std::vector<std::vector<field>> matrix = fill(size, bomb_c);
		print_matrix(matrix, size, std::cout);

		while (true)
		{
			if (game_end(matrix, size, std::cout))
				break;
			std::cout << "\n\n";

			std::cout << "\nX coordinate (row): ";
			int x = x_coordinate(size);

			std::cout << "\nY coordinate (column): ";
			int y = y_coordinate(size);

			std::cout << "\n\n";
			reveal_matrix(matrix, size, x, y);
			print_matrix(matrix, size, std::cout);
		}

		std::cout << "\nPLAY AGAIN? YES(0)  NO(1)\n";
		bool over = game_over();
		if (over)
			break;
	}
}