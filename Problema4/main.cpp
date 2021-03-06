#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

const static string DEFAULT_FILE_NAME = "poker.txt";

int main(int argc, char* argv[])
{
	/*for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		cout << "arg[" << i << "]: " << arg << endl;
	}*/

	if (argc > 2) {
		cout << "No se reconoce el comando" << endl;
	}
	else {
		string fname = argc <= 1 ? DEFAULT_FILE_NAME : argv[1];
		


	}

	system("pause");
	return 0;
}