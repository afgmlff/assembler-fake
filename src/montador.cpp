#ifndef MONTADOR
#define MONTADOR

#include "../include/montador.hpp"

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

void Montador::checkIfOperacaoValida(const Linha &linha) {
    bool isValida;
    if (linha.operacao == "COPY") {
        isValida = !linha.op1.empty() and !linha.op2.empty();
    } else if (linha.operacao == "STOP" or linha.operacao == "SPACE") {
        isValida = linha.op1.empty() and linha.op2.empty();
    } else {
        isValida = !linha.op1.empty() and linha.op2.empty();
        if (linha.operacao == "CONST") {

            if (!isInteger(linha.op1)) {
                throw MontadorException(MontadorException::OPERANDO_INVALIDO);
            }
            isValida = isValida and isInteger(linha.op1);
        } else if (linha.operacao == "SECTION") {
            if (linha.op1 != "TEXT" and linha.op1 != "DATA") {
                throw MontadorException(MontadorException::OPERANDO_INVALIDO);
            }
            isValida = isValida and (linha.op1 == "TEXT" or linha.op1 == "DATA");
        }
    }
    if (!isValida) {
        throw MontadorException(MontadorException::QUANTIDADE_OPERANDO);
    }
}

void Montador::primeiraPassagem() {
    string linha;
    int contadorPosicao = 0, contadorLinha = 0;
    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);
            contadorLinha += 1;
            if (linha.empty()) continue;
            Linha l = coletaTermosDaLinha(linha);

            if (!l.rotulo.empty()) { //checa se há rotulo
                if (mapSimbolos.end() != mapSimbolos.find(l.rotulo)) {//busca na tabela se há repetido. caso afirmativo -> erro rotulo rep

                    throw MontadorException(MontadorException::ROTULO_REPETIDO);
                } else {//caso negativo -> insere rotulo

                    mapSimbolos[l.rotulo] = contadorPosicao;
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//procura se é instrucao existente
                contadorPosicao += sizeInstDiretiva(l.operacao);
            } else {

                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) { //procura se é diretiva existente
                    contadorPosicao += sizeInstDiretiva(l.operacao);
                } else {
                    throw MontadorException(MontadorException::OPERACAO_INVALIDA); //caso nao seja -> erro operacao
                }
            }
        } catch (MontadorException &e) {
            errors.pushErro(e.error, linha, contadorLinha);
            continue;
        }
    }

    arquivo->resetFile();
}

string Montador::segundaPassagem() {
    string linha;
    string code;
    int contadorPosicao = 0, contadorLinha = 0;
    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);
            contadorLinha += 1;
            if (linha.empty()) continue;
            Linha l = coletaTermosDaLinha(linha, false);

            if (l.operacao != "CONST" and l.operacao != "SECTION") { //removendo possibilidade de ser diretiva
                if ((mapSimbolos.end() == mapSimbolos.find(l.op1) and !l.op1.empty()) or (
                        mapSimbolos.end() == mapSimbolos.find(l.op2) and !l.op2.empty())) {
                    throw MontadorException(MontadorException::ROTULO_AUSENTE);
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//localiza instrucao
                contadorPosicao += sizeInstDiretiva(l.operacao);
                checkIfOperacaoValida(l);

                //codigo de saida
                code += to_string(mapInstrucao[l.operacao]) + ' ';
                if (!l.op1.empty()) {
                    code += to_string(mapSimbolos[l.op1]) + ' ';
                }
                if (!l.op2.empty()) {
                    code += to_string(mapSimbolos[l.op2]) + ' ';
                }
            } else {
                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) {//localiza diretiva
                    checkIfOperacaoValida(l);

                    //codigo de saida p/ diretiva
                    if (l.operacao == "CONST") {
                        code += l.op1 + ' ';
                    } else if (l.operacao == "SPACE") {
                        code += "0 ";
                    }
                } else {
                    throw MontadorException(MontadorException::OPERACAO_INVALIDA);
                }
            }
        } catch (MontadorException &e) {
            errors.pushErro(e.error, linha, contadorLinha);
            continue;
        }
    }

    if (errors.contemErrors()) {
        throw PassagemException("Montagem", errors.mensagemTodosErros());
    }

    return code;
}

#endif