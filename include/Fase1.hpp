#ifndef FASE1_HPP
#define FASE1_HPP

#include "../ASCII_Engine/Fase.hpp"
#include <string>
#include <list>

#include "Heroi.hpp"
#include "Inimigo.hpp"
#include "Item.hpp"
#include "Inventario.hpp"
#include "Chave.hpp"
#include "Bau.hpp"
#include "Cura.hpp"
#include "Reliquia.hpp"

class Fase1 : public Fase
{
private:
    std::string dificuldade;

    TextSprite *vida;

    Reliquia *reliquia;

    Bau *bau;

    Heroi *heroi;
    int MAX_INIMIGOS = 4;
    Inimigo *inimigos[4];

    Inventario *inventario;
    TextSprite *inv;
    Chave *chave;
    Cura *cura;

    TextSprite *msg;

    std::list<ObjetoDeJogo*> colisoes;
public:
    Fase1(std::string name, const Sprite &bkg, std::string dificuldade) : Fase(name, bkg) {}
    Fase1(std::string name, const SpriteAnimado &bkg, std::string dificuldade) : Fase(name, bkg) {}
    virtual ~Fase1();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool colideComBloco() const;

    int getMAX_INIMIGOS() const {
        return MAX_INIMIGOS;
    }
};


#endif
