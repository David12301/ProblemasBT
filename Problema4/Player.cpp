#include "Player.h"
#include <vector>


const string Player::STR_HIGH_CARD = "High card ";
const string Player::STR_ONE_PAIR = "Par de ";
const string Player::STR_TWO_PAIRS = "Dos pares";
const string Player::STR_THREE_OF_A_KIND = "Tres ";
const string Player::STR_STRAIGHT = "Straight";
const string Player::STR_FLUSH = "Flush de ";
const string Player::STR_FULL_HOUSE = "Full House de ";
const string Player::STR_FOUR_OF_A_KIND = "Cuatro ";
const string Player::STR_STRAIGHT_FLUSH = "Straight Flush de ";
const string Player::STR_ROYAL_FLUSH = "Royal flush de ";

Player::Player() 
{
}

Player::~Player() 
{
}

GameResult Player::resolveHand()
{
	GameResult gResult;
	int result = -1;
	char v1 = false;
	char v2 = false;
	/*
	HIGH CARD: El valor de la carta de mayor valor
	ONE PAIR: Dos cartas del mismo valor (un par)
	TWO PAIRS: Dos pares diferentes.
	THREE OF A KIND: Tres cartas del mismo valor
	STRAIGHT: Todas las cartas son valores consecutivos
	FLUSH: Todas las cartas son del mismo tipo
	FULL HOUSE: Tres cartas del mismo valor y un par
	FOUR OF A KIND: Cuatro cartas del mismo valor
	STRAIGHT FLUSH: Todas las cartas son valores consecutivos del mismo tipo
	ROYAL FLUSH: 10, Jack, Queen, King, Ace, del mismo tipo
	*/

	// 1. ROYAL_FLUSH
	if ((gResult.type_of_hk = allSameType()) && countValue('T') == 1  && countValue('J') == 1 && countValue('Q') == 1 &&
		countValue('K') == 1 && countValue('A') == 1) {
		result = Player::ROYAL_FLUSH;
	}

	// 2. STRAIGHT FLUSH
	else if ((gResult.type_of_hk = allSameType()) && hasStraight()) {
		gResult.type_of_hk = hand[0].type;
		result = Player::STRAIGHT_FLUSH;
	}

	// 3. FOUR OF A KIND
	else if (gResult.val_of_hk = hasNRepeat(4)) {
		result = Player::FOUR_OF_A_KIND;
	}

	// 4. FULL HOUSE
	// v1 != v2 es porque debe repetirse de distinto valor. La asignación a v1 y v2 se resuelve 
	// antes de comparar v1 != v2 por el orden de las comparaciones ( a && b && c ) los
	// statement a y b se resuelven antes que c. En general los statement en una comparación
	// siempre se resuelven antes de comparar el valor en cuestión
	else if ( (v1 = hasNRepeat(3)) != false && (v2 = hasNRepeat(2)) != false && v1 != v2) {
		result = Player::FULL_HOUSE;
	}

	// 5. FLUSH
	else if ((gResult.type_of_hk = allSameType())) {
		result = Player::FLUSH;
	}

	// 6. STRAIGHT
	else if (hasStraight()) {
		result = Player::STRAIGHT;
	}

	// 7. THREE_OF_A_KIND
	else if (gResult.val_of_hk = hasNRepeat(3)) {
		result = Player::THREE_OF_A_KIND;
	}

	// 8. TWO PAIRS
	else if ( (v1=hasNRepeat(2)) != false && (v2 = hasNRepeat(2, v1)) != false && v1 != v2) {
		result = Player::TWO_PAIRS;
	}

	// 9. ONE PAIR
	else if ((v1=hasNRepeat(2)) != false && (v2=hasNRepeat(2, v1)) == false) {
		gResult.val_of_hk = v1;
		result = Player::ONE_PAIR;
	}
	
	// 10. HIGH CARD
	if(result == -1) {
		result = Player::HIGH_CARD;
	}

//lcontinue:
	gResult.hand_kind = result;

	int max = valorMaximo();
	
	gResult.max_val = iTocval(max);

	return gResult;
}

int Player::countValue(char val) 
{
	int result = 0;

	for (int i = 0; i < Player::MAX_HAND_SIZE; i++) {
		if (hand[i].val == val)
			result++;
	}

	return result;
}
int Player::countType(char type)
{
	int result = 0;

	for (int i = 0; i < Player::MAX_HAND_SIZE; i++) {
		if (hand[i].type == type)
			result++;
	}

	return result;
}

char Player::allSameType()
{
	char t = hand[0].type;
	for (int i = 0; i < Player::MAX_HAND_SIZE; i++) {
		if (hand[i].type != t) {
			return false;
		}
	}
	return t;
}

void Player::clearHand() 
{
	for (int i = 0; i < Player::MAX_HAND_SIZE; i++) {
		hand[i].val = 0;
		hand[i].type = 0;
	}
}

char Player::hasNRepeat(int n, char except) 
{
	int count = 0;
	for (int i = 1; i < 14; i++) {
		char v = iTocval(i);
		
		// Cuenta el nro de repeticiones por valor
		for (int j = 0; j < Player::MAX_HAND_SIZE; j++) {

			bool excepto = except == false ? true : hand[j].val != except;
			if (v == hand[j].val && excepto) {
				count++;
			}
		}

		if (count == n)
			return v;

		// Resetear el contador para contar de un valor diferente
		count = 0;
	}

	return false;
}

char Player::iTocval(int i) 
{
	return i == 1 ? 'A' : i == 10 ? 'T' : i == 11 ? 'J' : i == 12 ? 'Q' : i == 13 ? 'K' : i == 14 ? 'A' : std::to_string(i)[0];
}

bool Player::hasStraight() 
{
	// A 2 3 4 5
	// 2 3 4 5 6
	// 3 4 5 6 7
	// 4 5 6 7 8
	// 5 6 7 8 9
	// 6 7 8 9 T
	// 7 8 9 T J
	// 8 9 T J Q
	// 9 T J Q K
	// T J Q K A

	for (int i = 1, j = 2, k = 3, l = 4, m = 5; m < 15; i++, j++, k++, l++, m++) {
		
		char v[5] = { iTocval(i), iTocval(j), iTocval(k), iTocval(l), iTocval(m) };
		int  c[5] = { 0, 0, 0, 0, 0 };

		// Comparar cada valor generado con cada valor en la mano del jugador e incrementar un contador(c[y])
		// si es igual. El contador corresponderá al valor generado en cuestión(v[y]) porque tienen el mismo
		// indice(y)
		for (int x = 0; x < Player::MAX_HAND_SIZE; x++) {
			for (int y = 0; y < 5; y++) {
				if (hand[x].val == v[y])
					c[y]++;
			}
		}

		// Para que tenga escalera debe haber contado solamente 1 por cada valor
		if (c[0] == 1 && c[1] == 1 && c[2] == 1 && c[3] == 1 && c[4] == 1) {
			return true;
		}

	}

	return false;
	/*
	if (countValue('A') == 1 && countValue('2') == 1 && countValue('3') == 1 && countValue('4') == 1 && countValue('5') == 1) {
		return true;
	}
	else if (countValue('2') == 1 && countValue('3') == 1 && countValue('4') == 1 && countValue('5') == 1 && countValue('6') == 1) {
		return true;
	}
	else if (countValue('3') == 1 && countValue('4') == 1 && countValue('5') == 1 && countValue('6') == 1 && countValue('7') == 1) {
		return true;
	}
	else if (countValue('4') == 1 && countValue('5') == 1 && countValue('6') == 1 && countValue('7') == 1 && countValue('8') == 1) {
		return true;
	}
	else if (countValue('5') == 1 && countValue('6') == 1 && countValue('7') == 1 && countValue('8') == 1 && countValue('9') == 1) {
		return true;
	}
	else if (countValue('6') == 1 && countValue('7') == 1 && countValue('8') == 1 && countValue('9') == 1 && countValue('T') == 1) {
		return true;
	}
	else if (countValue('7') == 1 && countValue('8') == 1 && countValue('9') == 1 && countValue('T') == 1 && countValue('J') == 1) {
		return true;
	}
	else if (countValue('8') == 1 && countValue('9') == 1 && countValue('T') == 1 && countValue('J') == 1 && countValue('Q') == 1) {
		return true;
	}
	else if (countValue('9') == 1 && countValue('T') == 1 && countValue('J') == 1 && countValue('Q') == 1 && countValue('K') == 1) {
		return true;
	}
	else if (countValue('T') == 1 && countValue('J') == 1 && countValue('Q') == 1 && countValue('K') == 1 && countValue('A') == 1) {
		return true;
	}*/

	return false;
}

string Player::getHandStr() 
{
	string result = "";
	for (int x = 0; x < Player::MAX_HAND_SIZE; x++) {
		Card c = hand[x];
		result += c.val;
		result += c.type;
		result += " ";
	}
	return result;
}


int Player::valorMaximo()
{
	int max = -1;
	for (int i = 0; i < Player::MAX_HAND_SIZE; i++) {
		int v = aToival(hand[i].val);
		if (v > max)
			max = v;
	}
	return max;
}

int Player::aToival(char c) 
{
	return c == 'A' ? 14 : c == 'K' ? 13 : c == 'Q' ? 12 : c == 'J' ? 11 : c == 'T' ? 10 : atoi(&c);
}

