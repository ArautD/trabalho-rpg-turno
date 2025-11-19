#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <cstdlib>
#include <ctime>

using namespace std;

// ====================== CLASSE HABILIDADE ======================
class Habilidade {
public:
    std::string nome;
    std::string elemento;   // Ex: "Fogo", "Gelo", "Elétrico"
    int danoBase;

    Habilidade(std::string _nome, std::string _elemento, int _danoBase)
        : nome(_nome), elemento(_elemento), danoBase(_danoBase) {}
};

// ====================== CLASSE BASE ======================
class Personagem {
public:
    std::string nome;
    std::string elemento;
    int pontosVida;
    int forca;
    int defesa;
    int forcaOriginal;
    bool efeitoAtivo = false;
    bool estaDefendendo = false;

    std::vector<Habilidade> habilidades;

    Personagem(std::string _nome, int _pontosVida, int _forca, int _defesa)
        : nome(_nome), pontosVida(_pontosVida), forca(_forca), defesa(_defesa), forcaOriginal(_forca) {}

    virtual ~Personagem() = default;

    // ====================== MÉTODOS VIRTUAIS ======================
    virtual void mostrarStatus() {
        std::cout << "Vida: " << pontosVida << "\n";
    }

    virtual void atacar(Personagem& alvo) {
        if (efeitoAtivo) {
            forca = forcaOriginal;
            efeitoAtivo = false;
            std::cout << "\n" << nome << " recuperou sua força!\n";
        }
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.receberDano(dano);
        std::cout << nome << " atacou causando " << dano << " de dano!\n";
    }

    virtual void ataqueEspecial(Personagem& alvo) {}
    virtual void usarMagia(Personagem& alvo) {}
    virtual void habilidadeElemental(Personagem& alvo) {}

    // ====================== DEFENDER ======================
    virtual void defender() {
        estaDefendendo = true;
        std::cout << "\n" << nome << " está se defendendo! Sua defesa aumentará temporariamente.\n";
        defesa += 5;
    }

    // ====================== FUGIR ======================
    virtual void fugir() {
        std::srand(static_cast<unsigned int>(time(nullptr)));
        int chance = std::rand() % 100;
        if (chance < 50) {
            std::cout << "\n" << nome << " conseguiu fugir da batalha!\n";
            pontosVida = 0;
        } else {
            std::cout << "\n" << nome << " tentou fugir, mas falhou!\n";
        }
    }

    // ====================== UTILITÁRIOS ======================
    void receberDano(int dano) {
        pontosVida -= dano;
        if (pontosVida < 0) pontosVida = 0;
    }

    void adicionarHabilidades(const Habilidade& h) {
        habilidades.push_back(h);
    }

    int calcularDano(const Habilidade& habilidade, Personagem& alvo) {
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
};

// ====================== GUERREIRO ======================
class Guerreiro : public Personagem {
public:
    std::string tipo;
    int coragem = 2;
    bool covarde = false;

    Guerreiro(std::string nome, int vida, int forca, int defesa, std::string elem = "Fogo")
        : Personagem(nome, vida, forca, defesa), tipo("Guerreiro") {
            elemento = elem;
        }

    void mostrarStatus() override {
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Coragem: " << coragem
                  << (covarde ? " (Covarde)" : "") << "\n";
    }

    void atacar(Personagem& alvo) override {
        if (covarde) {
            std::cout << "\n" << nome << " está covarde e perde o turno!\n";
            covarde = false;
            coragem = 2;
            return;
        }
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.receberDano(dano);
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout << tipo << " " << nome << " atacou causando " << dano << " de dano!\n";
    }

    void ataqueEspecial(Personagem& alvo) override {
        if (covarde) {
            std::cout << "\n" << nome << " está covarde e não pode usar especial!\n";
            return;
        }
        if (coragem > 0) {
            int dano = (forca * 2) - (alvo.defesa / 2);
            if (dano < 0) dano = 0;
            alvo.receberDano(dano);
            coragem--;
            std::cout << "\n===== ATAQUE ESPECIAL DE " << nome << " =====\n";
            std::cout << "Ataque corajoso causou " << dano << " de dano!\n";
            std::cout << "Coragem restante: " << coragem << "\n";
            if (coragem == 0) {
                covarde = true;
                std::cout << nome << " ficou covarde e perderá o próximo turno!\n";
            }
        } else {
            std::cout << "\nVocê não tem coragem suficiente!\n";
        }
    }

    void habilidadeElemental(Personagem& alvo) override {
        Habilidade espadaFogo("Espada Flamejante", "Fogo", 10);
        int dano = calcularDano(espadaFogo, alvo);
        alvo.receberDano(dano);
        std::cout << "\n " << nome << " usa " << espadaFogo.nome
                  << " causando " << dano << " de dano!\n";
    }
};

// ====================== MAGO ======================
class Mago : public Personagem {
public:
    std::string tipo;
    int pontosMagia;
 
    Mago(std::string _nome, int _pontosMagia, int _pontosVida, int _forca, int _defesa, std::string elem = "Gelo")
        : Personagem(_nome, _pontosVida, _forca, _defesa), pontosMagia(_pontosMagia), tipo ("Mago") {
            elemento = elem;
        }
        
    void mostrarStatus() override{
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Magia: " << pontosMagia << "\n";
    }
 
    void atacar(Personagem& alvo) override {
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout << tipo << " " << nome << " lança um feitiço básico!\n";
 
        int dano = 1 + forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
        std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
        pontosMagia++;
    }
 
    void ataqueEspecial(Personagem& alvo) override {
        if (pontosMagia >= 2) {
            std::cout << "\n===== FEITIÇO ÉPICO DE " << nome << " =====\n";
            std::cout << nome << " conjura um feitiço devastador!\n";
 
            int dano = 20 + forca - alvo.defesa;
            if (dano < 0) dano = 0;
 
            alvo.receberDano(dano);
            std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
            pontosMagia = 0;
        } else {
            std::cout << nome << " não tem magia suficiente!\n";
        }
    }

    void habilidadeElemental(Personagem& alvo){
        Habilidade raioGelo("Raio congelante", "Gelo", 12);
        int dano = calcularDano(raioGelo, alvo);
        alvo.receberDano(dano);

        std::cout << "\n " << nome << " conjura " << raioGelo.nome
                  << " causando " << dano << " de dano!\n";
    }
};
 
// ====================== ARQUEIRO ======================
class Arqueiro : public Personagem {
public:
    std::string tipo;
    int destreza;
 
    Arqueiro(std::string _nome, int _destreza, int _pontosVida, int _forca, int _defesa, std::string elem = "Elétrico")
        : Personagem(_nome, _pontosVida, _forca, _defesa), destreza(_destreza), tipo("Arqueiro") {
            elemento = elem;
        }
 
    void mostrarStatus() override{
        std::cout << tipo << " " << nome
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa
                  << " | Pontos de Destreza: " << destreza << "\n";
    }
 
    void atacar(Personagem& alvo) override {
        std::cout << "\n===== TURNO DO JOGADOR: " << nome << " =====\n";
        std::cout<< tipo << " " << nome << " dispara uma flecha!\n";
 
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
        std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
        destreza++;
    }
 
    void ataqueEspecial(Personagem& alvo) override {
        if (destreza >= 2) {
            std::cout << "\n===== RAJADA DE FLECHAS DE " << nome << " =====\n";
            std::cout << "Ataque múltiplo!\n";
 
            int dano = (forca * 2) - alvo.defesa;
            if (dano < 0) dano = 0;
 
            alvo.receberDano(dano);
            std::cout << alvo.nome << " sofreu " << dano << " de dano!\n";
            destreza = 0;
        } else {
            std::cout << "\n" << nome << " não tem destreza suficiente!\n";
        }
    }
 
    void usarMagia(Personagem& alvo) override {
        std::cout << "\n===== FLECHA ENVENENADA DE " << nome << " =====\n";
 
        int dano = 2 - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
        alvo.forca -= 2;
        alvo.efeitoAtivo = true;
 
        std::cout << alvo.nome << " perdeu 2 pontos de força temporariamente!\n";
    }

    void habilidadeElemental(Personagem& alvo){
        Habilidade flechaEletrica("Flecha elétrica", "Elétrico", 12);
        int dano = calcularDano(flechaEletrica, alvo);
        alvo.receberDano(dano);

        std::cout << "\n " << nome << " dispara " << flechaEletrica.nome
                  << " causando " << dano << " de dano!\n";
    }
};
 
// ====================== INIMIGO ======================
class Inimigo : public Personagem {
public:
    std::string tipo;
 
    Inimigo(std::string nome, int vida, int forca, int defesa, std::string tipo, std::string elem)
        : Personagem(nome, vida, forca, defesa), tipo(tipo) {
            elemento = elem;
        }
   
    void mostrarStatus() override{
        std::cout << tipo << " " << nome
                  << " | Elemento: " << elemento
                  << " | Vida: " << pontosVida
                  << " | Força: " << forca
                  << " | Defesa: " << defesa << "\n";
    }
 
    void atacar(Personagem& alvo) override {
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
 
        std::cout << "\n===== TURNO DO INIMIGO =====\n";
        std::cout << tipo << " " << nome << " realiza um ataque feroz causando " << dano << " de dano!\n";
    }
 
    void ataqueEspecial(Personagem& alvo) override {
        int dano = (forca * 2) - alvo.defesa;
        if (dano < 0) dano = 0;
 
        alvo.receberDano(dano);
 
        std::cout << "\n ATAQUE ESPECIAL DO INIMIGO!\n";
        std::cout << tipo << " " << nome << " devastou com " << dano << " de dano!\n";
    }
};
 
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
        std::cout << "2  Ataque Especial\n";
        std::cout << "3  Defender\n";
        std::cout << "4  Habilidade Elemental\n";
        std::cout << "5  Fugir\n";
        std::cout << "Escolha sua ação: ";
 
        int escolha;
        std::cin >> escolha;
 
        switch (escolha) {
            case 1: jogador.atacar(inimigo); break;
            case 2: jogador.ataqueEspecial(inimigo); break;
            case 3: jogador.defender(); break;
            case 4: jogador.habilidadeElemental(inimigo); break;
            case 5: jogador.fugir();
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
 
// ====================== MAIN ======================
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
 
    menuPrincipal();
 
    return 0;
}
 