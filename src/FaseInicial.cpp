#include "../include/FaseInicial.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

void FaseInicial::init()
{
}

unsigned FaseInicial::run(SpriteBuffer &screen)
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

        switch (ch)
        {
        case 'e':
            return Fase::LEVEL_COMPLETE;
        case 'q':
            running = false;
            return Fase::END_GAME;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return Fase::END_GAME;
}