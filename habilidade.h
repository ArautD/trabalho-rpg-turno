#ifndef HABILIDADE_H
#define HABILIDADE_H
#include <string>

class Habilidade {
public:
    std::string nome;
    std::string elemento;   // Ex: "Fogo", "Gelo", "Elétrico"
    int danoBase;

    Habilidade(std::string _nome, std::string _elemento, int _danoBase);
};

#endif