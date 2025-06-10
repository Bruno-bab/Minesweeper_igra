#include "Minesweeper.h"

int main()
{
	while (1)
	{
		bool i;
		int n;
		int size, bomb_c;
		
		std::cout << "\nEasy mode (0)\nNormal mode (1)\nHard mode (2)\nCustom game (3)\n";
		std::cin >> n;
		if (n < 0 || n > 3)
			continue;

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
			while (1)
			{
				std::cout << "\nGame size: ";
				std::cin >> size;
				if (!(size < 1 || size > 99))
					break;
			}
			while (1)
			{
				std::cout << "\nNumber of bombs: ";
				std::cin >> bomb_c;
				if (!(bomb_c < 0 || bomb_c > size * size))
					break;
			}
		}
		
		field*** matrix = fill(size, bomb_c);
		print_matrix(matrix, size);

		while (1)
		{
			if (game_over(matrix, size))
				break;
			std::cout << "\n\n";
			int x, y;
			while (1)
			{
				std::cout << "\nX coordinate (row): ";
				std::cin >> x;
				if (!(x < 0 || x > size - 1))
					break;
			}
			while (1)
			{
				std::cout << "\nY coordinate (column): ";
				std::cin >> y;
				if (!(y < 0 || y > size - 1))
					break;
			}
			std::cout << "\n\n";
			reveal_matrix(matrix, size, x, y);
			print_matrix(matrix, size);
		}

		std::cout << "\nPLAY AGAIN? YES(0)  NO(1)\n";
		std::cin >> i;
		if (i)
			break;
	}
}
