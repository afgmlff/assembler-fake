#ifndef MONTADOR_ERROR
#define MONTADOR_ERROR


#include "../include/error.hpp"

using namespace std;

const char *MontadorException::what() const noexcept {
    return to_string(this->error).c_str();
}

void MontadorErrors::pushErro(MontadorException::tipoErro error, string linha, int numLinha) {
    errors.push_back((MontadorError) {error, linha, numLinha});
}

string MontadorErrors::mensagemError(MontadorException::tipoErro error) {
    switch (error) {
        case MontadorException::ROTULO_AUSENTE:
            return "Declaração/rótulo ausente";
        case MontadorException::ROTULO_REPETIDO:
            return "Declaração/rótulo repetido";
        case MontadorException::OPERACAO_INVALIDA:
            return "Diretiva/instrução inválida";
        case MontadorException::QUANTIDADE_OPERANDO:
            return "Instrução com a quantidade de operando errada";
        case MontadorException::OPERANDO_INVALIDO:
            return "Instrução com o tipo de operando inválido";
        case MontadorException::TOKEN_INVALIDO:
            return "Tokens inválidos";
        case MontadorException::DATA_FIRST:
            return "Seção DATA deve vir antes da seção TEXT";
    }
}

string MontadorErrors::errorTipo(MontadorException::tipoErro error) {
    if (error < MontadorException::QUANTIDADE_OPERANDO) {
        return "Erro Semântico";
    } else if (error == MontadorException::TOKEN_INVALIDO) {
        return "Erro Léxico";
    } else {
        return "Erro Sintático";
    }
}

bool MontadorErrors::contemErrors() {
    return !errors.empty();
}

string MontadorErrors::mensagemTodosErros() {
    string errorMessage;
    for (const auto &error: errors) {
        errorMessage = errorMessage + "\nLinha (" + to_string(error.numLinha) + ")" + ": " + mensagemError(error.code) + " (" + errorTipo(error.code) + ")"
                       "\nNo trecho: " + error.linha + "\n" +
                       "---" + "\n";
    }
    return errorMessage;
}

const char *PassagemException::what() const noexcept {
    return (this->mensagem).c_str();
}

string PassagemException::mensagemCompleta() {
    return "\nOcorreram erros durante a montagem:\n" + this->mensagem;
}

#endif