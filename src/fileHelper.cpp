#ifndef HFILE
#define HFILE

#include "../include/fileHelper.hpp"

void MemFile::getLine(std::string *linha) {
    if (!this->hasEnd()) {
        *linha = arquivo[this->linhaAtual];
        this->linhaAtual++;
    }
}

void MemFile::writeLine(std::string linha) {
    arquivo.push_back(linha);
}

bool MemFile::hasEnd() {
    return arquivo.size() == linhaAtual;
}

void MemFile::resetFile() {
    linhaAtual = 0;
}

PFile::PFile(const char *nomeArquivo, bool modoDeEscrita) {
    if (modoDeEscrita) {
        arquivo.open(nomeArquivo, std::ios::out | std::ios::trunc);
    } else {
        arquivo.open(nomeArquivo);
    }
    if (!arquivo)
        throw std::invalid_argument("Arquivo não encontrado");
}

void PFile::getLine(std::string *linha) {
    std::getline(this->arquivo, *linha);
}

void PFile::writeLine(std::string linha) {
    arquivo << linha << std::endl;
}

bool PFile::hasEnd() {
    return arquivo.eof();
}

void PFile::resetFile() {
    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);
}

void PFile::finishWrite() {
    arquivo.close();
}

#endif