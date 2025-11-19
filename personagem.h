#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <vector>
#include "Habilidade.h"

class Personagem {
public:
    std::string nome;
    std::string elemento;
    int pontosVida;
    int forca;
    int defesa;
    int forcaOriginal;
    bool estaDefendendo = false;

    std::vector<Habilidade> habilidades;

    
    Personagem(std::string _nome, int _pontosVida, int _forca, int _defesa);
    virtual ~Personagem();

    virtual void mostrarStatus();
    virtual void atacar(Personagem& alvo);
    //virtual void ataqueEspecial(Personagem& alvo);
    //virtual void usarMagia(Personagem& alvo);
    virtual void habilidadeEspecial(Personagem& alvo);
    virtual void defender();
    virtual void fugir();

    
    void receberDano(int dano);
    void adicionarHabilidades(const Habilidade& h);
    int calcularDano(const Habilidade& habilidade, Personagem& alvo);
};

#endif
