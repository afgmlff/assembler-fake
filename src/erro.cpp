#ifndef MONTADOR_ERROR
#define MONTADOR_ERROR


#include "../include/error.hpp"

using namespace std;

void AssembleErr::pushErro(EnumExcecao::tipoErro error, string linha, int numLinha) {
    errors.push_back((defErro) {error, linha, numLinha});
}

string AssembleErr::mensagemError(EnumExcecao::tipoErro error) {
    switch (error) {
        case EnumExcecao::DECLARACAO_ROT_AUSENTE:
            return "Declaração/rótulo ausente";
        case EnumExcecao::DECLARACAO_ROT_REP:
            return "Declaração/rótulo repetido";
        case EnumExcecao::DIRETIVA_INST_INVALID:
            return "Diretiva/instrução inválida";
        case EnumExcecao::QTD_OP_ERRADA:
            return "Instrução com a quantidade de operando errada";
        case EnumExcecao::OPERANDO_INVALIDO:
            return "Instrução com o tipo de operando inválido";
        case EnumExcecao::TOKEN_INVALIDO:
            return "Tokens inválidos";
    }
}

string AssembleErr::classifica(EnumExcecao::tipoErro error) {
    if ((error == EnumExcecao::QTD_OP_ERRADA) or ((error == EnumExcecao::OPERANDO_INVALIDO)) or ((error == EnumExcecao::DIRETIVA_INST_INVALID))) {
        return "Erro Sintático";
    } else if (error == EnumExcecao::TOKEN_INVALIDO) {
        return "Erro Léxico";
    } else {
        return "Erro Semântico";
    }
}

bool AssembleErr::emptyStack() {
    return !errors.empty();
}

string AssembleErr::collectErros() {
    string errorMessage;
    for (const auto &error: errors) {
        errorMessage = errorMessage + "\nLinha (" + to_string(error.numLinha) + ")" + ": " + mensagemError(error.code) + " (" + classifica(error.code) + ")"
                       "\nNo trecho: " + error.linha + "\n" +
                       "---" + "\n";
    }
    return errorMessage;
}


string PassagemException::stackErros() {
    return "\nOcorreram erros durante a montagem:\n" + this->mensagem;
}

#endif
