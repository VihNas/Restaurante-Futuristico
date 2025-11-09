#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <string>
#include "chef.hpp"
#include "mesa.hpp"

class Restaurante {
    std::vector<std::shared_ptr<Chef>> chefes;
    std::unordered_map<int, std::shared_ptr<Mesa>> mesasAtivas;
    std::unordered_map<int, std::shared_ptr<Chef>> mesaParaChefe;
    std::queue<std::pair<int, std::string>> filaEspera;

public:
    Restaurante(int nChefes);
    void processarPedido(int mesa, const std::string &pedido);
    void liberarChefe(int mesa);
    void finalizar();
};
