#include "Minesweeper.h"

int main()
{
	while (true)
	{
		int d = 10;
		bool i;
		field*** matrix = fill(d);
		print_matrix(matrix, d);

		while (true)
		{
			if (game_over(matrix, d))
				break;
			std::cout << "\n\n";
			int x, y;
			std::cout << "X coordinate: ";
			std::cin >> x;
			std::cout << "\n";
			std::cout << "Y coordinate: ";
			std::cin >> y;
			std::cout << "\n\n";
			reveal_matrix(matrix, d, x, y);
			print_matrix(matrix, d);
		}
		std::cout << "\nPLAY AGAIN?\n";
		std::cin >> i;
		if (!i)
			break;
	}
}
