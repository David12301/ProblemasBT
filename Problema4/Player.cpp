#include "Player.h"

const string Player::HIGH_CARD = "HIGH CARD";
const string Player::ONE_PAIR = "Par de";
const string Player::TWO_PAIRS = "TWO PAIRS";
const string Player::THREE_OF_A_KIND = "THREE OF A KIND";
const string Player::STRAIGHT = "STRAIGHT";
const string Player::FLUSH = "FLUSH";
const string Player::FULL_HOUSE = "FULL HOUSE";
const string Player::FOUR_OF_A_KIND = "FOUR OF A KIND";
const string Player::STRAIGHT_FLUSH = "STRAIGHT FLUSH";
const string Player::ROYAL_FLUSH = "ROYAL FLUSH";

Player::Player() 
{
	hand = new Card[5];
}

Player::~Player() 
{
	delete[] hand;
}

string Player::resolveHand() 
{
	string result = "";

	return result;
}