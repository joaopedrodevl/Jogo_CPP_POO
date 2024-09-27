#ifndef GAME_HPP
#define GAME_HPP

#include "../ASCII_Engine/SpriteBuffer.hpp"
#include "Fase1.hpp"
#include "Fase2.hpp"
#include "Heroi.hpp"
#include "FaseQuit.hpp"
#include "FaseInicial.hpp"

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

            FaseInicial faseInicial("FaseInicial", Sprite("./sprites/paredes/faseinicial/faseinicial.txt"));
            Fase1 fase1("Fase1", Sprite("./sprites/paredes/fase1/fase.txt"), "facil", heroi);
            Fase2 fase2("Fase2", Sprite("./sprites/paredes/fase2/fase.txt"), "medio", heroi);
            FaseQuit faseQuit("FaseQuit", Sprite("./sprites/paredes/fasequit/fasequit.txt"));

            faseInicial.init();
            int retn = faseInicial.run(buffer);
            if (retn != Fase::GAME_OVER && retn != Fase::END_GAME)
            {
                buffer.clear();
                fase1.init();
                int ret1 = fase1.run(buffer);
                if (ret1 != Fase::END_GAME && ret1 != Fase::GAME_OVER)
                {
                    buffer.clear();
                    fase2.init();
                    int ret2 = fase2.run(buffer);
                    if (ret2 != Fase::END_GAME && ret2 != Fase::GAME_OVER)
                    {
                        buffer.clear();
                        faseQuit.init();
                        int ret3 = faseQuit.run(buffer);
                        if (ret3 == Fase::END_GAME)
                        {
                            exit(0);
                        }
                    }
                }
            }
            else
            {
                std::cout << "Saindo..." << std::endl;
            }

            // fase1.init();
            // int ret = fase1.run(buffer);
            // if (ret == Fase::END_GAME)
            // {
            //     std::cout << "Parabéns, você venceu a fase 1!" << std::endl;

            //     buffer.clear();

            //     fase2.init();
            //     int ret2 = fase2.run(buffer);
            //     if (ret2 == Fase::END_GAME)
            //     {
            //         std::cout << "Parabéns, você venceu o jogo!" << std::endl;
            //         exit(0);
            //     }
            // }
            // else
            // {
            //     std::cout << "Game Over..." << std::endl;
            // }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Game Over: " << e.what() << std::endl;
        }
    }
};

#endif