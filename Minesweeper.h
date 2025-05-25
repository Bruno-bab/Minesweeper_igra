#pragma once

#include <iostream>
#include <string> 
#include <array>

class field
{
private:
	int touch_counter = 0;
	bool is_bomb = 0;
	std::string unrevealed_sign = " [ ] ";
	std::string revealed_sign = " [" + std::to_string(touch_counter) + "] ";
public:
	std::string getUnrevealed_sign();
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

field*** fill(int d);
void print_matrix(field*** matrix, int d);