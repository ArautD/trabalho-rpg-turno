#include "mago.h"
#include <iostream>

Mago::Mago(std::string _nome, int _pontosMagia, int _pontosVida, int _forca, int _defesa, std::string elem)
        : Personagem(_nome, _pontosVida, _forca, _defesa), pontosMagia(_pontosMagia), tipo ("Mago") {
            elemento = elem;
}

void Mago::mostrarStatus(){
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Magia: " << pontosMagia << "\n";
    }
 
    void Mago::atacar(Personagem& alvo){
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout << tipo << " " << nome << " lança um feitiço básico!\n";
 
        int dano = 1 + forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
        std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
        pontosMagia++;
    }

    void Mago::habilidadeEspecial(Personagem& alvo){
        if (pontosMagia >= 2){
            int opcao;

                std::cout << "\nEscolha o habilidade especial:\n";
                std::cout << "1 - Raio Congelante (Gelo)\n";
                std::cout << "2 - Magia cura\n";
                std::cout << "Digite sua escolha: ";
                std::cin >> opcao;

            switch (opcao){
                case 1: {
                    Habilidade raioGelo("Raio congelante", "Gelo", 12);
                    int dano = calcularDano(raioGelo, alvo);
                    alvo.receberDano(dano);

                    std::cout << "\n " << nome << " conjura " << raioGelo.nome
                            << " causando " << dano << " de dano!\n";
                    pontosMagia = 0;
                break;
                }
                case 2: 
                    std::cout << "\n===== MAGIA CURATIVA DE " << nome << " =====\n";
                    pontosVida += 10;
                    std::cout << nome << " recuperou 10 pontos de vida!\n";
                break;
            }
        } else {
            std::cout << "\n-----------------------------------------\n";
            std::cout << nome << " não tem magia suficiente!\n"; 
            std::cout << "-----------------------------------------\n";
        }
        
    }


