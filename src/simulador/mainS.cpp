#include <iostream>
#include <vector>

#include "../../include/simulador.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 2){
		cout << "Quantidade de parametros invalida. Forneça o nome do arquivo a ser simulado.";
		return 1;
	}

	cout << "Certo";
	return 0;

}