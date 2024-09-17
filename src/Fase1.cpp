#include "../include/Fase1.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../ASCII_Engine/Sprite.hpp"

void Fase1::init()
{
    reliquia = new Reliquia(ObjetoDeJogo("Reliquia", Sprite("./sprites/reliquia.txt"), 10, 80), "reliquia", 0);
    objs.push_back(reliquia);
    reliquia->desativarObj();
    
    cura = new Cura(ObjetoDeJogo("Cura", Sprite("./sprites/cura.txt"), 42, 70), "cura", 100);
    objs.push_back(cura);

    bau = new Bau(ObjetoDeJogo("Bau", Sprite("./sprites/bau.txt"), 10, 120));
    objs.push_back(bau);

    inventario = new Inventario();
    objs.push_back(new ObjetoDeJogo("Inventario", TextSprite("[]"), 2, 27));
    SpriteBase *tmp2 = const_cast<SpriteBase *>(objs.back()->getSprite());
    inv = dynamic_cast<TextSprite *>(tmp2);

    objs.push_back(new ObjetoDeJogo("Mensagem", TextSprite("Aperte 'w, a, s, d' para movimentar"), 2, 110));
    SpriteBase *tmp3 = const_cast<SpriteBase *>(objs.back()->getSprite());
    msg = dynamic_cast<TextSprite *>(tmp3);

    chave = new Chave(ObjetoDeJogo("Chave", Sprite("./sprites/chave.txt"), 42, 120), "chave");
    objs.push_back(chave);
    chave->desativarObj();

    inimigos[0] = new Inimigo(ObjetoDeJogo("Inimigo1", Sprite("./sprites/vilao.txt"), 15, 10), "Inimigo1", "comum", 10, 10, 10, false);
    objs.push_back(inimigos[0]);

    inimigos[1] = new Inimigo(ObjetoDeJogo("Inimigo2", Sprite("./sprites/vilao.txt"), 30, 50), "Inimigo1", "comum", 10, 10, 10, false);
    objs.push_back(inimigos[1]);

    inimigos[2] = new Inimigo(ObjetoDeJogo("boss", SpriteAnimado("./sprites/boss-adormecido.anm", 3), 10, 80), "boss", "boss", 50, 20, 20, true);
    objs.push_back(inimigos[2]);

    inimigos[3] = new Inimigo(ObjetoDeJogo("boss", SpriteAnimado("./sprites/boss.anm", 3), 10, 80), "boss", "boss", 100, 20, 20, true);
    objs.push_back(inimigos[3]);
    inimigos[3]->desativarObj();

    heroi = new Heroi(ObjetoDeJogo("Heroi", SpriteAnimado("./sprites/heroi.txt", 3), 42, 33), 250, 40, 45, inventario);
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
        update();
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
            for (int i = 0; i < Fase1::getMAX_INIMIGOS(); i++)
            {
                inimigos[i]->acordar();
                if (heroi->colideCom(*inimigos[i]))
                {
                    inimigos[i]->foiAtacado(heroi->atacar());

                    if (!inimigos[i]->estaVivo())
                    {
                        inimigos[i]->desativarObj();
                    }
                }
            }

            // Coleta a chave
            if (heroi->colideCom(*chave))
            {
                heroi->getInventario()->addItem(chave);
                chave->desativarObj();
                chave->setColetado(true);
            }

            // Coleta a cura
            if (heroi->colideCom(*cura))
            {
                heroi->getInventario()->addItem(cura);
                cura->desativarObj();
            }

            // Abre o bau
            if (heroi->colideCom(*bau) && chave->getColetado() && !bau->foiAberto() && reliquia->getColetado())
            {
                bau->abrir(chave);
                msg->setText("O bau foi aberto! Fim da Fase 1!");
                heroi->getInventario()->removeItem(chave);
                heroi->getInventario()->removeItem(reliquia);
            }

            // Coleta a reliquia
            if (heroi->colideCom(*reliquia))
            {
                heroi->getInventario()->addItem(reliquia);
                reliquia->desativarObj();
            }

            break;

        case 'c':
            // Verifica se o heroi tem a cura
            if (!inventario->itemExiste(*cura))
            {
                msg->setText("Voce nao tem a cura!");
                break;
            }

            // Usa a cura
            heroi->usarItem(*cura);
            inventario->removeItem(cura);
            inv->setText(heroi->getInventario()->toString());
            vida->setText(std::to_string(heroi->getVida()));
            break;

        default:
            break;
        }

        if (colideComBloco())
            heroi->moveTo(posL, posC);

        // Mostra os itens coletados
        inv->setText(heroi->getInventario()->toString());

        // acorda o boss ao passar por uma porta na posição 30, 55
        if (heroi->getPosL() == 27 && heroi->getPosC() >= 58 && heroi->getPosC() <= 71 && inimigos[3]->estaVivo())
        {
            msg->setText("O boss acordou! Cuidado!");
            inimigos[2]->desativarObj();
            inimigos[3]->acordar();
            inimigos[3]->ativarObj();
        }

        for (int i = 0; i < Fase1::getMAX_INIMIGOS(); i++)
            if (heroi->colideCom(*inimigos[i]) && !inimigos[i]->estaAdormecido())
            {
                msg->setText("Aperte 'e' para matar o inimigo");
                heroi->foiAtacado(inimigos[i]->atacar());

                if (!heroi->estaVivo())
                    return Fase1::END_GAME;

                vida->setText(std::to_string(heroi->getVida()));
            }

        // Verifica se o boss foi derrotado
        if (!inimigos[3]->estaVivo() && !chave->getColetado() && !reliquia->getColetado())
        {
            // Ativa a chave
            chave->ativarObj();
            msg->setText("A chave apareceu! Colete-a!");

            // Ativa a reliquia
            reliquia->ativarObj();
            reliquia->setColetado(true);
            msg->setText("A reliquia apareceu! Colete-a!");
        }

        if (heroi->colideCom(*reliquia) && !reliquia->getColetado())
        {
            msg->setText("Reliquia coletada! Encontre a chave!");
        }

        if (heroi->colideCom(*chave) && !chave->getColetado())
        {
            msg->setText("Chave coletada! Encontre o bau!");
        }

        if (heroi->colideCom(*bau) && !chave->getColetado())
        {
            msg->setText("Bau trancado! Encontre a chave!");
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
        if (heroi->colideComBordas(**it))
            return true;

    return false;
}

Fase1::~Fase1() {}