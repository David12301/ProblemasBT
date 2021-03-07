#pragma once
#include <string>
using namespace std;

class Card {
public:
	Card() {
		val = type = 0;
	}

	char type;
	char val;

	const static string CARD_TYPE_CLUB;
	const static string CARD_TYPE_SPADE;
	const static string CARD_TYPE_HEART;
	const static string CARD_TYPE_DIAMOND;
};

