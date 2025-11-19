#ifndef ARQUEIRO_H
#define ARQUEIRO_H
#include <string>
#include "personagem.h"


class Arqueiro : public Personagem {
public:
    std::string tipo;
    int destreza;
 
    Arqueiro(std::string _nome, int _destreza, int _pontosVida, int _forca, int _defesa, std::string elem = "Elétrico");

    void mostrarStatus() override;
    void atacar(Personagem& alvo) override;
    void habilidadeEspecial(Personagem& alvo) override;
    
};      
#endif