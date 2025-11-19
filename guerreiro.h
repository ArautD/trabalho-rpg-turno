#ifndef GUERREIRO_H
#define GUERREIRO_H

#include "Personagem.h"

class Guerreiro : public Personagem {
public:
    std::string tipo;
    int coragem = 0;
    int rodadasProtegido = 0;
    bool covarde = false;

    Guerreiro(std::string nome, int vida, int forca, int defesa, std::string elem = "Fogo");

    void receberDano(int dano);
    void mostrarStatus() override;
    void atacar(Personagem& alvo) override;
   // void ataqueEspecial(Personagem& alvo) override;
    void habilidadeEspecial(Personagem& alvo) override;
};

#endif
