#pragma once

#include <string> 
#include <vector>

class field
{
private:
	int touch_counter = 0;
	bool is_bomb = false;
	bool is_revealed = false;
	std::string revealed_sign;
public:
	std::string getUnrevealed_sign() const;
	std::string getRevealed_sign() const;
	bool getIs_bomb() const;
	bool getIs_revealed() const;
	int getTouch_counter() const;

	void setTouch_counter(int count);
	void setIsRevealed(bool revealed_c);
	void setIs_bomb(bool bomb_c);
};

std::vector<std::vector<field>> fill(int d, int random_count);

void print_matrix(const std::vector<std::vector<field>>& matrix, int d, std::ostream& os);

int bomb_touching(const std::vector<std::vector<field>>& matrix, int d, int x, int y);

std::vector<std::vector<field>> reveal_matrix(std::vector<std::vector<field>>& matrix, int d, int x, int y);

bool game_over(const std::vector<std::vector<field>>& matrix, int d, std::ostream& os);