#include <iostream>
#include <string>

class Personagem{
    public:
        std::string nome;
        int pontosVida;
        int forca;
        int defesa;

        virtual void atacar(){}
};

class Guerreiro : public Personagem{
    public:
        int coragem;
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