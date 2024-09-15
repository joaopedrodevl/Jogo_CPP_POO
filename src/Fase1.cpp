#include "../include/Fase1.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../include/Heroi.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../include/Inimigo.hpp"

void Fase1::init()
{
    inimigos[0] = new Inimigo(ObjetoDeJogo("Inimigo1", Sprite("./sprites/vilao.txt"), 10, 10), "Inimigo1", "comum", 10, 10, 10, false);
    objs.push_back(inimigos[0]);

    heroi = new Heroi(ObjetoDeJogo("Heroi", Sprite("./sprites/heroi.txt"), 42, 33));
    objs.push_back(heroi);

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite("IIIII"), 2, 9));
    SpriteBase *tmp = const_cast<SpriteBase *>(objs.back()->getSprite());
    vida = dynamic_cast<TextSprite *>(tmp);

    objs.push_back(new ObjetoDeJogo("P5", Sprite("./sprites/paredes/fase1/p5.txt"), 46, 0));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P6", Sprite("./sprites/paredes/fase1/p6.txt"), 46, 40));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P7", Sprite("./sprites/paredes/fase1/p7.txt"), 5, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P8", Sprite("./sprites/paredes/fase1/p8.txt"), 22, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P9", Sprite("./sprites/paredes/fase1/p9.txt"), 38, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P10", Sprite("./sprites/paredes/fase1/p10.txt"), 38, 104));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P11", Sprite("./sprites/paredes/fase1/p11.txt"), 39, 65));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P12", Sprite("./sprites/paredes/fase1/p11.txt"), 39, 105));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P12G", Sprite("./sprites/paredes/fase1/p12.txt"), 5, 58));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P13", Sprite("./sprites/paredes/fase1/p13.txt"), 29, 72));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P14", Sprite("./sprites/paredes/fase1/p14.txt"), 30, 73));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P15", Sprite("./sprites/paredes/fase1/p15.txt"), 5, 111));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P16", Sprite("./sprites/paredes/fase1/p16.txt"), 22, 127));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P17", Sprite("./sprites/paredes/fase1/p17.txt"), 34, 111));
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
            if (heroi->getPosL() > 5)
                heroi->moveUp(1);
            break;
        case 'a':
            if (heroi->getPosC() > 2)
                heroi->moveLeft(1);
            break;
        case 's':
            if (heroi->getPosL() < screen.getAltura() - 4)
                heroi->moveDown(1);
            break;
        case 'd':
            if (heroi->getPosC() < screen.getLargura(0) - (heroi->getSprite()->getLargura(0) + 8))
                heroi->moveRight(1);
            break;
        case 'q':
            running = false;
            return Fase1::END_GAME;
            break;
        case 'e':
            for (int i = 0; i < 1; i++){
                inimigos[i]->acordar();
                if (heroi->colideCom(*inimigos[i])){
                    inimigos[i]->foiAtacado(heroi->atacar());

                    if (!inimigos[i]->estaVivo()){
                        inimigos[i]->desativarObj();
                    }
                }
            }
        default:
            break;
        }

        if (colideComBloco())
            heroi->moveTo(posL, posC);
        
        for (int i = 0; i < 1; i++)
            if (heroi->colideCom(*inimigos[i])){
                heroi->foiAtacado(inimigos[i]->atacar());
                
                if (!heroi->estaVivo())
                    return Fase1::END_GAME;
                
                vida->setText(std::to_string(heroi->getVida()));
            }

        update();
        draw(screen);
        system("clear");
        show(screen);
    }
}

bool Fase1::colideComBloco() const
{
    for (auto it = colisoes.begin(); it != colisoes.end(); ++it)
        if (heroi->colideCom(**it))
            return true;

    return false;
}

Fase1::~Fase1() {}