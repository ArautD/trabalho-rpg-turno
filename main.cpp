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

        void receberDano(int dano){
            pontosVida -= dano;
            if (pontosVida < 0) pontosVida = 0;
        }
};

class Guerreiro : public Personagem{
    public:
        int coragem;

        void atacar() override{
            int dano = ataque - alvo.defesa;
        } 
        void especial() override {
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



int main(){


    return 0;
}