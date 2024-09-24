#ifndef FASEQUIT_HPP
#define FASEQUIT_HPP

#include "../ASCII_Engine/Fase.hpp"

class FaseQuit : public Fase
{
private:
public:
    FaseQuit(std::string name, const Sprite &bkg) : Fase(name, bkg) {};

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
};

#endif