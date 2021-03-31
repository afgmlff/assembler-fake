#ifndef AUX_ARQUIVO
#define AUX_ARQUIVO

#include "../include/auxArquivo.hpp"
#include "../include/global.hpp"

using namespace std;


AuxArquivo::AuxArquivo(const string &nomeArquivo) {
    arquivo = new PFile(nomeArquivo.c_str());
    arquivoPronto = new MemFile;
}


void AuxArquivo::extraiCode() {
    data_section_start = 0;
    text_section_start = 0;
    bool writeOut = true;
    int contadorLinha = 0;
    int flag = 0, flagData = 0, flagText = 0;
    string linha, label, texto = "TEXT", dataa = "DATA";

    while (!arquivo->hasEnd()) {

            arquivo->getLine(&linha);
            contadorLinha++;

            if (linha.empty() or (lstrip(linha))[0] == ';'){
              arquivoPronto->writeLine("");
//              cout << '\n';
              continue;
            }
            Linha l = splitLinha(linha, false);

            if(l.op1 == "DATA"){
                data_section_start = contadorLinha;
//                cout << "\nData section starts at: " << data_section_start;
            }

            if(l.op1 == "TEXT"){
                text_section_start = contadorLinha;
//                cout << "\nText section starts at: " << text_section_start;
            }

            if(l.op1 != texto and flagText == 0){ //escreve primeiro só a seção TEXT
                continue;
            }
            else if (l.op1 == texto and flagText == 0) flagText = 1;

//            cout << linha << '\n';

            if (isLabel(l)) {
                label = l.rotulo;
                continue;
            } else {
                if (!label.empty()) {
                    if (l.rotulo.empty()) {
                        l.rotulo = label;
                    }
                }
                label = "";
            }

            if (mapComponente.end() != mapComponente.find(l.op1)) {
                l.op1 = mapComponente[l.op1];
            }
            if (mapComponente.end() != mapComponente.find(l.op2)) {
                l.op2 = mapComponente[l.op2];
            }
            if (writeOut) {
                arquivoPronto->writeLine(concatLine(l));
            } else {
                writeOut = true;
            }

    }

    arquivo->resetFile();  //reseta o arquivo para ler apenas DATA

    while (!arquivo->hasEnd()) {

            arquivo->getLine(&linha);
            contadorLinha++;
            if (linha.empty() or (lstrip(linha))[0] == ';'){
              arquivoPronto->writeLine("");
  //            cout << '\n';
              continue;
            }
            Linha l = splitLinha(linha, false);

            if(l.op1 != dataa and flag == 0){ //escreve depois só a seção DATA
                continue;
            }
            else if (l.op1 == dataa and flag == 0) flag = 1;

            if(l.op1 == texto)
                break;

//            cout << linha << '\n';

            if (isLabel(l)) {
                label = l.rotulo;
                continue;
            } else {
                if (!label.empty()) {
                    if (l.rotulo.empty()) {
                        l.rotulo = label;
                    }
                }
                label = "";
            }

            if (mapComponente.end() != mapComponente.find(l.op1)) {
                l.op1 = mapComponente[l.op1];
            }
            if (mapComponente.end() != mapComponente.find(l.op2)) {
                l.op2 = mapComponente[l.op2];
            }
            if (writeOut) {
                arquivoPronto->writeLine(concatLine(l));
            } else {
                writeOut = true;
            }

    }

    arquivo->arquivo.close();
    arquivoPronto->finishWrite();
}

#endif
