#include "CppUnitTest.h"
#include "..\Minesweeper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForMinesweeper
{
	TEST_CLASS(Classes_Tests)
	{
	public:
		
		TEST_METHOD(Default_Values)
		{
			field f;

			Assert::AreEqual(false, f.getIs_bomb());
			Assert::AreEqual(false, f.getIs_revealed());
			Assert::AreEqual(0, f.getTouch_counter());
			Assert::AreEqual(std::string(" [ ] "), f.getUnrevealed_sign());
			Assert::AreEqual(std::string(" [0] "), f.getRevealed_sign());
		}

		TEST_METHOD(Field_Setters)
		{
			field f;
			f.setTouch_counter(3);
			f.setIsRevealed(true);
			f.setRevealed_sign(" [3] ");

			Assert::AreEqual(3, f.getTouch_counter());
			Assert::AreEqual(true, f.getIs_revealed());
			Assert::AreEqual(std::string(" [3] "), f.getRevealed_sign());
		}

		TEST_METHOD(Bomb_Override)
		{
			field* f = new bomb();

			Assert::AreEqual(true, f->getIs_bomb());
			Assert::AreEqual(std::string(" [X] "), f->getRevealed_sign());
		}
	};

	TEST_CLASS(Fill_Tests)
	{
	public:

		TEST_METHOD(Fill_Test)
		{
			int d = 5;
			field*** matrix = fill(d);

			int bombCount = 0;
			for (int i = 0; i < d; ++i)
			{
				Assert::IsNotNull(matrix[i]);
				for (int j = 0; j < d; ++j)
				{
					Assert::IsNotNull(matrix[i][j]);
					if (matrix[i][j]->getIs_bomb())
						bombCount++;
				}
			}

			Assert::AreEqual(2, bombCount);
		}
	};
}
