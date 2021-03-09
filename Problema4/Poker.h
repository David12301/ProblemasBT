#pragma once
#include "Player.h"
#include <vector>

class Poker {
public:
	vector<Player> players;
	const static int MAX_NUMBER_OF_PLAYERS = 2;

	Poker();
	void loadGamesFromFile(string in_fname, string out_fname);
	string str_hand_kind(GameResult p);

};