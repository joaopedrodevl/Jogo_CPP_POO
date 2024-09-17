#ifndef CURA_HPP
#define CURA_HPP

#include "Item.hpp"
#include "Heroi.hpp"

class Cura : public Item
{
private:
    
public:
    Cura(const ObjetoDeJogo &obj, std::string tipo = "cura", int valor = 100) : Item(obj, tipo, valor) {};

};

#endif