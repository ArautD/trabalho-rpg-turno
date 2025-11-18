#include <iostream>
#include <string>

class Personagem{
    public:
        std::string nome;
        int pontosVida;
        int forca;
        int defesa;

        virtual ~Personagem() = default;
        virtual void atacar(Personagem& alvo) = 0;
        virtual void especial(Personagem& alvo) = 0;
        virtual void defender() {
        std::cout << nome << " está defendendo!\n";
    }
    virtual void fugir() {
        std::cout << nome << " fugiu da batalha!\n";
    }

        void receberDano(int dano){
            pontosVida -= dano;
            if (pontosVida < 0) pontosVida = 0;
        }
};

class Guerreiro : public Personagem{
    public:
        int coragem = 2;
        bool covarde = false;

        void sttCovarde (){
            std::cout << "O guerreiro se encontra covarde e perderá seu próximo turno\n";
        }

        void atacar(Personagem& alvo) override{

            if (covarde) {
                sttCovarde();
                covarde = false;
                coragem = 2;
                return;
            }
            int dano = forca - alvo.defesa;
            if ( dano < 0) dano = 0;
            alvo.receberDano(dano);

            std:: cout << "o Ataque causou " << dano << " de dano\n";
        } 

        void especial(Personagem& alvo) override {

            if (covarde){
                sttCovarde();
                return;
            }
            if (coragem > 0){
                int dano = (forca * 2) - (alvo.defesa /2);
                if (dano < 0) dano = 0;
                alvo.receberDano(dano);
                coragem --;

                std::cout << nome << " usou ataque corajoso causando " << dano << " /Coragem Restante: " << coragem << "\n";

                if (coragem == 0){
                    covarde = true;
                    sttCovarde();
                }
            } else {
                std::cout << "Você não tem coragem sucificiente! \n";
            }
            
        }

};

class Mago : public Personagem{
    public:
        int pontosMagia;
    
};

class Arqueiro : public Personagem{
    public:
        int destreza;
};

class Inimigo : public Personagem {
public:
    std::string tipo; // exemplo: "Orc", "Goblin", "Dragão"

    Inimigo(std::string nome, int vida, int forca, int defesa, std::string tipo)
        : tipo(tipo) {
        this->nome = nome;
        this->pontosVida = vida;
        this->forca = forca;
        this->defesa = defesa;
    }

    void atacar(Personagem& alvo) override {
        int dano = forca - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.receberDano(dano);
        std::cout << tipo << " " << nome << " atacou causando " << dano << " de dano!\n";
    }

    void especial(Personagem& alvo) override {
        int dano = (forca * 2) - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.receberDano(dano);
        std::cout << tipo << " " << nome << " usou ataque especial causando " << dano << " de dano!\n";
    }
};

Inimigo criarOrc() {
    return Inimigo("Gorg", 80, 15, 5, "Orc");
}

/*Guerreiro personagemEscolhido(std::string nome){
            Guerreiro g;
            g.nome = nome;
            g.pontosVida = 20;
            g.forca = 20;
            g.defesa = 5;
            g.coragem = 2;
            g.covarde = false;
            return g;
        }*/

int main(){

    Guerreiro g;
    g.nome = "Thor";
    g.pontosVida = 100;
    g.forca = 20;
    g.defesa = 5;

    Inimigo orc = criarOrc();
    system("cls");
    std::cout << " ===================================================\n ";
    g.atacar(orc);
    orc.atacar(g);
    g.especial(orc);
    orc.especial(g);
    std::cout << " ===================================================\n ";


    return 0;
}