#include "Menu.h"
#include <iostream>

// ====================== MENU DE BATALHA ======================
void menuBatalha(Personagem& jogador, Personagem& inimigo) {
    int rodada = 1;

    while (jogador.pontosVida > 0 && inimigo.pontosVida > 0) {
 
        std::cout << "\n\n============================================\n";
        std::cout << "         STATUS DA BATALHA \n";
        std::cout << "============================================\n";
        std::cout << "Rodada: " << rodada << "\n";

        std::cout << "\n--- Jogador ---\n";
        jogador.mostrarStatus();
 
        std::cout << "\n--- Inimigo ---\n";
        inimigo.mostrarStatus();
 
        std::cout << "\n============================================\n";
        std::cout << "1  Atacar\n";
        std::cout << "2  Habilidade Epecial\n";
        std::cout << "3  Defender\n";
        std::cout << "4  Fugir\n";
        std::cout << "Escolha sua ação: ";
 
        int escolha;
        std::cin >> escolha;
 
        switch (escolha) {
            case 1: jogador.atacar(inimigo); break;
            case 2: jogador.habilidadeEspecial(inimigo); break;
            case 3: jogador.defender(); break;
            case 4: jogador.fugir();
                    if (jogador.pontosVida <= 0) return;
                    break;
            default: std::cout << "\n Escolha inválida!\n"; break;
        }
 
        if (inimigo.pontosVida <= 0) break;
 
        inimigo.atacar(jogador);
 
        // Resetar defesa se estava defendendo
        if (jogador.estaDefendendo) {
            jogador.defesa -= 5;
            jogador.estaDefendendo = false;
            std::cout << "🔄 " << jogador.nome << " terminou de se defender. Defesa volta ao normal.\n";
        }
        rodada++;
    }
 
    if (jogador.pontosVida <= 0)
        std::cout << "\n " << jogador.nome << " foi derrotado!\n";
    else if (inimigo.pontosVida <= 0)
        std::cout << "\n" << inimigo.nome << " foi derrotado!\n";
}
 
// ====================== MENU PRINCIPAL ======================
void menuPrincipal() {
    int escolha;
 
    std::cout << "\n============================================\n";
    std::cout << "            MENU PRINCIPAL \n";
    std::cout << "============================================\n";
    std::cout << "Escolha seu personagem:\n";
    std::cout << "1  Guerreiro (Elemento: Fogo)\n";
    std::cout << "2  Mago (Elemento: Gelo)\n";
    std::cout << "3  Arqueiro (Elemento: Elétrico)\n";
    std::cout << "Digite sua escolha: ";
 
    std::cin >> escolha;
 
    Personagem* jogador = nullptr;
 
    switch (escolha) {
        case 1:
            jogador = new Guerreiro("Aragorn", 80, 15, 5);
            std::cout << "\n Você escolheu o Guerreiro!\n";
            break;
 
        case 2:
            jogador = new Mago("Gandalf", 0, 60, 12, 5);
            std::cout << "\n Você escolheu o Mago!\n";
            break;
 
        case 3:
            jogador = new Arqueiro("Legolas", 2, 70, 14, 6);
            std::cout << "\n Você escolheu o Arqueiro!\n";
            break;
 
        default:
            std::cout << "\n Opção inválida! Guerreiro selecionado.\n";
            jogador = new Guerreiro("Aragorn", 80, 15, 5);
            break;
    }
 
    // =====================
    // 2 INIMIGOS NORMAIS
    // =====================
    for (int i = 1; i <= 2; i++) {
        std::cout << "\n\n============================================\n";
        std::cout << "             BATALHA " << i << " \n";
        std::cout << "============================================\n";
 
        Inimigo orc("Gorg", 60, 12, 4, "Troll","Gelo");
 
        menuBatalha(*jogador, orc);
 
        if (jogador->pontosVida <= 0) {
            std::cout << "\n Você morreu. Fim do jogo.\n";
            delete jogador;
            return;
        }
 
        std::cout << "\n Você derrotou o inimigo " << i << "!\n";
    }
 
    // =====================
    // CHEFE FINAL
    // =====================
    std::cout << "\n\n============================================\n";
    std::cout << "            O CHEFE APARECE! \n";
    std::cout << "============================================\n";
 
    Inimigo chefe("Azgalor", 120, 20, 10, "CHEFE", "Água");
 
    menuBatalha(*jogador, chefe);
 
    if (jogador->pontosVida <= 0) {
        std::cout << "\n Você foi derrotado pelo chefe.\n";
        delete jogador;
        return;
    }
 
    std::cout << "\n\n PARABÉNS! Você venceu TODOS os inimigos! \n";
 
    delete jogador;
}