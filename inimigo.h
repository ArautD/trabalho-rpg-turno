#ifndef INIMIGO_H
#define INIMIGO_H

#include "personagem.h"

class Inimigo : public Personagem {
public:
    std::string tipo;
 
    Inimigo(std::string nome, int vida, int forca, int defesa, std::string tipo, std::string elem);
    void mostrarStatus() override;
    void atacar(Personagem& alvo) override;
    //void habilidadeEspecial(Personagem& alvo) override;
};

#endif