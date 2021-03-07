#pragma once

struct GameResult {
	int hand_kind;
	char val_of_hk;
	char type_of_hk;
	char max_val;
	int ind_winner;

	GameResult() {
		hand_kind = val_of_hk = type_of_hk = max_val = 0;
		ind_winner = -1;
	}
	
	string mtype() {
		string result = "";
		if (type_of_hk == 'C') {
			result = "treboles";
		}
		else if (type_of_hk == 'H') {
			result = "corazones";
		}
		else if (type_of_hk == 'D') {
			result = "diamantes";
		}
		else if (type_of_hk == 'S') {
			result = "espadas";
		}
		return result;
	}

	string mval(char val=false) {
		string result = "";
		char c = !val ? val_of_hk : val;

		if (c == '2') {
			result = "dos";
		}
		else if (c == '3') {
			result = "tres";
		}
		else if (c == '4') {
			result = "cuatro";
		}
		else if (c == '5') {
			result = "cinco";
		}
		else if (c == '6') {
			result = "seis";
		}
		else if (c == '7') {
			result = "siete";
		}
		else if (c == '8') {
			result = "ocho";
		}
		else if (c == '9') {
			result = "nueve";
		}
		else if (c == 'T') {
			result = "diez";
		}
		else if (c == 'J') {
			result = "once";
		}
		else if (c == 'Q') {
			result = "doce";
		}
		else if (c == 'K') {
			result = "trece";
		}
		else if (c == 'A') {
			result = "aces";
		}
		return result;
	}
};