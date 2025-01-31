#include "Michi.h"

Michi::Michi() 
{
	for (int i = 0; i < Michi::MAX_LEN; i++) {
		choices.push_back(Michi::CHOICE_BLANK);
	}
	result = Michi::RESULT_NO_RESULT;
	nro_jugadas = 0;
}

void Michi::clear() 
{
	for (int i = 0; i < Michi::MAX_LEN; i++) {
		choices[i] = Michi::CHOICE_BLANK;
	}
	result = Michi::RESULT_NO_RESULT;
	nro_jugadas = 0;
}
void Michi::addChoice(int c, int index) 
{
	if (c == Michi::CHOICE_X || c == Michi::CHOICE_O) 
	{
		choices[index] = c;
		nro_jugadas++;
	}
}

int Michi::checkWinner()
{
	int result = Michi::RESULT_NO_RESULT;
	/*
		0|1|2
		3|4|5
		6|7|8

		x|0|x
		0|x|0
		x| |
	*/

	// Horizontal

	if ( (choices[0] == choices[1] && choices[1] == choices[2]) ) {
		result = checkResult(choices[0]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	if ((choices[3] == choices[4] && choices[4] == choices[5])) {
		result = checkResult(choices[3]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	if ((choices[6] == choices[7] && choices[7] == choices[8])) {
		result = checkResult(choices[6]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	// Vertical

	if ((choices[0] == choices[3] && choices[3] == choices[6])) {
		result = checkResult(choices[0]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	if ((choices[1] == choices[4] && choices[4] == choices[7])) {
		result = checkResult(choices[1]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	if ((choices[2] == choices[5] && choices[5] == choices[8])) {
		result = checkResult(choices[2]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	// Diagonal

	if ((choices[0] == choices[4] && choices[4] == choices[8])) {
		result = checkResult(choices[0]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	if ((choices[2] == choices[4] && choices[4] == choices[6])) {
		result = checkResult(choices[2]);
		if (result != Michi::RESULT_NO_RESULT)
			return result;
	}

	// Empate (solo puede haber empate cuando el nro de jugadas sea 9 y no haya ganador)

	if (result == Michi::RESULT_NO_RESULT && nro_jugadas == 9)
		return Michi::RESULT_TIE;

	return result;
}

int Michi::checkResult(int c) 
{
	int result = Michi::RESULT_NO_RESULT;
	if (c == Michi::CHOICE_X) {
		result = Michi::RESULT_WIN_X;
	}
	else if (c == Michi::CHOICE_O) {
		result = Michi::RESULT_WIN_O;
	}

	return result;
}

int Michi::jugadas() 
{
	return this->nro_jugadas;
}
