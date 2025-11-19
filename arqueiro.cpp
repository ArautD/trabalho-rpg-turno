#include "arqueiro.h"
#include <iostream>

Arqueiro::Arqueiro(std::string _nome, int _destreza, int _pontosVida, int _forca, int _defesa, std::string elem)
        : Personagem(_nome, _pontosVida, _forca, _defesa), destreza(_destreza), tipo("Arqueiro") {
            elemento = elem;
        }
 
    void Arqueiro::mostrarStatus(){
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Destreza: " << destreza << "\n";
    }
 
    void Arqueiro::atacar(Personagem& alvo) {
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout<< tipo << " " << nome << " dispara uma flecha!\n";
 
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
        std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
        destreza++;
    }

    void Arqueiro::habilidadeEspecial(Personagem& alvo){
         
        if (destreza >= 2){
        int opcao;
                std::cout << "\nEscolha o habilidade especial:\n";
                std::cout << "1 - Flecha Encantada (Elétrico) \n";
                std::cout << "2 - Flecha Venenosa (Veneno)\n";
                std::cout << "Digite sua escolha: ";
                std::cin >> opcao;


            switch (opcao){
                case 1: {
                     Habilidade flechaEletrica("Flecha elétrica", "Elétrico", 12);
                    int dano = calcularDano(flechaEletrica, alvo);
                    alvo.receberDano(dano);

                    std::cout << "\n " << nome << " dispara " << flechaEletrica.nome
                            << " causando " << dano << " de dano!\n";
                            break;
                }
                case 2: {
                    std::cout << "\n===== FLECHA ENVENENADA DE " << nome << " =====\n";
                    int dano = 14 - alvo.defesa;
                    if (dano < 0) dano = 0;
                    alvo.receberDano(dano);
                    alvo.defesa = 0;
                    std::cout << alvo.nome << " perdeu 2 pontos de força temporariamente!\n";
               

                break;
             }
            }
        }else{
            std::cout << "\n-----------------------------------------\n";
            std::cout << "Você não tem pontos de destreza suficiente!";
            std::cout << "\n-----------------------------------------\n";
        }
    }