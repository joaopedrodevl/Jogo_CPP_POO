#ifndef HEROI_HPP
#define HEROI_HPP

#include <list>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "../include/Item.hpp"

#include "../include/Entidade.hpp"

class Heroi : public Entidade
{
private:
    int vida;
    int ataque;
    int defesa;
public:
    Heroi(const ObjetoDeJogo &obj, int vida = 100, int ataque = 40, int defesa = 25) : Entidade(obj, obj.getName(), ataque, defesa, vida), vida(vida), ataque(ataque), defesa(defesa) {};
    virtual ~Heroi();

    int atacar() {
        return ataque;
    };
    int defender() {
        return defesa;
    };

    void foiAtacado(int dano) {
        this->vida = (vida - dano + defesa >= 0) ? (vida - dano + (defesa / 10)) : 0;
    };

    int getVida() {
        return vida;
    };

    int getAtaque() {
        return ataque;
    };

    int getDefesa() {
        return defesa;
    };

    // bool addItem(Item item) {
    //     if (inventario.size() < 10) {
    //         inventario.push_back(item);
    //         return true;
    //     }
    //     return false;
    // };

    // void removeItem(Item item) {
    //     inventario.remove(item);
    // };

    bool estaVivo() {
        return vida > 0;
    };

    void setVida(int vida) {
        this->vida = this->vida + vida;
    };

    void setAtaque(int ataque) {
        this->ataque = this->ataque + ataque;
    };

    void setDefesa(int defesa) {
        this->defesa = this->defesa + defesa;
    };
    
};

#endif