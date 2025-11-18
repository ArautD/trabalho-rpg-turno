#include <iostream>
#include <string>
#include <vector>

class Personagem{
    public:
        std::string nome;
        int pontosVida;
        int forca;
        int defesa;
        std::vector<std::string> habilidades;
        bool estaDefendendo = true;

        Personagem(std::string _nome, int _pontosVida, int _forca, int _defesa, std::vector<std::string> _habilidades){
            nome = _nome;
            pontosVida = _pontosVida;
            forca = _forca;
            defesa = _defesa;
            habilidades = _habilidades;
        }
        virtual void atacar(Personagem* inimigo){}

        virtual void ataqueEspecial(Personagem* inimigo){}

        virtual void defender(){
            estaDefendendo = true;
        }

        virtual void fugir(){}
};

class Guerreiro : public Personagem{
    public:
        int coragem;

};

class Mago : public Personagem{
    public:
        int pontosMagia = 0;

        Mago(int _pontosMagia, std::string _nome, int _pontosVida, int _forca, int _defesa, std::vector<std::string> _habilidades) : Personagem(_nome, _pontosVida, _forca, _defesa, _habilidades){
            pontosMagia = _pontosMagia;
        }

        void atacar(Personagem* inimigo) override{
            std::cout <<"\nMago lanca um feitico basico, nao eh muito efetivo\n\n";
            int dano = 1 + forca - inimigo->defesa;
            if(dano < 0) {
                dano = 0;
            }
            inimigo->pontosVida -= dano;
            std::cout << inimigo->nome << " sofreu " << dano << " de dano!\n";
            pontosMagia++;
        }

        void ataqueEspecial(Personagem* inimigo) override{
            if(pontosMagia == 2){
                std::cout <<"\nMago lança um feitiço de nível épico, é muito efetivo\n\n";
                int dano = 20 + forca - inimigo->defesa;
                if(dano < 0) {
                    dano = 0;
                }
                inimigo->pontosVida -= dano;
                std::cout << inimigo->nome << " sofreu " << dano << " de dano!\n";
                pontosMagia = 0;
            }else{
                std::cout <<"\nMago ainda nao tem pontos o suficente\n\n";
            }
        }

        void defender() override{
            std::cout <<"\nMago cria uma bola de energia e se protege do ataque\n\n";
            estaDefendendo = true;
        }

        void fugir() override{
            std::cout <<"\nMago se teletransportou da briga\n\n";
        }
};

class Arqueiro : public Personagem{
    public:
        int destreza;
};


class Monstro : public Personagem{
public:
    Monstro(std::string _nome, int _pontosVida, int _forca, int _defesa, std::vector<std::string> _habilidades)
    : Personagem(_nome, _pontosVida, _forca, _defesa, _habilidades){}

    void atacar(Personagem* inimigo) override{
        std::cout <<"\nO monstro avança e desfere um ataque selvagem!\n\n";
        if(!inimigo->estaDefendendo){
            int dano = 10 + forca - inimigo->defesa;
            if(dano < 0) {
                dano = 0;
            }
            inimigo->pontosVida -= dano;
            std::cout << inimigo->nome << " sofreu " << dano << " de dano!\n";
        } else {
            std::cout << inimigo->nome << " bloqueou o ataque!\n";
        }
    }
};

class Batalha {
public:
    void iniciar(Personagem* jogador, Personagem* inimigo) {
        std::cout << "\n=== BATALHA INICIADA ===\n";
        std::cout << jogador->nome << " VS " << inimigo->nome << "\n\n";

        while(jogador->pontosVida > 0 && inimigo->pontosVida > 0) {

            int opc;
            std::cout << "Vida jogador: " << jogador->pontosVida << "\n";
            std::cout << "Vida inimigo: " << inimigo->pontosVida << "\n";

            jogador->estaDefendendo = false;

            std::cout << "\n--- Seu turno ---\n";
            std::cout << "1 - Ataque simples\n";
            std::cout << "2 - Ataque especial\n";
            std::cout << "3 - Defender\n";
            std::cout << "4 - Fugir\n";
            std::cout << "Opc: ";
            std::cin >> opc;

            switch(opc){
                case 1:
                    jogador->atacar(inimigo);
                    break;

                case 2:
                    jogador->ataqueEspecial(inimigo);
                    break;

                case 3:
                    jogador->defender();
                    break;

                case 4:
                    std::cout << "\nVocê fugiu da batalha!\n";
                    return;

                default:
                    std::cout << "\nOpção inválida.\n";
            }

            if(inimigo->pontosVida <= 0){
                std::cout << "\n" << inimigo->nome << " foi derrotado!\n";
                break;
            }

            std::cout << "\n--- Turno inimigo ---\n";
            inimigo->estaDefendendo = false;
            inimigo->atacar(jogador);

            if(jogador->pontosVida <= 0){
                std::cout << "\nVocê foi derrotado!\n";
                break;
            }
        }

        std::cout << "\n=== FIM DA BATALHA ===\n\n";
    }
};

int main(){
    //vida
    //guerreiro 20
    //mago 10
    //arqueiro 15

   std::vector<std::string> habilidades;

    Personagem* p1 = new Mago(0, "Brenun", 50, 10, 5, {"fogo", "gelo"});
    Personagem* inimigo = new Monstro("Slime", 20, 5, 5, {"gosma"});

    Batalha batalha;
    batalha.iniciar(p1, inimigo);

    delete p1;
    delete inimigo;

    return 0;
}