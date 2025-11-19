#include "Personagem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Personagem::Personagem(std::string _nome, int _pontosVida, int _forca, int _defesa)
    : nome(_nome), pontosVida(_pontosVida), forca(_forca), defesa(_defesa), forcaOriginal(_forca) {}

Personagem::~Personagem() = default;

void Personagem::mostrarStatus() {
    std::cout << "Vida: " << pontosVida << "\n";
}

void Personagem::atacar(Personagem& alvo) {
    int dano = forca - alvo.defesa;
    if (dano < 0) dano = 0;
    alvo.receberDano(dano);
    std::cout << nome << " atacou causando " << dano << " de dano!\n";
}

//void Personagem::ataqueEspecial(Personagem& alvo) {}
//void Personagem::usarMagia(Personagem& alvo) {}
void Personagem::habilidadeEspecial(Personagem& alvo) {}

void Personagem::defender() {
    estaDefendendo = true;
    std::cout << "\n" << nome << " está se defendendo! Sua defesa aumentará temporariamente.\n";
    defesa += 5;
}

void Personagem::fugir() {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int chance = std::rand() % 100;
    if (chance < 50) {
        std::cout << "\n" << nome << " conseguiu fugir da batalha!\n";
        pontosVida = 0;
    } else {
        std::cout << "\n" << nome << " tentou fugir, mas falhou!\n";
    }
}

void Personagem::receberDano(int dano) {
    pontosVida -= dano;
    if (pontosVida < 0) pontosVida = 0;
}

void Personagem::adicionarHabilidades(const Habilidade& h) {
    habilidades.push_back(h);
}

int Personagem::calcularDano(const Habilidade& habilidade, Personagem& alvo) {
    int dano = habilidade.danoBase + forca - alvo.defesa;

    if (habilidade.elemento == "Fogo" && alvo.elemento == "Gelo") {
        dano = static_cast<int>(dano * 1.5);
    } else if (habilidade.elemento == "Gelo" && alvo.elemento == "Fogo") {
        dano = static_cast<int>(dano * 0.75);
    } else if (habilidade.elemento == "Elétrico" && alvo.elemento == "Água") {
        dano = static_cast<int>(dano * 1.5);
    } else if (habilidade.elemento == "Água" && alvo.elemento == "Elétrico") {
        dano = static_cast<int>(dano * 0.75);
    }

    if (dano < 0) dano = 0;
    return dano;
}
