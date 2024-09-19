#include "../include/Fase2.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../ASCII_Engine/Sprite.hpp"

void Fase2::init()
{
    heroi->setVidaMaxima(350);
    heroi->moveTo(42, 33);
    heroi->setVida(350);
    heroi->setAtaque(40);
    heroi->setDefesa(80);

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite("III"), 2, 9));
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

    reliquia = new Reliquia(ObjetoDeJogo("Relíquia Floresta", Sprite("./sprites/reliquia.txt"), 14, 117), "Relíquia floresta", 0);
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
        std::cout << "Posicao: " << posL << " " << posC << std::endl;

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
            if (heroi->getPosC() < screen.getLargura(0) - (heroi->getSprite()->getLargura(0) + 6))
                heroi->moveRight(1);
            break;
        case 'q':
            running = false;
            return Fase2::END_GAME;
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
                return Fase2::END_GAME;
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
                    vida->setText(std::to_string(heroi->getVida()));
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
                    return Fase2::GAME_OVER;
                }

                vida->setText(std::to_string(heroi->getVida()));
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