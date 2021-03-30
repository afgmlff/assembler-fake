#include <iostream>
#include <vector>

#include "../../include/simulador.hpp"



int main(int argc, char **argv) {
	if (argc < 2){
		cout << "Quantidade de parametros invalida. Forneça o nome do arquivo a ser simulado.";
		return 1;
	}

	Simulador simulador(argv[1]);
	simulador.simular();

	return 0;

}