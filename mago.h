#ifndef MAGO_H
#define MAGO_H
#include <string>
#include "personagem.h"

class Mago : public Personagem {
public:
    std::string tipo;
    int pontosMagia;
 
    Mago(std::string _nome, int _pontosMagia, int _pontosVida, int _forca, int _defesa, std::string elem = "Gelo");

    void mostrarStatus() override;
    void atacar(Personagem& alvo) override;
    //void ataqueEspecial(Personagem& alvo) override;
    void habilidadeEspecial(Personagem& alvo) override;
};
#endif