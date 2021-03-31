#ifndef HFILE_H
#define HFILE_H

#include <fstream>
#include "vector"
#include "string"

class FileHandler {
public:
    virtual bool hasEnd() = 0;

    virtual void getLine(std::string* linha) = 0;
    virtual void writeLine(std::string linha) = 0;

    virtual void finishWrite() {};
    virtual void resetFile() = 0;
};

class MemFile : public FileHandler {
public:
    int percorreL = 0;

    std::vector<std::string> arquivo;

    bool hasEnd() override;

    void writeLine(std::string linha) override;
    void getLine(std::string *linha) override;


    void resetFile() override;
};

class PFile : public FileHandler {
public:
    std::fstream arquivo;

    explicit PFile(const char *file1, bool wEnable = false);

    bool hasEnd() override;

    void writeLine(std::string linha) override;
    void getLine(std::string *linha) override;

    void finishWrite() override;
    void resetFile() override;
};

#endif
