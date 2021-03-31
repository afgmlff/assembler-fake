#ifndef AUX_ARQUIVO_H
#define AUX_ARQUIVO_H

#include <string>
#include <map>
#include "fileHelper.hpp"
#include "error.hpp"
#include "helper.hpp"

using namespace std;

class AuxArquivo {
public:
    map<string, string> mapComponente = {};
    PFile *arquivo;
    FileHandler *arquivoPronto;
    MontadorErrors errors;

    explicit AuxArquivo(const string &nomeArquivo);

    void extraiCode();
};

#endif
