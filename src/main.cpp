#include <iostream>
#include "../include/montador.hpp"
#include "../include/auxArquivo.hpp"
#include "../include/helper.hpp"

int main(int argc, char **argv) {
    try {
        if (argc == 2) {// ./montador input.asm

            std::cout << "Arquivo de entrada: " << argv[1] << endl;
            AuxArquivo auxArquivo(argv[1]);
            auxArquivo.extraiCode();

            Montador montador(auxArquivo.arquivoPronto);
            montador.primeiraPassagem();
            criaSaidaMontador(montador.segundaPassagem(), argv[1]);
            std::cout << "Arquivo de saída: " << trocaExtensao(argv[1], ".obj") << std::endl;
        } else {
            printf("Favor, informar arquivo para execucao do montador. Ex.: \"./montador caminho/entrada.asm\n");
            return 1;
        }
    } catch (PassagemException &e) {
        std::cout << e.stackErros() << std::endl;
    }
    return 0;
};
