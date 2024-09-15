#ifndef ITEM_HPP
#define ITEM_HPP

#include "./Heroi.hpp"
#include <string>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Item : public ObjetoDeJogo
{
private:
    std::string nome;
    std::string tipo;
    bool usado;
    bool eConsumivel;

public:
    Item(const ObjetoDeJogo &obj, std::string nome, std::string tipo) : ObjetoDeJogo(obj), nome(nome), tipo(tipo), usado(false) {};
    virtual ~Item();

    bool operator==(const Item &other) const
    {
        return (nome == other.nome) && (tipo == other.tipo) && (usado == other.usado) && (eConsumivel == other.eConsumivel);
    }
};

#endif // ITEM_HPP