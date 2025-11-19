#include "Guerreiro.h"
#include <iostream>

Guerreiro::Guerreiro(std::string nome, int vida, int forca, int defesa, std::string elem)
    : Personagem(nome, vida, forca, defesa), tipo("Guerreiro") {
    elemento = elem;
}

void Guerreiro::mostrarStatus(){
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Coragem: " << coragem
                  << (covarde ? " (Covarde)" : "") << "\n";
    }
void Guerreiro::receberDano(int dano) {
        if (rodadasProtegido > 0) {
            dano /= 2;
            rodadasProtegido--;
            std::cout << nome << " está protegido! Dano reduzido para " << dano << ". Rodadas restantes: " << rodadasProtegido << "\n";
        }
        pontosVida -= dano;
        if (pontosVida < 0) pontosVida = 0;
    }
void Guerreiro::atacar(Personagem& alvo){
    if (covarde) {
        std::cout << "\n" << nome << " está covarde e perde o turno!\n";
        covarde = false;
        return;
    }
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.receberDano(dano);
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout << tipo << " " << nome << " atacou causando " << dano << " de dano!\n";
        coragem ++;
    }

    void Guerreiro::habilidadeEspecial(Personagem& alvo){
         
        if (coragem >= 2){
            int opcao;

                std::cout << "\nEscolha o habilidade especial:\n";
                std::cout << "1 - Espada Flamejante (Fogo) \n";
                std::cout << "2 - Grito de Guerra\n";
                std::cout << "Digite sua escolha: ";
                std::cin >> opcao;

            switch (opcao){
                case 1: {
                     Habilidade espadaFogo("Espada Flamejante", "Fogo", 10);
                    int dano = calcularDano(espadaFogo, alvo);
                    alvo.receberDano(dano);
                    std::cout << "\n " << nome << " usa " << espadaFogo.nome
                  << " causando " << dano << " de dano!\n";
                            break;
                }
                case 2: {
                    std::cout << "\n===== GRITO DE GUERRA DE " << nome << " =====\n";
                    rodadasProtegido = 2;
                    std::cout << nome << " ficará protegido e receberá menos dano por 2 rodadas!\n";
                    
                break;
            }
            }
        }else{
            std::cout << "\n-----------------------------------------\n";
            std::cout << "Você não tem pontos de coragem suficiente!";
            std::cout << "\n-----------------------------------------\n";

        
    }
}

