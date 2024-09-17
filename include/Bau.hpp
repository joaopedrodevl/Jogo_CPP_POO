#ifndef BAU_HPP
#define BAU_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Chave.hpp"

class Bau : public ObjetoDeJogo
{
private:
    bool aberto;
public:
    Bau(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj), aberto(false) {};

    void abrir(Chave *chave) {
        chave->usar();
        aberto = true;
    };

    bool foiAberto() {
        return aberto;
    };
};

#endif // BAU_HPP