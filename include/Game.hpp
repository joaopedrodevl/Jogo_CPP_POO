#ifndef GAME_HPP
#define GAME_HPP

#include "../ASCII_Engine/SpriteBuffer.hpp"
#include "Fase1.hpp"

class Game
{
private:
    /* data */
public:
    Game(/* args */);
    ~Game();

    static void run() {
        SpriteBuffer buffer(150, 47);

        std::cout << "AAA" << std::endl;
        Fase1 fase1("Fase1", Sprite("./sprites/paredes/fase1/fase.txt"), "facil");
        std::cout << "BBB" << std::endl;

        fase1.init();
        int ret1 = fase1.run(buffer);
        if (ret1 != Fase::GAME_OVER && ret1 != Fase::END_GAME){
            buffer.clear();
        } else {
            if (ret1 == Fase::GAME_OVER)
                std::cout << "GAME OVER" << std::endl;
        }

        std::cout << "Saindo..." << std::endl;
    }
};

#endif