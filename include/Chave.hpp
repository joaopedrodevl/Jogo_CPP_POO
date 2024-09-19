#ifndef CHAVE_HPP
#define CHAVE_HPP

#include "Item.hpp"
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Chave : public Item
{
private:
public:
    Chave(const ObjetoDeJogo &obj, std::string tipo) : Item(obj, tipo) {};
    ~Chave();

    void usar() {
        setUsado(true);
    };

    bool foiUsado() {
        return getUsado();
    };
};

#endif