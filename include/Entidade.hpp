#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include <string>

class Entidade : public ObjetoDeJogo
{
protected:
    std::string nome;
    int forca;
    int defesa;
    int vida;
public:
    Entidade(const ObjetoDeJogo &obj, const std::string &nome, int forca, int defesa, int vida) : ObjetoDeJogo(obj), nome(nome), forca(forca), defesa(defesa), vida(vida) {};
    virtual ~Entidade();

    virtual int atacar() = 0;
    virtual int defender() = 0;
};

#endif