#include "../include/Fase2.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../ASCII_Engine/Sprite.hpp"

void Fase2::init()
{
    heroi->setVidaMaxima(750);
    heroi->moveTo(42, 33);
    heroi->setVida(750);
    heroi->setAtaque(40);
    heroi->setDefesa(80);

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite(heroi->vidaEmIs(heroi->getVida(), heroi->getVidaMaxima())), 2, 9));
    SpriteBase *tmp = const_cast<SpriteBase *>(objs.back()->getSprite());
    vida = dynamic_cast<TextSprite *>(tmp);

    bau = new Bau(ObjetoDeJogo("Bau", Sprite("./sprites/bau.txt"), 17, 135));
    objs.push_back(bau);

    chave = new Chave(ObjetoDeJogo("Chave", Sprite("./sprites/chave.txt"), 17, 25), "chave");
    objs.push_back(chave);
    chave->desativarObj();

    objs.push_back(new ObjetoDeJogo("Mensagem", TextSprite("Aperte 'w, a, s, d' para movimentar"), 2, 110));
    SpriteBase *tmp3 = const_cast<SpriteBase *>(objs.back()->getSprite());
    msg = dynamic_cast<TextSprite *>(tmp3);

    objs.push_back(new ObjetoDeJogo("Inventario", TextSprite("[]"), 2, 27));
    SpriteBase *tmp2 = const_cast<SpriteBase *>(objs.back()->getSprite());
    inv = dynamic_cast<TextSprite *>(tmp2);

    reliquia = new Reliquia(ObjetoDeJogo("Reliquia Floresta", Sprite("./sprites/reliquia.txt"), 14, 117), "Reliquia floresta", 0);
    objs.push_back(reliquia);
    reliquia->desativarObj();

    cura[0] = new Cura(ObjetoDeJogo("Cura", Sprite("./sprites/cura.txt"), 41, 134), "cura", 80);
    objs.push_back(cura[0]);

    cura[1] = new Cura(ObjetoDeJogo("Cura", Sprite("./sprites/cura.txt"), 6, 69), "cura", 150);
    objs.push_back(cura[1]);

    inimigos[0] = new Inimigo(ObjetoDeJogo("Inimigo1", Sprite("./sprites/vilaof2.txt"), 37, 77), "Inimigo1", "comum", 80, 10, 10, false);
    objs.push_back(inimigos[0]);

    inimigos[1] = new Inimigo(ObjetoDeJogo("Inimigo2", Sprite("./sprites/vilaof2.txt"), 29, 35), "Inimigo2", "comum", 25, 15, 10, false);
    objs.push_back(inimigos[1]);

    inimigos[2] = new Inimigo(ObjetoDeJogo("Inimigo3", Sprite("./sprites/vilaof2.txt"), 9, 9), "Inimigo3", "comum", 30, 12, 40, false);
    objs.push_back(inimigos[2]);

    inimigos[3] = new Inimigo(ObjetoDeJogo("Inimigo4", Sprite("./sprites/vilaof2.txt"), 14, 47), "Inimigo4", "comum", 100, 5, 60, false);
    objs.push_back(inimigos[3]);

    inimigos[4] = new Inimigo(ObjetoDeJogo("Inimigo5", Sprite("./sprites/vilaof2.txt"), 21, 75), "Inimigo5", "comum", 100, 5, 60, false);
    objs.push_back(inimigos[4]);

    inimigos[5] = new Inimigo(ObjetoDeJogo("Inimigo6", Sprite("./sprites/vilaof2.txt"), 10, 95), "Inimigo6", "comum", 100, 5, 60, false);
    objs.push_back(inimigos[5]);

    inimigos[6] = new Inimigo(ObjetoDeJogo("boss", SpriteAnimado("./sprites/bossf2-adormecido.anm", 3), 26, 126), "boss", "boss", 0, 0, 0, true);
    objs.push_back(inimigos[6]);

    inimigos[7] = new Inimigo(ObjetoDeJogo("boss", SpriteAnimado("./sprites/bossf2.anm", 3), 26, 126), "boss", "boss", 200, 50, 80, false);
    objs.push_back(inimigos[7]);
    inimigos[7]->desativarObj();

    objs.push_back(heroi);

    objs.push_back(new ObjetoDeJogo("P1", Sprite("./sprites/paredes/fase2/p1.txt"), 38, 2));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P2", Sprite("./sprites/paredes/fase2/p2.txt"), 38, 90));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P3", Sprite("./sprites/paredes/fase2/p3.txt"), 38, 133));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P4", Sprite("./sprites/paredes/fase2/p4.txt"), 39, 65));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P4C", Sprite("./sprites/paredes/fase2/p4.txt"), 45, 65));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P4A", Sprite("./sprites/paredes/fase2/p4.txt"), 45, 105));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P4B", Sprite("./sprites/paredes/fase2/p4.txt"), 39, 105));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P6", Sprite("./sprites/paredes/fase2/p6.txt"), 34, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P7", Sprite("./sprites/paredes/fase2/p7.txt"), 30, 72));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P8", Sprite("./sprites/paredes/fase2/p8.txt"), 12, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P10", Sprite("./sprites/paredes/fase2/p10.txt"), 23, 23));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P11", Sprite("./sprites/paredes/fase2/p11.txt"), 23, 44));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P12", Sprite("./sprites/paredes/fase2/p12.txt"), 18, 58));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P13", Sprite("./sprites/paredes/fase2/p13.txt"), 29, 72));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P15", Sprite("./sprites/paredes/fase2/p15.txt"), 9, 111));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P16", Sprite("./sprites/paredes/fase2/p16.txt"), 9, 127));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P17", Sprite("./sprites/paredes/fase2/p17.txt"), 22, 127));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P18", Sprite("./sprites/paredes/fase2/p18.txt"), 5, 21));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P19", Sprite("./sprites/paredes/fase2/p19.txt"), 5, 58));
    colisoes.push_back(objs.back());

    objs.push_back(new ObjetoDeJogo("P20", Sprite("./sprites/paredes/fase2/p20.txt"), 5, 86));
    colisoes.push_back(objs.back());
    
}

unsigned Fase2::run(SpriteBuffer &screen)
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
            if (heroi->getPosL() < screen.getAltura() - 5)
                heroi->moveDown(1);
            break;
        case 'd':
            if (heroi->getPosC() < screen.getLargura(0) - (heroi->getSprite()->getLargura(0) + 6))
                heroi->moveRight(1);
            break;
        case 'q':
            running = false;
            return Fase::LEVEL_COMPLETE;
            break;
        case 'e':
            // Verifica se o heroi colide com inimigos
            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                if (heroi->colideCom(*inimigos[i]) && !inimigos[i]->estaAdormecido())
                {
                    inimigos[i]->foiAtacado(heroi->atacar());

                    if (!inimigos[i]->estaVivo())
                    {
                        inimigos[i]->desativarObj();
                    }
                }
            }

            if (heroi->colideCom(*reliquia) && reliquia->getColetado() && !chave->getColetado())
            {
                msg->setText("Reliquia coletada! Encontre a chave!");
            }
            else if (heroi->colideCom(*chave) && chave->getColetado() && !reliquia->getColetado())
            {
                msg->setText("Chave coletada! Encontre a reliquia!");
            }

            // Coleta a chave
            if (heroi->colideCom(*chave))
            {
                heroi->getInventario()->addItem(chave);
                chave->desativarObj();
                chave->setColetado(true);
            }

            // Coleta a cura
            for (int i = 0; i < 2; i++)
            {
                if (heroi->colideCom(*cura[i]))
                {
                    heroi->getInventario()->addItem(cura[i]);
                    cura[i]->desativarObj();
                }
            }

            // Coleta a reliquia
            if (heroi->colideCom(*reliquia))
            {
                heroi->getInventario()->addItem(reliquia);
                reliquia->desativarObj();
                reliquia->setColetado(true);
            }

            // Abre o bau
            if (heroi->colideCom(*bau) && chave->getColetado() && !bau->foiAberto() && reliquia->getColetado())
            {
                bau->abrir(chave);
                msg->setText("O bau foi aberto! Fim!");
                heroi->getInventario()->removeItem(chave);
                update();
                draw(screen);
                system("clear");
                show(screen);
                return Fase::LEVEL_COMPLETE;
            }

            break;
        case 'c':
            // Verifica se o heroi tem a cura
            if (!heroi->getInventario()->itemExiste(*cura[0]) && !heroi->getInventario()->itemExiste(*cura[1]))
            {
                msg->setText("Voce nao tem a cura!");
                break;
            }

            // Usa uma cura
            for (int i = 0; i < 2; i++)
            {
                if (heroi->getInventario()->itemExiste(*cura[i]))
                {
                    heroi->usarItem(*cura[i]);
                    heroi->getInventario()->removeItem(cura[i]);
                    inv->setText(heroi->getInventario()->toString());
                    vida->setText(heroi->vidaEmIs(heroi->getVida(), heroi->getVidaMaxima()));
                    break;
                }
            }
        }

        if (colideComBloco())
            heroi->moveTo(posL, posC);

        // Mostra os itens coletados
        inv->setText(heroi->getInventario()->toString());

        // acorda o boss ao passar por uma porta na posição 37, da 120 a 130
        if (((heroi->getPosL() == 37 && heroi->getPosC() >= 120 && heroi->getPosC() <= 130) || (heroi->getPosL() == 7 && heroi->getPosC() >= 112 && heroi->getPosC() <= 120)) && inimigos[7]->estaVivo())
        {
            msg->setText("O boss acordou! Cuidado!");
            inimigos[6]->desativarObj();
            inimigos[7]->acordar();
            inimigos[7]->ativarObj();
        }

        // Verifica se o heroi colide com inimigos
        for (int i = 0; i < MAX_INIMIGOS; i++)
        {
            if (heroi->colideCom(*inimigos[i]) && !inimigos[i]->estaAdormecido())
            {
                msg->setText("Aperte 'e' para matar o inimigo");
                heroi->foiAtacado(inimigos[i]->atacar());
                if (!heroi->estaVivo())
                {
                    vida->setText("0");
                    msg->setText("Game Over!");
                    update();
                    draw(screen);
                    system("clear");
                    show(screen);
                    return Fase::LEVEL_COMPLETE;
                }

                vida->setText(heroi->vidaEmIs(heroi->getVida(), heroi->getVidaMaxima()));
            }
        }

        // Verifica se o boss foi derrotado
        if (!inimigos[7]->estaVivo() && !chave->getColetado() && !reliquia->getColetado())
        {
            msg->setText("Colete a chave e a reliquia!");
            chave->ativarObj();
            reliquia->ativarObj();
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

bool Fase2::colideComBloco() const
{
    for (auto it = colisoes.begin(); it != colisoes.end(); ++it)
        if (heroi->colideComBordas(**it))
            return true;

    return false;
}

Fase2::~Fase2()
{
}