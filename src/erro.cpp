#ifndef MONTADOR_ERROR
#define MONTADOR_ERROR


#include "../include/error.hpp"

using namespace std;

const char *EnumExcecao::what() const noexcept {
    return to_string(this->error).c_str();
}

void MontadorErrors::pushErro(EnumExcecao::tipoErro error, string linha, int numLinha) {
    errors.push_back((defErro) {error, linha, numLinha});
}

string MontadorErrors::mensagemError(EnumExcecao::tipoErro error) {
    switch (error) {
        case EnumExcecao::ROTULO_AUSENTE:
            return "Declaração/rótulo ausente";
        case EnumExcecao::ROTULO_REPETIDO:
            return "Declaração/rótulo repetido";
        case EnumExcecao::OPERACAO_INVALIDA:
            return "Diretiva/instrução inválida";
        case EnumExcecao::QUANTIDADE_OPERANDO:
            return "Instrução com a quantidade de operando errada";
        case EnumExcecao::OPERANDO_INVALIDO:
            return "Instrução com o tipo de operando inválido";
        case EnumExcecao::TOKEN_INVALIDO:
            return "Tokens inválidos";
    }
}

string MontadorErrors::classifica(EnumExcecao::tipoErro error) {
    if ((error == EnumExcecao::QUANTIDADE_OPERANDO) or ((error == EnumExcecao::OPERANDO_INVALIDO)) or ((error == EnumExcecao::OPERACAO_INVALIDA))) {
        return "Erro Sintático";
    } else if (error == EnumExcecao::TOKEN_INVALIDO) {
        return "Erro Léxico";
    } else {
        return "Erro Semântico";
    }
}

bool MontadorErrors::emptyStack() {
    return !errors.empty();
}

string MontadorErrors::collectErros() {
    string errorMessage;
    for (const auto &error: errors) {
        errorMessage = errorMessage + "\nLinha (" + to_string(error.numLinha) + ")" + ": " + mensagemError(error.code) + " (" + classifica(error.code) + ")"
                       "\nNo trecho: " + error.linha + "\n" +
                       "---" + "\n";
    }
    return errorMessage;
}

const char *PassagemException::what() const noexcept {
    return (this->mensagem).c_str();
}

string PassagemException::stackErros() {
    return "\nOcorreram erros durante a montagem:\n" + this->mensagem;
}

#endif
