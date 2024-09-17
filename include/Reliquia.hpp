#ifndef RELIQUIA_HPP
#define RELIQUIA_HPP

#include "Item.hpp"
#include "Heroi.hpp"

class Reliquia : public Item
{
private:
    bool coletado = false;
public:
    Reliquia(ObjetoDeJogo obj, std::string nome, int valor = 0) : Item(obj, nome, valor) {}

    bool getColetado() {
         return coletado;
    }

    void setColetado(bool coletado) {
        this->coletado = coletado;
    }
};

#endif // RELIQUIA_HPP