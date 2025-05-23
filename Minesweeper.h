#pragma once

#include <iostream>
#include <string> 

class field
{
private:
	int touch_counter = 0;
	bool is_bomb = 0;
	std::string unreaveled_sign = " [ ] ";
	std::string revealed_sign = " [" + std::to_string(touch_counter) + "] ";
public:
	virtual std::string getRevealed_sign();
	bool getIs_bomb();
	bool is_revealed = 0;

};

class bomb : public field
{
private:
	bool is_bomb = 1;
	std::string revealed_sign = " [X] ";
public:
	std::string getRevealed_sign() override;
};

void fill();