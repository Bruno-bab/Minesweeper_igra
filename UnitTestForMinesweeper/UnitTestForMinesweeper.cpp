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
			f.setRevealed_sign(" [3] ");

			Assert::AreEqual(3, f.getTouch_counter());
			Assert::AreEqual(true, f.getIs_revealed());
			Assert::AreEqual(std::string(" [3] "), f.getRevealed_sign());
		}

		TEST_METHOD(Bomb_override)
		{
			field* f = new bomb();

			Assert::AreEqual(true, f->getIs_bomb());
			Assert::AreEqual(std::string(" [X] "), f->getRevealed_sign());
		}
	};

	TEST_CLASS(Fill_Tests)
	{
	public:
		TEST_METHOD(Matrix_size_and_bomb_count)
		{
			int d = 5;
			int bombCount = 2;
			std::vector<std::vector<field*>> matrix = fill(d, bombCount);
			for (int i = 0; i < d; ++i)
			{
				for (int j = 0; j < d; ++j)
					Assert::IsNotNull(matrix[i][j]);
			}
			int real_bomb_count = 0;
			for (int i = 0; i < d; ++i)
			{
				for (int j = 0; j < d; ++j)
				{
					if (matrix[i][j]->getIs_bomb())
						real_bomb_count++;
				}
			}

			Assert::AreEqual(bombCount, real_bomb_count);
		}
	};

	TEST_CLASS(Bomb_Touching_Tests)
	{
	public:
		TEST_METHOD(Bomb_touching_count)
		{
			int d = 5;
			std::vector<std::vector<field*>> matrix(d, std::vector<field*>(d));
			for (int i = 0; i < d; i++)
			{
				for (int j = 0; j < d; j++)
					matrix[i][j] = new field();
			}
			delete matrix[0][1];
			matrix[0][1] = new bomb();
			delete matrix[1][1];
			matrix[1][1] = new bomb();
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
			std::vector<std::vector<field*>> matrix(d, std::vector<field*>(d));
			for (int i = 0; i < d; i++)
			{
				for (int j = 0; j < d; j++)
					matrix[i][j] = new field();
			}
			delete matrix[0][0];
			matrix[0][0] = new bomb();
			reveal_matrix(matrix, d, 0, 0);

			for (int i = 0; i < d; i++)
			{
				for (int j = 0; j < d; j++)
					Assert::IsTrue(matrix[i][j]->getIs_revealed());
			}
		}
	};

	TEST_CLASS(Game_Over_Tests)
	{
	public:
		TEST_METHOD(Return_0_if_not_all_revealed)
		{
			int d = 5;
			std::vector<std::vector<field*>> matrix(d, std::vector<field*>(d));
			for (int i = 0; i < d; ++i)
			{
				for (int j = 0; j < d; ++j)
					matrix[i][j] = new field();
			}
			matrix[0][0]->setIsRevealed(true); 

			Assert::IsFalse(game_over(matrix, d));
		}

		TEST_METHOD(Return_1_if_bomb_is_revealed)
		{
			int d = 5;
			std::vector<std::vector<field*>> matrix(d, std::vector<field*>(d));
			for (int i = 0; i < d; i++)
			{
				for (int j = 0; j < d; j++)
					matrix[i][j] = new field();
			}
			delete matrix[0][0];
			matrix[0][0] = new bomb();
			matrix[0][0]->setIsRevealed(true);

			Assert::IsTrue(game_over(matrix, d));
		}
	};
}
