#pragma once
#include "Card.h"
#include "GameResult.h"
#include <string>
using namespace std;

class Player {
public:

	Player();
	~Player();

	const static int MAX_HAND_SIZE = 5;
	Card hand[MAX_HAND_SIZE];

	GameResult resolveHand();
	void clearHand();
	int countValue(char val);
	int countType(char type);
	char allSameType();
	bool hasStraight();
	char hasNRepeat(int n, char except=false);
	char iTocval(int i);
	int aToival(char c);
	int valorMaximo();
	string getHandStr();

	const static string STR_HIGH_CARD;
	const static string STR_ONE_PAIR;
	const static string STR_TWO_PAIRS;
	const static string STR_THREE_OF_A_KIND;
	const static string STR_STRAIGHT;
	const static string STR_FLUSH;
	const static string STR_FULL_HOUSE;
	const static string STR_FOUR_OF_A_KIND;
	const static string STR_STRAIGHT_FLUSH;
	const static string STR_ROYAL_FLUSH;

	const static int HIGH_CARD = 1;
	const static int ONE_PAIR = 2;
	const static int TWO_PAIRS = 3;
	const static int THREE_OF_A_KIND = 4;
	const static int STRAIGHT = 5;
	const static int FLUSH = 6;
	const static int FULL_HOUSE = 7;
	const static int FOUR_OF_A_KIND = 8;
	const static int STRAIGHT_FLUSH = 9;
	const static int ROYAL_FLUSH = 10;

};