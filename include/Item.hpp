#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Item : public ObjetoDeJogo
{
protected:
    int valor;
    std::string tipo;
    bool usado;
    bool eConsumivel;
    bool coletado = false;
public:
    Item(const ObjetoDeJogo &obj, std::string tipo, int valor = 0) : ObjetoDeJogo(obj), tipo(tipo), valor(valor), usado(false), eConsumivel(false) {};
    virtual ~Item();

    std::string getTipo() {
        return tipo;
    };

    bool getUsado() {
        return usado;
    };

    void setUsado(bool usado) {
        this->usado = usado;
    };

    bool getEConsumivel() {
        return eConsumivel;
    };

    void setEConsumivel(bool eConsumivel) {
        this->eConsumivel = eConsumivel;
    };

    int getValor() {
        return valor;
    };

    void setColetado(bool coletado) {
        this->coletado = coletado;
    };

    bool getColetado() {
        return coletado;
    };
};

#endif // ITEM_HPP