#include "Minesweeper.h"
#include <limits>

int main()
{
	while (1)
	{
		bool i;
		int n;
		char c;
		int size, bomb_c;
		
		std::cout << "\nEasy mode (2 bombs) -> 0\nNormal mode (10 bombs) -> 1\nHard mode (25 bombs) -> 2\nCustom game -> 3\n";
		while (1)
		{
			if ((std::cin >> n) && (std::cin.peek() == '\n') && n >= 0 && n <= 3)
				break;
			std::cout << "\nEnter an integer between 0 and 3: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		switch (n)
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
			while (1)
			{
				if ((std::cin >> size) && (std::cin.peek() == '\n') && size >= 1 && size <= 99)
					break;
				std::cout << "\nEnter an integer between 1 and 99: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\nNumber of bombs: ";
			while (1)
			{
				if ((std::cin >> bomb_c) && (std::cin.peek() == '\n') && bomb_c >= 1 && bomb_c <= (size * size) - 1)
					break;
				std::cout << "\nEnter an integer between 1 and " << (size * size) - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		
		std::vector<std::vector<field*>> matrix = fill(size, bomb_c);
		print_matrix(matrix, size);

		while (1)
		{
			if (game_over(matrix, size))
				break;
			std::cout << "\n\n";
			int x, y;

			std::cout << "\nX coordinate (row): ";
			while (1)
			{
				if ((std::cin >> x) && (std::cin.peek() == '\n') && x >= 0 && x <= size - 1)
					break;
				std::cout << "\nEnter an integer between 0 and " << size - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\nY coordinate (column): ";
			while (1)
			{
				if ((std::cin >> y) && (std::cin.peek() == '\n') && y >= 0 && y <= size - 1)
					break;
				std::cout << "\nEnter an integer between 0 and " << size - 1 << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "\n\n";
			reveal_matrix(matrix, size, x, y);
			print_matrix(matrix, size);
		}

		std::cout << "\nPLAY AGAIN? YES(0)  NO(1)\n";
		while (1)
		{
			if ((std::cin >> i) && (std::cin.peek() == '\n') && i >= 0 && i <= 1)
				break;
			std::cout << "\nEnter 1 or 0 ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (i)
			break;
	}
}
