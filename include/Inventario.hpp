#ifndef INVENTARIO_CPP
#define INVENTARIO_CPP

#include "../include/Item.hpp"

#include <list>

class Inventario
{
private:
    std::list<Item*> inventario;

    int maxItens = 6;
public:
    Inventario(std::list<Item*> inventario = std::list<Item*>(), int maxItens = 6) : inventario(inventario), maxItens(maxItens) {};

    void abrirInventario() {
        for (auto &item : inventario) {
            std::cout << item->getName() << std::endl;
        }
    };

    bool addItem(Item *item) {
        if (inventario.size() < maxItens) {
            inventario.push_back(item);
            return true;
        }
        return false;
    };

    void removeItem(Item *item) {
        inventario.remove(item);
    };

    std::list<Item*> getInventario() {
        return inventario;
    };

    int getMaxItens() {
        return maxItens;
    };

    // toString() method: Retorna uma string no formato [item1, item2, item3, ...]
    std::string toString() {
        std::string str = "[";
        for (auto &item : inventario) {
            str += item != inventario.back() ? item->getName() + ", " : item->getName();
        }
        str += "]";
        return str;
    };

    bool itemExiste(Item &item) {
        for (auto &i : inventario) {
            if (i == &item) {
                return true;
            }
        }
        return false;
    };

    ~Inventario();
};

#endif