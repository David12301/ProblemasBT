#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Michi.h"
using namespace std;

void listAllTicTacToeGames(string fname)
{
	/*
	* 
	De: https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
	Generation in lexicographic order
	1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
	2. Find the largest index l greater than k such that a[k] < a[l].
	3. Swap the value of a[k] with that of a[l].
	4. Reverse the sequence from a[k + 1] up to and including the final element a[n].
	*/

	string secuence = "";
	secuence.reserve(3265920); // nro digitos aprox: 9 * 9!, serán mucho menos al eliminar repeticiones
	secuence.clear();
	secuence = "  N    X 0 X 0 X 0 X 0 X Win\n";
	vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int nro = 1;
	Michi juego;
	string last_secuence = "";

	while (true) {
	
		//Evita llamar a la función size varias veces en los for
		int size = a.size();

		// Rellenar 0s a la izquierda
		string str_nro = std::to_string(nro);
		int len = str_nro.length();

		// 9! = 362880, 6 digitos a lo mucho
		for (int i = 0; i < (6 - len); i++) {
			str_nro = "0" + str_nro;
		}



		juego.clear();
		bool swap = true;
		string strtemp = "";
		for (int i = 0; i < size; i++) {
			//1 2 3 4 5 6 7 8 9 

			int choice = swap ? Michi::CHOICE_X : Michi::CHOICE_O;
			swap = !swap;
			juego.addChoice(choice, a[i] - 1);

			strtemp.append(std::to_string(a[i]) + " ");

			if (juego.jugadas() >= 5) 
			{
				int game_result = juego.checkWinner();
				if (game_result != Michi::RESULT_NO_RESULT) {
					for (int j = juego.jugadas(); j < size; j++) {
						strtemp.append("0 ");
					}

					if (game_result == Michi::RESULT_WIN_X) {
						strtemp.append("X");
					} else if (game_result == Michi::RESULT_WIN_O) {
						strtemp.append("O");
					} else if (game_result == Michi::RESULT_TIE) {
						strtemp.append("E");
					}

					break;
				}
			}
		}
		strtemp.append("\n");

		bool repetida = strtemp != last_secuence;

		if (repetida) {
			secuence.append(str_nro + " ");
			secuence.append(strtemp);
			nro++;
		}

		last_secuence = strtemp;

		//1.
		int k = 0;
		int aux = -1;
		for (int i = 0; i < size - 1; i++) {
			if (a[i] < a[i + 1]) {
				k = i;
				aux = a[i];
			}
		}

		// Cuando no existe valor para el indice tal que a[k] < a[k + 1] significa que la secuencia de permutaciones terminó
		if (aux == -1) {
			ofstream ofs_archivo;
			ofs_archivo.open(fname, ios::trunc);
			ofs_archivo << secuence;
			ofs_archivo.close();
			return;
		}

		//2. 
		int l = k + 1;
		for (int i = l; i < size; i++) {
			if (a[k] < a[i]) {
				l = i;
			}
		}

		// 3.
		int temp = a[k];
		a[k] = a[l];
		a[l] = temp;

		// 4.
		std::reverse(a.begin() + (k + 1), a.end());

		/*
		// También funciona pero siendo un poquito más lento que std::reverse por menos de un segundo
		vector<int> atemp;
		for (int i = k + 1; i < size; i++) {
			atemp.push_back(a[i]);
		}

		int tsize = atemp.size();
		for (int i = tsize - 1, j = k + 1; i >= 0; i--, j++) {
			a[j] = atemp[i];
		}
		*/

		
	}
}

int main(int argc, char *argv[])
{
	/*for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		cout << "arg[" << i << "]: " << arg << endl;
	}*/

	if (argc > 2) {
		cout << "No se reconoce el comando" << endl;
	} else {
		string fname = argc <= 1 ? "michi.txt" : argv[1];
		cout << "Procesando..." << endl;
		listAllTicTacToeGames(fname.c_str());
		cout << "Proceso terminado" << endl;
	}
	
	system("pause");
	return 0;
}