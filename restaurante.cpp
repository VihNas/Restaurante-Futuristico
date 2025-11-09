#include "restaurante.hpp"
#include <iostream>
#include <fstream>

Restaurante::Restaurante(int nChefes) {
    for (int i = 0; i < nChefes; ++i)
        chefes.push_back(std::make_shared<Chef>(i + 1));
}

void Restaurante::processarPedido(int mesa, const std::string &pedido) {
    if (pedido == "fim") {
        liberarChefe(mesa);
        return;
    }

    if (!mesasAtivas.count(mesa))
        mesasAtivas[mesa] = std::make_shared<Mesa>(mesa);

    auto mesaAtual = mesasAtivas[mesa];
    mesaAtual->adicionarPedido(pedido);

    if (mesaParaChefe.count(mesa)) {
        mesaParaChefe[mesa]->prepararPedido(pedido);
        return;
    }

    for (auto &chef : chefes) {
        if (chef->estaLivre()) {
            chef->iniciarAtendimento(mesa);
            chef->prepararPedido(pedido);
            mesaParaChefe[mesa] = chef;
            return;
        }
    }

    // Nenhum chef disponível → fila de espera
    filaEspera.push({mesa, pedido});
    std::ofstream naoAtendidas("MesasNaoAtendidas.txt", std::ios::app);
    naoAtendidas << "Mesa " << mesa << " aguardando: " << pedido << std::endl;
}

void Restaurante::liberarChefe(int mesa) {
    if (mesaParaChefe.count(mesa)) {
        mesaParaChefe[mesa]->encerrarAtendimento();
        mesaParaChefe.erase(mesa);
    }

    if (!filaEspera.empty()) {
        auto [mesaEspera, pedidoEspera] = filaEspera.front();
        filaEspera.pop();
        processarPedido(mesaEspera, pedidoEspera);
    }
}

void Restaurante::finalizar() {
    for (auto &chef : chefes)
        chef->encerrarAtendimento();
}

