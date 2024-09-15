#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

#include "../include/Entidade.hpp"

#include <string>

class Inimigo : public Entidade
{
private:
    std::string tipo;
    bool adormecido;
public:
    Inimigo(const ObjetoDeJogo &obj, const std::string nome, const std::string &tipo, int vida = 10, int ataque = 30, int defesa = 10, bool adormecido = true) : Entidade(obj, nome, ataque, defesa, vida), tipo(tipo), adormecido(adormecido) {};
    virtual ~Inimigo();

    bool estaAdormecido() {
        return adormecido;
    };

    void acordar() {
        adormecido = false;
    };

    void dormir() {
        adormecido = true;
    };

    int atacar() {
        if (adormecido) return 0;

        if (!estaVivo()) return 0;

        if (tipo == "boss") return Entidade::forca * 2;

        if (tipo == "comum") return Entidade::forca / 2;

        return Entidade::forca;
    };

    int defender() {
        if (adormecido) return 0;

        if (!estaVivo()) return 0;

        if (tipo == "boss") return Entidade::defesa * 2;

        if (tipo == "comum") return Entidade::defesa / 2;

        return Entidade::defesa;
    };

    void foiAtacado(int dano) {
        this->vida = (vida - this->atacar() + this->defender() >= 0) ? (vida - this->atacar() + (this->defender() / 10)) : 0;
        std::cout << this->vida;
    }

    bool estaVivo() {
        return this->vida > 0;
    };
};


#endif