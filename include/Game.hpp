#ifndef GAME_HPP
#define GAME_HPP

#include "../ASCII_Engine/SpriteBuffer.hpp"
#include "Fase1.hpp"
#include "Fase2.hpp"
#include "Heroi.hpp"

class Game
{
private:
    /* data */
public:
    Game(/* args */);
    ~Game();

    static void run()
    {
        try
        {
            SpriteBuffer buffer(150, 47);

            Heroi *heroi = new Heroi(ObjetoDeJogo("Heroi", SpriteAnimado("./sprites/heroi.txt", 3), 42, 33), 250, 40, 45, new Inventario());

            Fase1 fase1("Fase1", Sprite("./sprites/paredes/fase1/fase.txt"), "facil", heroi);
            Fase2 fase2("Fase2", Sprite("./sprites/paredes/fase2/fase.txt"), "medio", heroi);

            fase1.init();
            int ret = fase1.run(buffer);
            if (ret == Fase::END_GAME)
            {
                std::cout << "Parabéns, você venceu a fase 1!" << std::endl;

                buffer.clear();

                fase2.init();
                int ret2 = fase2.run(buffer);
                if (ret2 == Fase::END_GAME)
                {
                    std::cout << "Parabéns, você venceu o jogo!" << std::endl;
                    exit(0);
                }
            }
            else
            {
                std::cout << "Game Over..." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Game Over: " << e.what() << std::endl;
        }
    }
};

#endif