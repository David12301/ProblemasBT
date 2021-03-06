#pragma once

#include <vector>

class Michi 
{
private:
	std::vector<int> choices;
	int result;
	unsigned int nro_jugadas;

	int checkResult(int c);
public:
	Michi();

	const static int CHOICE_BLANK = 0;
	const static int CHOICE_X = 1;
	const static int CHOICE_O = 2;

	const static int RESULT_NO_RESULT = 0;
	const static int RESULT_WIN_X = 1;
	const static int RESULT_WIN_O = 2;
	const static int RESULT_TIE = 3;

	const static int MAX_LEN = 9;
	
	void addChoice(int c, int index);
	int checkWinner();
	int jugadas();
	void clear();

};