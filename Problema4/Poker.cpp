#include "Poker.h"
#include <fstream>
#include <sstream>
#include <iostream>


Poker::Poker() 
{
	for (int i = 0; i < Poker::MAX_NUMBER_OF_PLAYERS; i++)
	{
		Player p;
		players.push_back(p);
	}
}


void Poker::loadGamesFromFile(string in_fname, string out_fname) 
{
	ifstream infile(in_fname);
	string line;
	string result = "";
	result.reserve(1000000);
	result.clear();
	result.append("Mano        Jugador 1       Jugador 2           Ganador\n");
	int mano = 1;
	int j1 = 0;
	int j2 = 0;

	while (std::getline(infile, line)) {

		if (line == "") {
			break;
		}
		players[0].clearHand();
		players[1].clearHand();
		istringstream iss(line);
		string h = "";
		for (int i = 0, j = 0; i < (2 * Player::MAX_HAND_SIZE); i++) {
			iss >> h; // Lee hasta espacio en blanco, por lo tanto lee de 2 en 2 dejando un espacio

			if (i < Player::MAX_HAND_SIZE) {
				players[0].hand[i].val = h[0];
				players[0].hand[i].type = h[1];
			} else {
				players[1].hand[j].val = h[0];
				players[1].hand[j].type = h[1];
				j++;
			}
		}
		
		GameResult r1 = players[0].resolveHand();
		GameResult r2 = players[1].resolveHand();
		string strwinner = "";
		if (r1.hand_kind > r2.hand_kind) {
			strwinner = "Jugador 1";
			j1++;
		} else if (r1.hand_kind < r2.hand_kind) {
			strwinner = "Jugador 2";
			j2++;
		} else {
			//Si son iguales comparar el valor del tipo de mano primero
			int hv1 = players[0].aToival(r1.val_of_hk);
			int hv2 = players[1].aToival(r2.val_of_hk);
			if (hv1 > hv2) {
				strwinner = "Jugador 1";
				j1++;
			}
			else if (hv2 > hv1) {
				strwinner = "Jugador 2";
				j2++;
			}
			else {
				//Si son iguales comparar el valor maximo
				int v1 = players[0].valorMaximo();
				int v2 = players[1].valorMaximo();
				if (v1 > v2) {
					strwinner = "Jugador 1";
					j1++;
				}
				else if (v2 > v1) {
					strwinner = "Jugador 2";
					j2++;
				}
			}


			
		
		}

		result.append(std::to_string(mano));
		result.append("       ");
		result.append(players[0].getHandStr());
		result.append("     ");
		result.append(players[1].getHandStr());
		result.append("     ");
		result.append(strwinner);
		result.append("\n");

		string espacios = "";
		int manolen = std::to_string(mano).length();
		for (int i = 0; i < manolen; i++) {
			espacios += " ";
		}
		result.append(espacios);
		result.append("       ");

		string strres = str_hand_kind(r1);
		espacios = "";
		int espacios_len = 14 - strres.length() < 0 ? 0 : 14 - strres.length();
		for (int i = 0; i < espacios_len; i++) {
			espacios += " ";
		}
		result.append(strres);
		result.append(espacios);
		result.append("      ");

		strres = str_hand_kind(r2);
		result.append(strres);
		result.append("\n");

			
		mano++;
	}

	result.append("\n");
	result += "***********************************************************\n\n";
	result += "Nro victorias Jugador 1: " + std::to_string(j1) + "\n";
	result += "Nro victorias Jugador 2: " + std::to_string(j2) + "\n";

	ofstream ofs_archivo;
	ofs_archivo.open(out_fname, ios::trunc);
	ofs_archivo << result;
	ofs_archivo.close();

	string cmd = "notepad.exe " + out_fname;
	system(cmd.c_str());
	system("pause");
}

int Poker::checkWinner() 
{
	return 0;
}

string Poker::str_hand_kind(GameResult r)
{
	string result = "";

	if (r.hand_kind == Player::ROYAL_FLUSH) {
		result = Player::STR_ROYAL_FLUSH + r.mtype();
	}
	else if (r.hand_kind == Player::STRAIGHT_FLUSH) {
		result = Player::STR_STRAIGHT_FLUSH + r.mtype();
	}
	else if (r.hand_kind == Player::FOUR_OF_A_KIND) {
		result = Player::STR_FOUR_OF_A_KIND + r.mval();
	}
	else if (r.hand_kind == Player::FULL_HOUSE) {
		result = Player::STR_FULL_HOUSE + r.mval(r.max_val);
	}
	else if (r.hand_kind == Player::FLUSH) {
		result = Player::STR_FLUSH + r.mtype();
	}
	else if (r.hand_kind == Player::STRAIGHT) {
		result = Player::STR_STRAIGHT;
	}
	else if (r.hand_kind == Player::THREE_OF_A_KIND) {
		result = Player::STR_THREE_OF_A_KIND + r.mval();
	}
	else if (r.hand_kind == Player::TWO_PAIRS) {
		result = Player::STR_TWO_PAIRS;
	}
	else if (r.hand_kind == Player::ONE_PAIR) {
		result = Player::STR_ONE_PAIR + r.mval();
	}
	else if(r.hand_kind == Player::HIGH_CARD) {
		result = Player::STR_HIGH_CARD + r.mval(r.max_val);
	}

	return result;
}