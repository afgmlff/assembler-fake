#ifndef HFILE_H
#define HFILE_H

#include <fstream>
#include "vector"
#include "string"

class FileHandler {
public:
    virtual void getLine(std::string* linha) = 0;
    virtual void writeLine(std::string linha) = 0;
    virtual bool hasEnd() = 0;
    virtual void resetFile() = 0;
    virtual void finishWrite() {};
};

class MemFile : public FileHandler {
public:
    int linhaAtual = 0;
    std::vector<std::string> arquivo;
    void getLine(std::string *linha) override;
    void writeLine(std::string linha) override;
    bool hasEnd() override;
    void resetFile() override;
};

class PFile : public FileHandler {
public:
    std::fstream arquivo;
    explicit PFile(const char *nomeArquivo, bool modoDeEscrita = false);
    void getLine(std::string *linha) override;
    void writeLine(std::string linha) override;
    bool hasEnd() override;
    void resetFile() override;
    void finishWrite() override;
};

#endif