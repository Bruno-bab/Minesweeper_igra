#pragma once

#include <iostream>
#include <string> 
#include <array>
#include <vector>

class field
{
protected:
	int touch_counter = 0;
	bool is_bomb;
	bool is_revealed = false;
	std::string unrevealed_sign = " [ ] ";
	std::string revealed_sign;
public:
	field()
	{
		is_bomb = false;
	}
	virtual ~field() {}

	std::string getUnrevealed_sign() const;
	std::string getRevealed_sign() const;
	bool getIs_bomb() const;
	bool getIs_revealed() const;
	int getTouch_counter() const;

	void setTouch_counter(int count);
	void setRevealed_sign(std::string rsign);
	void setIsRevealed(bool revealed_c);
	void setIs_bomb(bool bomb_c);
};

std::vector<std::vector<field>> fill(int d, int random_count);

void print_matrix(const std::vector<std::vector<field>>& matrix, int d);

int bomb_touching(const std::vector<std::vector<field>>& matrix, int d, int x, int y);

std::vector<std::vector<field>> reveal_matrix(std::vector<std::vector<field>>& matrix, int d, int x, int y);

bool game_over(const std::vector<std::vector<field>>& matrix, int d);