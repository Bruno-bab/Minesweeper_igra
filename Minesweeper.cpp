#include "Minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

bool field::getIs_bomb() const { return is_bomb; }

bool field::getIs_revealed() const { return is_revealed; }

std::string field::getUnrevealed_sign() const { return " [ ] "; }

std::string field::getRevealed_sign() const
{
	if (is_bomb)
		return " [X] ";
	else
		return " [" + std::to_string(touch_counter) + "] ";
}

int field::getTouch_counter() const { return touch_counter; }


void field::setTouch_counter(int count) { touch_counter = count; }

void field::setIsRevealed(bool revealed_c) { is_revealed = revealed_c; }

void field::setIs_bomb(bool bomb_c) { is_bomb = bomb_c; }

std::vector<std::vector<field>> fill(int d, int random_count)
{
	std::vector<std::vector<field>> matrix(d, std::vector<field>(d)); //popunjava matricu sa field klasom

	srand(time(0));

	int counter = 0;
	while (counter < random_count)
	{
		int random_i = rand() % d;
		int random_j = rand() % d;

		if (!(matrix[random_i][random_j]).getIs_bomb())
		{
			matrix[random_i][random_j].setIs_bomb(true);
			counter++;
		}
	}

	for (int i = 0; i < d; ++i) //touch counter se povecava ako polje dira bombu
	{
		for (int j = 0; j < d; ++j)
		{
			int count = bomb_touching(matrix, d, i, j);
			matrix[i][j].setTouch_counter(count);
		}
	}

	return matrix;
}

void print_matrix(const std::vector<std::vector<field>>& matrix, int d, std::ostream& os) //ispisuje matricu zajdno sa x i y koordinatama
{
	os << " ";
	for (int i = 0; i < d; ++i)
	{
		if (i > 9)
			os << "   " << i;
		else
			os << "    " << i;
	}

	os << "\n  ";
	for (int i = 0; i < d; ++i)
		os << "_____";
	os << "\n0 |";

	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (!matrix[i][j].getIs_revealed()) //ovisno da li je polje otvoreno, ispisuje se njegovo stanje
				os << matrix[i][j].getUnrevealed_sign();
			else
				os << matrix[i][j].getRevealed_sign();
		}
		if (i < d - 1)
		{
			os << "\n  |\n";
			if (i >= 9)
				os << i + 1 << "|";
			else
				os << i + 1 << " |";
		}
	}
}

int bomb_touching(const std::vector<std::vector<field>>& matrix, int d, int x, int y) //broji koliko se bombi nalazi u 8 polja oko odabranog polja
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
				if (matrix[x2][y2].getIs_bomb())
					bomb_counter++;
			}
		}
	}

	return bomb_counter;
}

std::vector<std::vector<field>> reveal_matrix(std::vector<std::vector<field>>& matrix, int d, int x, int y)
{
	if (x < 0 || x >= d || y < 0 || y >= d) //provjera da li se izaslo iz matrice
		return matrix;

	if (matrix[x][y].getIs_revealed()) //ako je polje vec bilo odabrano nista se ne dogada
		return matrix;

	matrix[x][y].setIsRevealed(true); //mjenja stanje odabranog polja na otvoreno

	if (matrix[x][y].getIs_bomb()) //ako je odabrano polje sva se polja otvaraju
	{
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				matrix[i][j].setIsRevealed(true);
		return matrix;
	}

	if (matrix[x][y].getTouch_counter() == 0) //ako je odabrano polje koje ne dira bombu, otvaraju se 8 polja oko njega
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

bool game_over(const std::vector<std::vector<field>>& matrix, int d, std::ostream& os) //govori korisniku da li je igra gotova ovisno da li je pobjedio ili izgubio
{
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (!(matrix[i][j].getIs_bomb()) && (!(matrix[i][j].getIs_revealed())))
				return false;
			if (matrix[i][j].getIs_bomb() && (matrix[i][j].getIs_revealed()))
			{
				os << "\nGAME OVER\nYOU LOSE\n";
				return true;
			}
		}
	}
	os << "\nYOU WIN\n";
	return true;
}