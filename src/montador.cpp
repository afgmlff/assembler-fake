#ifndef MONTADOR
#define MONTADOR

#include "../include/montador.hpp"
#include "../include/global.hpp"

using namespace std;

Montador::Montador(FileHandler *fileHandler) {
    this->arquivo = fileHandler;
}

int Montador::sizeInstDiretiva(const string &instrucao) {
    if (instrucao == "COPY") {
        return 3;
    } else if (instrucao == "STOP" or instrucao == "SPACE" or instrucao == "CONST") {
        return 1;
    } else if (instrucao == "SECTION") {
        return 0;
    } else {
        return 2;
    }
};

void Montador::validaOPlinha(const Linha &linha) {
    bool isValida;
    if (linha.operacao == "COPY") {
        isValida = !linha.op1.empty() and !linha.op2.empty();
    }
    else if (linha.operacao == "STOP" or linha.operacao == "SPACE") {
        isValida = linha.op1.empty() and linha.op2.empty();
    }
    else {
        isValida = !linha.op1.empty() and linha.op2.empty();
        if (linha.operacao == "CONST") {

            if (!isInteger(linha.op1)) {
                throw EnumExcecao(EnumExcecao::OPERANDO_INVALIDO);
            }
            isValida = isValida and isInteger(linha.op1);
        }
        else if (linha.operacao == "SECTION") {
            if (linha.op1 != "DATA" and linha.op1 != "TEXT") {
                throw EnumExcecao(EnumExcecao::OPERANDO_INVALIDO);
            }
            isValida = isValida and (linha.op1 == "DATA" or linha.op1 == "TEXT");
        }
    }
    if (!isValida) {
        throw EnumExcecao(EnumExcecao::QTD_OP_ERRADA);
    }
}

void Montador::primeiraPassagem() {
    string linha;
    int contadorPosicao = 0, contadorLinha = 0, auxCount = 0, flagTxtS = 0, flagDataS = 0, contPostText, contPostData;
    contPostText = text_section_start;
    contPostData = data_section_start;

//    cout << "(montador)text section start: " << text_section_start << '\n' << "(montador)data section start: "<< data_section_start << '\n';

    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);
//            cout << linha << '\n';
            if(flagDataS == 0 && flagTxtS == 1){
              contPostText += 1;
            }
            if(flagDataS == 1){
              contPostData += 1;
            }

            if (linha.empty()) continue;
            Linha l = splitLinha(linha);

            if(l.op1 == "DATA")
              flagDataS = 1;

            if(l.op1 == "TEXT")
              flagTxtS = 1;

            if (!l.rotulo.empty()) { //checa se há rotulo
                if (mapSimbolos.end() != mapSimbolos.find(l.rotulo)) {//busca na tabela se há repetido. caso afirmativo -> erro rotulo rep

                    throw EnumExcecao(EnumExcecao::DECLARACAO_ROT_REP);
                }
                else {//caso negativo -> insere rotulo

                    mapSimbolos[l.rotulo] = contadorPosicao;
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//procura se é instrucao existente
                contadorPosicao += sizeInstDiretiva(l.operacao);
            }
            else {

                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) { //procura se é diretiva existente
                    contadorPosicao += sizeInstDiretiva(l.operacao);
                }
                else {
                    throw EnumExcecao(EnumExcecao::DIRETIVA_INST_INVALID); //caso nao seja -> erro operacao
                }
            }
        } catch (EnumExcecao &e) {
            if(flagDataS == 0){
              errors.pushErro(e.error, linha, contPostText);
              continue;
            }
            else{
              errors.pushErro(e.error, linha, contPostData);
              continue;
            }
        }
    }

    arquivo->resetFile();
}

string Montador::segundaPassagem() {
    string linha;
    string code;
    int contadorPosicao = 0, contadorLinha = 0, auxCount = 0, flagTxtS, flagDataS = 0, contPostText, contPostData;
    contPostText = text_section_start;
    contPostData = data_section_start;

    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);

            if(flagDataS == 0 && flagTxtS == 1){
              contPostText += 1;
            }

            if(flagDataS == 1){
              contPostData += 1;
            }

            if (linha.empty()) continue;
            Linha l = splitLinha(linha, false);

//            cout << l.operacao << '\n';

            if(l.op1 == "DATA")
              flagDataS = 1;

            if(l.op1 == "TEXT")
              flagTxtS = 1;

            if (l.operacao != "CONST" and l.operacao != "SECTION") { //removendo possibilidade de ser diretiva
                if ((mapSimbolos.end() == mapSimbolos.find(l.op1) and !l.op1.empty()) or (
                        mapSimbolos.end() == mapSimbolos.find(l.op2) and !l.op2.empty())) {
                    throw EnumExcecao(EnumExcecao::DECLARACAO_ROT_AUSENTE);
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//localiza instrucao
                contadorPosicao += sizeInstDiretiva(l.operacao);
                validaOPlinha(l);

                //codigo de saida
                code += to_string(mapInstrucao[l.operacao]) + ' ';
                if (!l.op1.empty()) {
                    code += to_string(mapSimbolos[l.op1]) + ' ';
                }
                if (!l.op2.empty()) {
                    code += to_string(mapSimbolos[l.op2]) + ' ';
                }
            }
            else {
                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) {//localiza diretiva
                    validaOPlinha(l);

                    //codigo de saida p/ diretiva
                    if (l.operacao == "CONST") {
                        code += l.op1 + ' ';
                    }
                    else if (l.operacao == "SPACE") {
                        code += "0 ";
                    }
                } else {
                    throw EnumExcecao(EnumExcecao::DIRETIVA_INST_INVALID);
                }
            }
        } catch (EnumExcecao &e) {
            if(flagDataS == 0){
              errors.pushErro(e.error, linha, contPostText);
              continue;
            }
            else{
              errors.pushErro(e.error, linha, contPostData);
              continue;
            }
        }
    }

    if (errors.emptyStack()) {
        throw PassagemException("Montagem", errors.collectErros());
    }

    return code;
}

#endif
