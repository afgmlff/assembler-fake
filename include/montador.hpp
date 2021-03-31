#ifndef MONTADOR_H
#define MONTADOR_H

#include <map>
#include <string>

#include "helper.hpp"
#include "error.hpp"
#include "fileHelper.hpp"

class Montador {
public:
    void primeiraPassagem();
    //void segundaPassagem();
    string segundaPassagem();

    AssembleErr errors;

    map<string, int> mapSimbolos = {};

    map<string, int> mapInstrucao = {
            {"ADD", 1},
            {"SUB", 2},
            {"MUL", 3},
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

    FileHandler *arquivo;

    explicit Montador(FileHandler *fileHandler);

    static int sizeInstDiretiva(const string &argumento);

    static void validaOPlinha(const Linha &linha);


};

#endif
