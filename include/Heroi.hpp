#ifndef HEROI_HPP
#define HEROI_HPP

#include <list>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "../include/Item.hpp"
#include "../include/Inventario.hpp"
#include "../include/Entidade.hpp"

class Heroi : public Entidade
{
private:
    int vida;
    int ataque;
    int defesa;
    int vidaMaxima = 250;

    Inventario *inventario;
public:
    Heroi(const ObjetoDeJogo &obj, int vida = 250, int ataque = 40, int defesa = 45, Inventario *inventario = new Inventario()) : Entidade(obj, obj.getName(), ataque, defesa, vida), vida(vida), ataque(ataque), defesa(defesa), inventario(inventario) {};
    virtual ~Heroi();

    int atacar()
    {
        return ataque;
    };
    int defender()
    {
        return defesa;
    };

    void foiAtacado(int dano)
    {
        this->vida = (vida - dano > 0) ? (vida - dano + (defesa / 50)) : 0;
    };

    int getVida()
    {
        return vida;
    };

    int getAtaque()
    {
        return ataque;
    };

    int getDefesa()
    {
        return defesa;
    };

    void usarItem(Item &item) {
        if (item.getTipo() == "cura") {
            vida = (vida + item.getValor() <= vidaMaxima) ? vida + item.getValor() : vidaMaxima;
        }
    }

    bool estaVivo()
    {
        return vida > 0;
    };

    void setVida(int vida)
    {
        this->vida = vida;
    };

    void setAtaque(int ataque)
    {
        this->ataque = this->ataque + ataque;
    };

    void setDefesa(int defesa)
    {
        this->defesa = this->defesa + defesa;
    };

    Inventario *getInventario()
    {
        return inventario;
    };

    int getVidaMaxima() {
        return vidaMaxima;
    }

    void setVidaMaxima(int vidaMaxima) {
        this->vidaMaxima = vidaMaxima;
    }
};

#endif