#ifndef MONTADOR_ERROR_H
#define MONTADOR_ERROR_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MontadorException : public std::exception {
public:
    enum tipoErro {
        ROTULO_AUSENTE,
        ROTULO_REPETIDO,
        OPERACAO_INVALIDA,
        QUANTIDADE_OPERANDO,
        OPERANDO_INVALIDO,
        TOKEN_INVALIDO,
    } error;

    MontadorException(tipoErro error) : std::exception() {
        this->error = error;
    }

    const char *what() const noexcept override;
};

struct MontadorError {
    MontadorException::tipoErro code;
    string linha;
    int numLinha;
};

class MontadorErrors {
    vector<MontadorError> errors;
public:
    void pushErro(MontadorException::tipoErro error, string linha, int numLinha);

    static string mensagemError(MontadorException::tipoErro);

    static string errorTipo(MontadorException::tipoErro);

    string mensagemTodosErros();


    bool contemErrors();

};

class PassagemException : public std::exception {
    string passagem;
    string mensagem;
public:
    PassagemException(string passagem, string mensagem) : std::exception() {
        this->passagem = passagem;
        this->mensagem = mensagem;
    }

    string mensagemCompleta();

    const char *what() const noexcept override;
};


#endif