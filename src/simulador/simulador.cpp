#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/simulador.hpp"

using namespace std;

Simulador::Simulador(string arquivoS) {
	arquivoSim = arquivoS;
}

Simulador::~Simulador() {}



void Simulador::simular(){
	arquivoParaFila();
	percorrerMapa();
}

void Simulador::arquivoParaFila(){
	int opcode;
	ifstream file;
	file.open(arquivoSim);

//	string input;
//	int intFile;

	if(file.is_open()){
		cout << "Arquivo inicializado: " << arquivoSim << '\n';

	int index = 0;
	while (file >> opcode) {
	  	filaInstrucoes[index] = opcode;
//	  	cout << filaInstrucoes[index] << ' ';
	  	index++;
	}

		file.close();
	}

	else
		cout << "Erro ao abrir o arquivo no simulador.\n";
}

string trocarExtensao(string nome, const string &terminacao) {
    if (std::string::npos == nome.find('.')) {
        return nome + '.' + terminacao;
    } else {
        return nome.replace(nome.find_last_of('.'), nome.length(), terminacao);
    }
}


void Simulador::percorrerMapa(){

	int opcode, enderecoOp1, operando1, enderecoOp2, operando2, aux, userInput;
	pc = 0;
	acumulador = 0;
	string instrucao;
	cout << '\n';
	while (filaInstrucoes[pc] != 14){//stop
		opcode = filaInstrucoes[pc];
		enderecoOp1 = filaInstrucoes[pc+1];
		operando1 = filaInstrucoes[enderecoOp1];

		instrucao = mapInstrucaoSim[opcode];
		cout << "\n\n- Depois da instrução " << instrucao;

		switch(opcode){

			case 1: //add
				acumulador += operando1;
				pc += 2;
			break;

			case 2: //sub
				acumulador -= operando1;
				pc += 2;
			break;

			case 3: //mul
				acumulador *= operando1;
				pc += 2;
			break;

			case 4: //div
				acumulador /= operando1;
				pc += 2;
			break;

			case 5: //jmp
				pc = enderecoOp1;
			break;

			case 6: //jmpn
				if(acumulador < 0){
					pc = enderecoOp1;
				}
				else{
					pc += 2;
				}
			break;

			case 7: //jmpp
				if(acumulador > 0){
					pc = enderecoOp1;
				}
				else{
					pc += 2;
				}
			break;

			case 8: //jmpz
				if(acumulador == 0){
					pc = enderecoOp1;
				}
				else{
					pc += 2;
				}
			break;

			case 9: //copy
				enderecoOp2 = filaInstrucoes[pc+2];

				aux = filaInstrucoes[enderecoOp1];

				filaInstrucoes[enderecoOp2] = aux;
				pc += 3;
			break;

			case 10: //load
				acumulador = operando1;
				pc += 2;
			break;

			case 11: //store
				filaInstrucoes[enderecoOp1] = acumulador;
				pc += 2;
			break;

			case 12: //input
				cout << "\nInsira o valor da instrução Input: ";
				cin >> userInput;
				filaInstrucoes[enderecoOp1] = userInput;
				pc += 2;
			break;

			case 13: //output
				aux = operando1;
				cout << "\nOUTPUT: " << aux ;
				saidaspArquivo.push_back(aux);
				pc += 2;
			break;

			default:
				cout << "\nErro: Instrução não identificada.\nOpcode: " << opcode << "\nCaso o arquivo de entrada seja externo (não tenha sido gerado pelo montador), favor verificar instruções utilizadas.\n";
				return;
		}


		
		cout << "\nPC <- " << pc ;
    	cout << "\nACC <- " << acumulador;

	}

	cout << '\n';
	string arqOUT, stgsaida = "";

	arqOUT = trocarExtensao(arquivoSim, ".out");
	cout << "Foi gerado o arquivo: " << arqOUT << '\n';

	ofstream fileout;
	fileout.open(arqOUT);

	for (auto conta : saidaspArquivo) {
    	stgsaida.append(to_string(conta) + "\n");
  	}
  	stgsaida = stgsaida + '\n';
	fileout << stgsaida;
  	fileout.close();

}