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
    while (!arquivo->hasEnd()) {
        try {

            arquivo->getLine(&linha);
            contadorLinha++;
            if (linha.empty()) continue;
            Linha l = coletaTermosDaLinha(linha, false);

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
        } catch (MontadorException &e) {
            errors.pushErro(e.error, linha, contadorLinha);
            continue;
        }
    }
    arquivo->arquivo.close();
    arquivoPronto->finishWrite();
}

#endif
