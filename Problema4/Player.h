#pragma once
#include "Card.h"
#include <string>
using namespace std;

class Player {
public:

	Player();
	~Player();
	Card* hand;

	string resolveHand();

	const static string HIGH_CARD;
	const static string ONE_PAIR;
	const static string TWO_PAIRS;
	const static string THREE_OF_A_KIND;
	const static string STRAIGHT;
	const static string FLUSH;
	const static string FULL_HOUSE;
	const static string FOUR_OF_A_KIND;
	const static string STRAIGHT_FLUSH;
	const static string ROYAL_FLUSH;

};