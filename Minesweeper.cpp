#include "Minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <array>

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

field*** fill(int d, int random_count)
{
	field*** matrix = new field * *[d]; //popunjava matricu sa field klasom
	for (int i = 0; i < d; ++i)
	{
		matrix[i] = new field * [d];
		for (int j = 0; j < d; ++j)
			matrix[i][j] = new field();
	}

	srand(time(0));

	for (int j = 0; j < random_count; ++j) //na nasumicnim mjestima se brise field klasa i mjenja se bomb klasom
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

	for (int i = 0; i < d; ++i) //touch counter se povecava ako polje dira bombu
	{
		for (int j = 0; j < d; ++j)
		{
			int count = bomb_touching(matrix, d, i, j);
			matrix[i][j]->setTouch_counter(count);
		}
	}

	return matrix;
}

void print_matrix(field*** matrix, int d) //ispisuje matricu zajdno sa x i y koordinatama
{
	std::cout << " ";
	for (int i = 0; i < d; ++i)
	{
		if (i > 9)
			std::cout << "   " << i;
		else
			std::cout << "    " << i;
	}

	std::cout << "\n  ";
	for (int i = 0; i < d; ++i)
		std::cout << "_____";
	std::cout << "\n0 |";

	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (!matrix[i][j]->getIs_revealed()) //ovisno da li je polje otvoreno, ispisuje se njegovo stanje
				std::cout << matrix[i][j]->getUnrevealed_sign();
			else
				std::cout << matrix[i][j]->getRevealed_sign();
		}
		if (i < d - 1)
		{
			std::cout << "\n  |\n";
			if (i >= 9)
				std::cout << i + 1 << "|";
			else
				std::cout << i + 1 << " |";
		}
	}
}

int bomb_touching(field*** matrix, int d, int x, int y) //broji koliko se bombi nalazi u 8 polja oko odabranog polja
{
	int bomb_counter = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			int x2 = x + i;
			int y2 = y + j;

			if (x2 >= 0 && x2 < d && y2 >= 0 && y2 < d)
			{
				if (matrix[x2][y2]->getIs_bomb())
					bomb_counter++;
			}
		}
	}
	
	return bomb_counter;
}

field*** reveal_matrix(field*** matrix, int d, int x, int y)
{
	if (x < 0 || x >= d || y < 0 || y >= d) //provjera da li se izaslo iz matrice
		return matrix;

	if (matrix[x][y]->getIs_revealed()) //ako je polje vec bilo odabrano nista se ne dogada
		return matrix;

	matrix[x][y]->setIsRevealed(1); //mjenja stanje odabranog polja na otvoreno

	if (matrix[x][y]->getIs_bomb()) //ako je odabrano polje sva se polja otvaraju
	{
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				matrix[i][j]->setIsRevealed(1);
		return matrix;
	}

	if (matrix[x][y]->getTouch_counter() == 0) //ako je odabrano polje koje ne dira bombu, otvaraju se 8 polja oko njega
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0)
					continue;
				reveal_matrix(matrix, d, x + i, y + j);
			}
		}
	}

	return matrix;
}

bool game_over(field*** matrix, int d) //govori korisniku da li je igra gotova ovisno da li je pobjedio ili izgubio
{
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (!(matrix[i][j]->getIs_bomb()) && (!(matrix[i][j]->getIs_revealed())))
				return 0;
			if (matrix[i][j]->getIs_bomb() && (matrix[i][j]->getIs_revealed()))
			{
				std::cout << "\nGAME OVER\nYOU LOSE\n";
				return 1;
			}
		}
	}
	std::cout << "\nYOU WIN\n";
	return 1;
}

