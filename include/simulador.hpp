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

	string arquivoSim;

	void arquivoParaFila();

public:
  Simulador(string arquivoS);

  ~Simulador();

  void simular();
};

void imprime();

#endif