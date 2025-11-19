#include "inimigo.h"
#include <iostream>

Inimigo::Inimigo(std::string nome, int vida, int forca, int defesa, std::string tipo, std::string elem)
        : Personagem(nome, vida, forca, defesa), tipo(tipo) {
            elemento = elem;
        }
    
    void Inimigo::mostrarStatus(){
        std::cout << tipo << " " << nome
                  << " | Elemento: " << elemento
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa << "\n";
    }
    void Inimigo::atacar(Personagem& alvo)  {
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
 
        std::cout << "\n===== TURNO DO INIMIGO =====\n";
        std::cout << tipo << " " << nome << " realiza um ataque feroz causando " << dano << " de dano!\n";
    }