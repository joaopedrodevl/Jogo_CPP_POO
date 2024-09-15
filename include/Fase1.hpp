#ifndef FASE1_HPP
#define FASE1_HPP

#include "../ASCII_Engine/Fase.hpp"
#include <string>
#include <list>

#include "Heroi.hpp"

class Fase1 : public Fase
{
private:
    std::string dificuldade;

    TextSprite *vida;

    Heroi *heroi;

    std::list<ObjetoDeJogo*> colisoes;
public:
    Fase1(std::string name, const Sprite &bkg) : Fase(name, bkg) {}
    Fase1(std::string name, const SpriteAnimado &bkg) : Fase(name, bkg) {}
    virtual ~Fase1();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool colideComBloco() const;
};


#endif
