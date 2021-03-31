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

std::string &lstrip(std::string &s);

std::string &rstrip(std::string &s);

std::string &strip(std::string &s);

bool isInteger(const std::string &s);

bool isVariavelValida(const string &variavel);


bool isLabel(const Linha &linha);

string trocaExtensao(string nome, const string &terminacao);

string concatLine(const Linha &linha);

void criaSaidaMontador(string codigo, string filename);

string maiusc(string str);

Linha splitLinha(string linha, bool isToThrowErros = true);

#endif
