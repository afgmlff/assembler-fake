#ifndef SIMULADOR_H_INCLUDED
#define SIMULADOR_H_INCLUDED

#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Simulador {
private:
	int filaInstrucoes[300];
	int pc;
	int acumulador;

	map<int, string> mapInstrucaoSim = {
    		{1, "ADD"},
    		{2, "SUB"},
    		{3, "MUL"},
    		{4, "DIV"},
    		{5, "JMP"},
    		{6, "JMPN"},
    		{7, "JMPP"},
    		{8, "JMPZ"},
    		{9, "COPY"},
    		{10, "LOAD"},
    		{11, "STORE"},
    		{12, "INPUT"},
    		{13, "OUTPUT"},
    		{14, "STOP"},
  };

	string arquivoSim;

	void arquivoParaFila();

	vector<int> saidaspArquivo;

public:
	Simulador(string arquivoS);

  	~Simulador();

  	void simular();

  	void percorrerMapa();
};

string trocarExtensao(string nome, const string &terminacao);

#endif