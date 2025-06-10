#pragma once

#include <iostream>
#include <string> 
#include <array>

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

field*** fill(int d, int random_count);

void print_matrix(field*** matrix, int d);

int bomb_touching(field*** matrix, int d, int x, int y);

field*** reveal_matrix(field*** matrix, int d, int x, int y);

bool game_over(field*** matrix, int d);
