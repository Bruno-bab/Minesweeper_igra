#include "Minesweeper.h"
#include <limits>
#include <iostream>

int main()
{
	while (true)
	{
		int mode;
		char c;

		std::cout << "\nEasy mode (2 bombs) -> 0\nNormal mode (10 bombs) -> 1\nHard mode (25 bombs) -> 2\nCustom game -> 3\n";
		while (true)
		{
			if ((std::cin >> mode) && (std::cin.peek() == '\n') && mode >= 0 && mode <= 3)
				break;
			std::cout << "\nEnter an integer between 0 and 3: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

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
			while (true)
			{
				if ((std::cin >> size) && (std::cin.peek() == '\n') && size >= 1 && size <= 99)
					break;
				std::cout << "\nEnter an integer between 1 and 99: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\nNumber of bombs: ";
			while (true)
			{
				if ((std::cin >> bomb_c) && (std::cin.peek() == '\n') && bomb_c >= 1 && bomb_c <= (size * size) - 1)
					break;
				std::cout << "\nEnter an integer between 1 and " << (size * size) - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		std::vector<std::vector<field>> matrix = fill(size, bomb_c);
		print_matrix(matrix, size, std::cout);

		while (true)
		{
			if (game_over(matrix, size, std::cout))
				break;
			std::cout << "\n\n";
			int x, y;

			std::cout << "\nX coordinate (row): ";
			while (true)
			{
				if ((std::cin >> x) && (std::cin.peek() == '\n') && x >= 0 && x <= size - 1)
					break;
				std::cout << "\nEnter an integer between 0 and " << size - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\nY coordinate (column): ";
			while (true)
			{
				if ((std::cin >> y) && (std::cin.peek() == '\n') && y >= 0 && y <= size - 1)
					break;
				std::cout << "\nEnter an integer between 0 and " << size - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\n\n";
			reveal_matrix(matrix, size, x, y);
			print_matrix(matrix, size, std::cout);
		}

		bool over;

		std::cout << "\nPLAY AGAIN? YES(0)  NO(1)\n";
		while (true)
		{
			if ((std::cin >> over) && (std::cin.peek() == '\n'))
				break;
			std::cout << "\nEnter 1 or 0: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (over)
			break;
	}
}