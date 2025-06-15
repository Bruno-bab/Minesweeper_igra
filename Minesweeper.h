#pragma once

#include <iostream>
#include <string> 
#include <array>
#include <vector>

class field
{
protected:
	int touch_counter = 0;
	bool is_bomb = 0;
	bool is_revealed = 0;
	std::string unrevealed_sign = " [ ] ";
	std::string revealed_sign;
	void updateRevealedSign();
public:
	field() { updateRevealedSign(); }
	virtual ~field() {}

	std::string getUnrevealed_sign();
	virtual std::string getRevealed_sign();
	virtual bool getIs_bomb();
	bool getIs_revealed();
	int getTouch_counter();

	void setTouch_counter(int count);
	void setRevealed_sign(std::string rsign);
	void setIsRevealed(bool revealed_c);
};

class bomb : public field
{
public:
	bomb() { is_bomb = true; } 
	bool getIs_bomb() override;
	std::string getRevealed_sign() override;
};

std::vector<std::vector<field*>> fill(int d, int random_count);

void print_matrix(std::vector<std::vector<field*>> matrix, int d);

int bomb_touching(std::vector<std::vector<field*>> matrix, int d, int x, int y);

std::vector<std::vector<field*>> reveal_matrix(std::vector<std::vector<field*>> matrix, int d, int x, int y);

bool game_over(std::vector<std::vector<field*>> matrix, int d);
