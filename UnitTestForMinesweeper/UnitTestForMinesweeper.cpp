#include "CppUnitTest.h"
#include "..\Minesweeper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForMinesweeper
{
	TEST_CLASS(Classes_Tests)
	{
	public:
		field f;
		TEST_METHOD(Default_values)
		{
			Assert::AreEqual(false, f.getIs_bomb());
			Assert::AreEqual(false, f.getIs_revealed());
			Assert::AreEqual(0, f.getTouch_counter());
			Assert::AreEqual(std::string(" [ ] "), f.getUnrevealed_sign());
			Assert::AreEqual(std::string(" [0] "), f.getRevealed_sign());
		}

		TEST_METHOD(Field_setters)
		{
			f.setTouch_counter(3);
			f.setIsRevealed(true);

			Assert::AreEqual(3, f.getTouch_counter());
			Assert::AreEqual(true, f.getIs_revealed());
		}

		TEST_METHOD(Bomb_override)
		{
			field f;
			f.setIs_bomb(true);
			Assert::AreEqual(true, f.getIs_bomb());
			Assert::AreEqual(std::string(" [X] "), f.getRevealed_sign());
		}
	};

	TEST_CLASS(Fill_Tests)
	{
	public:
		TEST_METHOD(Matrix_size_and_bomb_count)
		{
			int d = 5;
			int bombCount = 2;
			std::vector<std::vector<field>> matrix = fill(d, bombCount);
			int real_bomb_count = 0;
			for (int i = 0; i < d; ++i)
			{
				for (int j = 0; j < d; ++j)
				{
					if (matrix[i][j].getIs_bomb())
						real_bomb_count++;
				}
			}

			Assert::AreEqual(bombCount, real_bomb_count);
		}
	};

	TEST_CLASS(Print_Matrix_Tests)
	{
	public:
		TEST_METHOD(Print_unrevealed)
		{
			std::vector<std::vector<field>> matrix = fill(5, 2);
			std::stringstream ss;
			print_matrix(matrix, 5, ss);
			std::string printed_matrix =
				"     0    1    2    3    4\n"
				"  _________________________\n"
				"0 | [ ]  [ ]  [ ]  [ ]  [ ] \n"
				"  |\n"
				"1 | [ ]  [ ]  [ ]  [ ]  [ ] \n"
				"  |\n"
				"2 | [ ]  [ ]  [ ]  [ ]  [ ] \n"
				"  |\n"
				"3 | [ ]  [ ]  [ ]  [ ]  [ ] \n"
				"  |\n"
				"4 | [ ]  [ ]  [ ]  [ ]  [ ] ";

			Assert::AreEqual(printed_matrix, ss.str());
		}

		TEST_METHOD(Print_revealed)
		{
			std::vector<std::vector<field>> matrix = fill(3, 0);
			matrix[1][1].setIsRevealed(true);
			std::stringstream ss;
			print_matrix(matrix, 3, ss);
			std::string printed_matrix =
				"     0    1    2\n"
				"  _______________\n"
				"0 | [ ]  [ ]  [ ] \n"
				"  |\n"
				"1 | [ ]  [0]  [ ] \n"
				"  |\n"
				"2 | [ ]  [ ]  [ ] ";

			Assert::AreEqual(printed_matrix, ss.str());
		}
		
	};


	TEST_CLASS(Bomb_Touching_Tests)
	{
	public:
		TEST_METHOD(Bomb_touching_count)
		{
			int d = 5;
			std::vector<std::vector<field>> matrix(d, std::vector<field>(d));
			matrix[0][1].setIs_bomb(true);
			matrix[1][1].setIs_bomb(true);
			int count = bomb_touching(matrix, d, 1, 0);

			Assert::AreEqual(2, count);
		}
	};

	TEST_CLASS(Reveal_Matrix_Tests)
	{
	public:
		TEST_METHOD(Reveal_all_if_bomb_is_chosen)
		{
			int d = 5;
			std::vector<std::vector<field>> matrix(d, std::vector<field>(d));
			matrix[0][0].setIs_bomb(true);
			reveal_matrix(matrix, d, 0, 0);

			for (int i = 0; i < d; i++)
			{
				for (int j = 0; j < d; j++)
					Assert::IsTrue(matrix[i][j].getIs_revealed());
			}
		}
	};

	TEST_CLASS(Game_Over_Tests)
	{
	public:
		TEST_METHOD(Return_0_if_not_all_revealed)
		{
			int d = 5;
			std::stringstream ss;
			std::vector<std::vector<field>> matrix(d, std::vector<field>(d));
			matrix[0][0].setIsRevealed(true);
			Assert::IsFalse(game_over(matrix, d, ss));
		}

		TEST_METHOD(You_lose)
		{
			int d = 5;
			std::vector<std::vector<field>> matrix(d, std::vector<field>(d));
			matrix[0][0].setIs_bomb(true);
			matrix[0][0].setIsRevealed(true);
			std::stringstream ss;
			std::string lost = "\nGAME OVER\nYOU LOSE\n";

			Assert::IsTrue(game_over(matrix, d, ss));
			Assert::AreEqual(lost, ss.str());
		}

		TEST_METHOD(You_win)
		{
			int d = 2;
			std::vector<std::vector<field>> matrix(d, std::vector<field>(d));
			matrix[0][0].setIs_bomb(true);
			matrix[0][1].setIsRevealed(true);
			matrix[1][0].setIsRevealed(true);
			matrix[1][1].setIsRevealed(true);
			std::stringstream ss;
			std::string lost = "\nYOU WIN\n";

			Assert::IsTrue(game_over(matrix, d, ss));
			Assert::AreEqual(lost, ss.str());
		}
	};
}
