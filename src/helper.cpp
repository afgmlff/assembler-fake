#ifndef HELPER
#define HELPER

#include "../include/helper.hpp"

using namespace std;

bool isInteger(const std::string &s) {
    return std::regex_match(s, std::regex("-?[0-9]{0,10}"));
}

bool isVariavelValida(const string &variavel) {
    return variavel.size() <= 50 && regex_match(variavel, regex("^[a-zA-Z_$][a-zA-Z_$0-9]*"));
}

string toUpperCase(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool somenteRotulo(const Linha &linha) {
    return !linha.rotulo.empty() and linha.operacao.empty() and linha.op1.empty();
}

string trocarTipo(string nome, const string &terminacao) {
    if (std::string::npos == nome.find('.')) {
        return nome + '.' + terminacao;
    } else {
        return nome.replace(nome.find_last_of('.'), nome.length(), terminacao);
    }
}

Linha coletaTermosDaLinha(string linha, bool isToThrowErros) {
    string elementos[4];
    int cont = 0;
    bool jaPulou = false;

    linha = strip(linha); //remove espaços
    
    if (string::npos == linha.find(':'))
        cont++;

    for (char ch : linha) {
        if (ch == ';') { //tira coment

            break;
        }

        if (cont == 4) {
            if (isToThrowErros) {
                throw MontadorException(MontadorException::QUANTIDADE_OPERANDO);
            } else {
                break;
            }
        }

        if (ch == ' ' or ch == ',' or (ch == ':' and cont == 0)) {//para o COPY
            if (!jaPulou)
                cont++;
            jaPulou = true;
        } else {
            jaPulou = false;
            elementos[cont] += ch;
        }
    }

    for (auto &elemento : elementos) {
        if (elementos[1] != "CONST") {

            if (!elemento.empty() and !isVariavelValida(elemento) and isToThrowErros) {
                throw MontadorException(MontadorException::TOKEN_INVALIDO);
            }
        }
    }

    Linha l = {toUpperCase(elementos[0]),
               toUpperCase(elementos[1]),
               toUpperCase(elementos[2]),
               toUpperCase(elementos[3])};
    return l;
}

string linhaToString(const Linha &linha) {
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

void gerarArquivoObjeto(string codigo, string filename) {
    auto *arq = new PFile(trocarTipo(filename, ".obj").c_str(), true);
    arq->writeLine(codigo);
    arq->finishWrite();
}

// strip from start
std::string &lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// strip from end
std::string &rstrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// strip from both ends
std::string &strip(std::string &s) {
    return lstrip(rstrip(s));
}

#endif