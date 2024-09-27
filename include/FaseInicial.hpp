#ifndef FASEINICIAL_HPP
#define FASEINICIAL_HPP

#include "../ASCII_Engine/Fase.hpp"
#include <string>

class FaseInicial : public Fase
{
private:
public:
    FaseInicial(std::string name, const Sprite &bkg) : Fase(name, bkg) {};

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
};

#endif