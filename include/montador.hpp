#ifndef MONTADOR_H
#define MONTADOR_H

#include <map>
#include <string>

#include "helper.hpp"
#include "error.hpp"
#include "fileHelper.hpp"

class Montador {
public:
    FileHandler *arquivo;
    MontadorErrors errors;

    map<string, int> mapSimbolos = {};

    map<string, int> mapInstrucao = {
            {"ADD", 1},
            {"SUB", 2},
            {"MULT", 3},
            {"DIV", 4},
            {"JMP", 5},
            {"JMPN", 6},
            {"JMPP", 7},
            {"JMPZ", 8},
            {"COPY", 9},
            {"LOAD", 10},
            {"STORE", 11},
            {"INPUT", 12},
            {"OUTPUT", 13},
            {"STOP", 14}
    };

    map<string, int> mapDiretiva = {
            {"SECTION", 0},
            {"SPACE",   1},
            {"CONST",   1},
    };

    explicit Montador(FileHandler *fileHandler);

    static int sizeInstDiretiva(const string &argumento);

    static void checkIfOperacaoValida(const Linha &linha);

    void primeiraPassagem();

    string segundaPassagem();
};

#endif
