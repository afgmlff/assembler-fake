#ifndef MONTADOR_ERROR_H
#define MONTADOR_ERROR_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class EnumExcecao : public std::exception {
public:
    enum tipoErro {
        DECLARACAO_ROT_AUSENTE,
        DECLARACAO_ROT_REP,
        DIRETIVA_INST_INVALID,
        QTD_OP_ERRADA,
        OPERANDO_INVALIDO,
        TOKEN_INVALIDO,
    } error;

    EnumExcecao(tipoErro error) : std::exception() {
        this->error = error;
    }

};

struct defErro {
    EnumExcecao::tipoErro code;
    string linha;
    int numLinha;
};

class AssembleErr {
    vector<defErro> errors;
public:
    void pushErro(EnumExcecao::tipoErro error, string linha, int numLinha);

    static string mensagemError(EnumExcecao::tipoErro);

    static string classifica(EnumExcecao::tipoErro);

    string collectErros();


    bool emptyStack();

};

class PassagemException : public std::exception {
    string passagem;
    string mensagem;
public:
    PassagemException(string passagem, string mensagem) : std::exception() {
        this->passagem = passagem;
        this->mensagem = mensagem;
    }

    string stackErros();

};


#endif
