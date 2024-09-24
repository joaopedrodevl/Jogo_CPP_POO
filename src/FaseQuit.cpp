#include "../include/FaseQuit.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "../ASCII_Engine/Sprite.hpp"

void FaseQuit::init()
{
}

unsigned FaseQuit::run(SpriteBuffer &screen)
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
        case 'q':
            running = false;
            return Fase::END_GAME;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return Fase::END_GAME;
}