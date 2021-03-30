#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/simulador.hpp"

using namespace std;

Simulador::Simulador(string arquivoS) {
	arquivoSim = arquivoS;
}

Simulador::~Simulador() {}

void imprime(){

	cout << "funcao integrada";
}


void Simulador::simular(){
	arquivoParaFila();
}

void Simulador::arquivoParaFila(){
	int opcode;
	ifstream file;
	file.open(arquivoSim);

	string input;
	int intFile;

	if(file.is_open()){
		cout << "Arquivo inicializado: " << arquivoSim << '\n';

	int i = 0;
	while (file >> opcode) {
	  	cout << opcode << ' ';
	}

		file.close();
	}

	else
		cout << "Erro ao abrir o arquivo no simulador.\n";
}