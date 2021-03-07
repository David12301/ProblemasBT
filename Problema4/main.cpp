#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Poker.h"

using namespace std;

const static string DEFAULT_INPUT_FILE_NAME = "poker.txt";
const static string DEFAULT_OUTPUT_FILE_NAME = "output.txt";
const 

int main(int argc, char* argv[])
{
	/*for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		cout << "arg[" << i << "]: " << arg << endl;
	}*/

	if (argc > 3) {
		cout << "No se reconoce el comando" << endl;
	}
	else {
		string ifname = argc <= 1 ? DEFAULT_INPUT_FILE_NAME : argv[1];
		string ofname = argc <= 1 ? DEFAULT_OUTPUT_FILE_NAME : argv[2];
		Poker* game = new Poker;
		game->loadGamesFromFile(ifname, ofname);
		delete game;
	}

	system("pause");
	return 0;
}