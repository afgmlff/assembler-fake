#ifndef HFILE
#define HFILE

#include "../include/fileHelper.hpp"

bool PFile::hasEnd() {
    return arquivo.eof();
}

void MemFile::getLine(std::string *linha) {
    if (!this->hasEnd()) {
        *linha = arquivo[this->percorreL];
        this->percorreL++;
    }
}

void MemFile::writeLine(std::string linha) {
    arquivo.push_back(linha);
}

bool MemFile::hasEnd() {
    return arquivo.size() == percorreL;
}

void MemFile::resetFile() {
    percorreL = 0;
}

PFile::PFile(const char *file1, bool wEnable) {
    if (!wEnable) {
        arquivo.open(file1);
    } else {
        arquivo.open(file1, std::ios::out | std::ios::trunc);
    }
    if (!arquivo)
        throw std::invalid_argument("O arquivo não foi encontrado.");
}

void PFile::getLine(std::string *linha) {
    std::getline(this->arquivo, *linha);
}

void PFile::writeLine(std::string linha) {
    arquivo << linha << std::endl;
}

void PFile::finishWrite() {
    arquivo.close();
}

void PFile::resetFile() {
    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);
}

#endif
