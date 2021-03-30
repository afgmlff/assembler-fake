#ifndef AUX_ARQUIVO
#define AUX_ARQUIVO

#include "../include/auxArquivo.hpp"

using namespace std;


AuxArquivo::AuxArquivo(const string &nomeArquivo) {
    arquivo = new PFile(nomeArquivo.c_str());
    arquivoPronto = new MemFile;
}


void AuxArquivo::extraiCode() {
    string linha, ultimoRotulo;
    bool printLine = true;
    int contadorLinha = 0;
    int flag = 0, flagData = 0, flagText = 0;

    string texto = "TEXT";
    string dataa = "DATA";
    while (!arquivo->hasEnd()) {

            arquivo->getLine(&linha);
            contadorLinha++;
            if (linha.empty()) continue;
            Linha l = coletaTermosDaLinha(linha, false);

            if(l.op1 != texto and flagText == 0){ //escreve primeiro só a seção TEXT
                continue;
            }
            else if (l.op1 == texto and flagText == 0) flagText = 1;


            if (somenteRotulo(l)) {
                ultimoRotulo = l.rotulo;
                continue;
            } else {
                if (!ultimoRotulo.empty()) {
                    if (l.rotulo.empty()) {
                        l.rotulo = ultimoRotulo;
                    }
                }
                ultimoRotulo = "";
            }

            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op1)) {
                l.op1 = tabelaDeDefinicoes[l.op1];
            }
            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op2)) {
                l.op2 = tabelaDeDefinicoes[l.op2];
            }
            if (printLine) {
                arquivoPronto->writeLine(linhaToString(l));
            } else {
                printLine = true;
            }

    }

    arquivo->resetFile();  //reseta o arquivo para ler apenas DATA

    while (!arquivo->hasEnd()) {

            arquivo->getLine(&linha);
            contadorLinha++;
            if (linha.empty()) continue;
            Linha l = coletaTermosDaLinha(linha, false);

            if(l.op1 != dataa and flag == 0){ //escreve depois só a seção DATA
                continue;
            }
            else if (l.op1 == dataa and flag == 0) flag = 1;

            if(l.op1 == texto)
                break;

            if (somenteRotulo(l)) {
                ultimoRotulo = l.rotulo;
                continue;
            } else {
                if (!ultimoRotulo.empty()) {
                    if (l.rotulo.empty()) {
                        l.rotulo = ultimoRotulo;
                    }
                }
                ultimoRotulo = "";
            }

            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op1)) {
                l.op1 = tabelaDeDefinicoes[l.op1];
            }
            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op2)) {
                l.op2 = tabelaDeDefinicoes[l.op2];
            }
            if (printLine) {
                arquivoPronto->writeLine(linhaToString(l));
            } else {
                printLine = true;
            }

    }

    arquivo->arquivo.close();
    arquivoPronto->finishWrite();
}

#endif
