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
    AssembleErr errors;

//    int data_section_start = 0;
//    int text_section_start = 0;

    map<string, string> mapComponente = {};
    PFile *arquivo;

    FileHandler *arquivoPronto;


    explicit AuxArquivo(const string &nomeArquivo);

    void extraiCode();
};

#endif
