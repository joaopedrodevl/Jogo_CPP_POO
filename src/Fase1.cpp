#include "../include/Fase1.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../include/Heroi.hpp"
#include "../ASCII_Engine/Sprite.hpp";

void Fase1::init()
{
    heroi = new Heroi(ObjetoDeJogo("Heroi", Sprite("./sprites/heroi.txt"), 42, 35));
    objs.push_back(heroi);

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite("IIIII"), 2, 9));
    SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
    vida = dynamic_cast<TextSprite*> (tmp);

    objs.push_back(new ObjetoDeJogo("P13", Sprite("./sprites/paredes/fase1/p13.txt"), 29, 72));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P14", Sprite("./sprites/paredes/fase1/p14.txt"), 30, 73));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P15", Sprite("./sprites/paredes/fase1/p15.txt"), 5, 111));
    colisoes.push_back(objs.back());
}

unsigned Fase1::run(SpriteBuffer &screen)
{
    draw(screen);
    system("clear");
    show(screen);

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    bool running = true;

    while (running)
    {
        ch = getchar();
        int posL = heroi->getPosL(), posC = heroi->getPosC();

        switch (ch)
        {
            case 'w':
                if (heroi->getPosL() > 5) heroi->moveUp(1);
                break;
            case 'a':
                if (heroi->getPosC() > 2) heroi->moveLeft(1);
                break;
            case 's':
                if (heroi->getPosL() < screen.getAltura() - 4) heroi->moveDown(1);
                break;
            case 'd':
                if (heroi->getPosC() < screen.getLargura(0) - (heroi->getSprite()->getLargura(0) + 8)) heroi->moveRight(1);
                break;
            case 'q':
                running = false;
                return Fase1::END_GAME;
                break;
            default:
                break;
        }   

        if (colideComBloco())
            heroi->moveTo(posL, posC);

        update();
        draw(screen);
        system("clear");
        show(screen);
    }
}

bool Fase1::colideComBloco() const
{
    for (auto it = colisoes.begin(); it != colisoes.end(); ++it)
        if (heroi->colideCom(**it)) return true;
    
    return false;
}

Fase1::~Fase1() {}