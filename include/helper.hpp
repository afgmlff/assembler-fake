#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <regex>

#include "fileHelper.hpp"
#include "error.hpp"

using namespace std;

struct Linha {
    string rotulo;
    string operacao;
    string op1;
    string op2;
};

bool isInteger(const std::string &s);

bool isVariavelValida(const string &variavel);

string toUpperCase(string str);

bool somenteRotulo(const Linha &linha);

string trocarTipo(string nome, const string &terminacao);

Linha coletaTermosDaLinha(string linha, bool isToThrowErros = true);

string linhaToString(const Linha &linha);

void gerarArquivoObjeto(string codigo, string filename);

std::string &lstrip(std::string &s);

// strip from end
std::string &rstrip(std::string &s);

//strip()
std::string &strip(std::string &s);

#endif