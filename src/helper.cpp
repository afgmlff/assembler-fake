#ifndef HELPER
#define HELPER

#include "../include/helper.hpp"

using namespace std;

std::string &lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


std::string &rstrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}


std::string &strip(std::string &s) {
    return lstrip(rstrip(s));
}



bool isVariavelValida(const string &variavel) {
    return variavel.size() <= 50 && regex_match(variavel, regex("^[a-zA-Z_$][a-zA-Z_$0-9]*"));
}



bool isLabel(const Linha &linha) {
    return !linha.rotulo.empty() and linha.operacao.empty() and linha.op1.empty();
}

string trocaExtensao(string nome, const string &terminacao) {
    if (std::string::npos == nome.find('.')) {
        return nome + '.' + terminacao;
    } else {
        return nome.replace(nome.find_last_of('.'), nome.length(), terminacao);
    }
}

bool isInteger(const std::string &s) {
    return std::regex_match(s, std::regex("-?[0-9]{0,10}"));
}

Linha splitLinha(string linha, bool detectarErro) {
    string tokens[4];
    int count = 0;
    bool flag = false;

    linha = strip(linha); //remove espaços

    if (string::npos == linha.find(':'))
        count++;

    for (char ch : linha) {
        if (ch == ';') { //tira coment
            break;
        }

        if (count == 4) {
            if (detectarErro) {
                throw EnumExcecao(EnumExcecao::QTD_OP_ERRADA); //caso haja incremento apos o ultimo operando esperado
            }
            else {
                break;
            }
        }

        if (ch == ' ' or ch == ',' or (ch == ':' and count == 0)) {//para o COPY
            if (!flag)
                count++;
            flag = true;
        }
        else {
            flag = false;
            tokens[count] += ch;
        }
    }

    for (auto &arg : tokens) {
        if (tokens[1] != "CONST") {
            if (!arg.empty() and !isVariavelValida(arg) and detectarErro) {
                throw EnumExcecao(EnumExcecao::TOKEN_INVALIDO);
            }
        }
    }

    Linha l = {maiusc(tokens[0]), maiusc(tokens[1]), maiusc(tokens[2]),maiusc(tokens[3])};
    return l;
}

string concatLine(const Linha &linha) {
    string str;
    if (!linha.rotulo.empty()) {
        str += linha.rotulo + ": ";
    }
    if (!linha.op1.empty()) {
        str += linha.operacao + ' ';
    } else {
        str += linha.operacao;
    }
    if (!linha.op1.empty() and !linha.op2.empty()) {
        str += linha.op1 + ", " + linha.op2;
    } else if (!linha.op1.empty()) {
        str += linha.op1;
    }
    return str;
}

void criaSaidaMontador(string codigo, string filename) {
    auto *arq = new PFile(trocaExtensao(filename, ".obj").c_str(), true);
    arq->writeLine(codigo);
    arq->finishWrite();
}

string maiusc(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}


#endif
