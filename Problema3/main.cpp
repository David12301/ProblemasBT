#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Michi.h"
using namespace std;

const static string DEFAULT_FILE_NAME = "michi.txt";

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

	// Permutación de 9 items
	vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Para llevar cuenta del nro de la partida N = 000001 .... N = 255168
	int nro = 1;

	// Clase para calcular cual fue el ganador o si hubo empate y el nro de jugadas
	Michi juego;

	string last_secuence = "";

	// Para datos extra al final de la ejecución
	int gana_en_5, gana_en_6, gana_en_7, gana_en_8, gana_en_9, empate;
	gana_en_5 = gana_en_6 = gana_en_7 = gana_en_8 = gana_en_9 = empate = 0;

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


		// Resetea el resultado anterior para calcular el de la sgte. partida
		juego.clear();

		// Para intercalar el valor de cada elección X ú O por cada posición en el array (vector)
		bool swap = true;

		string strtemp = "";

		// Luego será usado para contar empates
		string jresult = "";

		for (int i = 0; i < size; i++) {

			int choice = swap ? Michi::CHOICE_X : Michi::CHOICE_O;
			swap = !swap; // se intercala los valores

			// Indices del 0 al 8, simplemente a[i]-1
			juego.addChoice(choice, a[i] - 1);

			strtemp.append(std::to_string(a[i]) + " ");

			// Minímo 5 jugadas para que haya un posible ganador
			if (juego.jugadas() >= 5) 
			{
				int game_result = juego.checkWinner();
				if (game_result != Michi::RESULT_NO_RESULT) {

					// Agregar 0s al final hasta completar 9 jugadas
					for (int j = juego.jugadas(); j < size; j++) {
						strtemp.append("0 ");
					}

					if (game_result == Michi::RESULT_WIN_X) {
						jresult = "X";
					} else if (game_result == Michi::RESULT_WIN_O) {
						jresult = "O";
					} else if (game_result == Michi::RESULT_TIE) {
						jresult = "E";
					}

					strtemp.append(jresult);

					break;
				}
			}
		}
		strtemp.append("\n");

		bool no_es_repetida = strtemp != last_secuence;

		if (no_es_repetida) {

			if (jresult == "E") {
				empate++;
			} else {
				if (juego.jugadas() == 5)
					gana_en_5++;
				else if (juego.jugadas() == 6)
					gana_en_6++;
				else if (juego.jugadas() == 7)
					gana_en_7++;
				else if (juego.jugadas() == 8)
					gana_en_8++;
				else if (juego.jugadas() == 9)
					gana_en_9++;
			}

			// Importante agregar str_nro después porque sino strtemp y last_secuence siempre serán distintas
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
			cout << "Nro de juegos que: " << endl;
			cout << "Gana en 5: " << gana_en_5 << endl;
			cout << "Gana en 6: " << gana_en_6 << endl;
			cout << "Gana en 7: " << gana_en_7 << endl;
			cout << "Gana en 8: " << gana_en_8 << endl;
			cout << "Gana en 9: " << gana_en_9 << endl;
			cout << "Empates: " << empate << endl;
			cout << "Total de juegos: " << (gana_en_5 + gana_en_6 + gana_en_7 + gana_en_8 + gana_en_9 + empate) << endl;

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
	string fname = "";
	if (argc > 2) {
		cout << "No se reconoce el comando" << endl;
	} else {
		fname = argc <= 1 ? DEFAULT_FILE_NAME : argv[1];
		cout << "Procesando..." << endl;
		listAllTicTacToeGames(fname);
		cout << "Proceso terminado" << endl;
	}
	string cmd = "notepad.exe " + fname;
	system(cmd.c_str());
	system("pause");
	return 0;
}