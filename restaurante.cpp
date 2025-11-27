// Restaurante.cpp
#include "restaurante.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cctype>   // isspace
#include <memory>   // shared_ptr

Restaurante::Restaurante(int nChefes, int nMesas) {
    static const std::string nomes[] = {
        "Vitória","Carlos","Natálly","Chihiro","Kiki",
        "Totoro","Valesca","Luiza","Ponyo","Haru",
        "Aylla","Nadylla","Sakura","Brino","Ghibi"
    };
    // garante que não ultrapassa o número de nomes definidos
    int maxNomes = static_cast<int>(sizeof(nomes)/sizeof(nomes[0]));
    int total = std::min(nChefes, maxNomes);

    // reserva espaço para os chefs
    chefes.reserve(total);
    for (int i = 0; i < total; ++i) {
        chefes.push_back(std::make_shared<Chef>(i, nomes[i]));
        // enfileira o índice do chef na fila de chefs livres
        chefsLivres.push(i);
    }

    // -1 sig sem chefe 
    mesaParaChefe.assign(nMesas + 1, -1);

    indiceChef = 0;
}


void Restaurante::processarPedido(int mesa, const std::string& pedidoRaw) {
    //  limpeza  do pedido, estética, não necessario, verificaçoes de entrada ---
    std::string pedido = pedidoRaw;
    while (!pedido.empty() && isspace((unsigned char)pedido.front())) pedido.erase(pedido.begin());
    while (!pedido.empty() && isspace((unsigned char)pedido.back())) pedido.pop_back();

    if (mesa < 1 || mesa >= (int)mesaParaChefe.size()) {
        std::cerr << "Mesa inválida: " << mesa << std::endl;
        return;
    }

    // se já houver chef atendendo aql mesa
    if (mesaParaChefe[mesa] != -1) {
        int id = mesaParaChefe[mesa];

        // se a mesa finaliza ("fim")
        if (pedido == "fim") {
            // encerra a mesa com o chefe atual
            chefes[id]->encerrarMesa();
            mesaParaChefe[mesa] = -1;

            // coloca esse chef de volta na fila de livres 
            chefsLivres.push(id);

            // se houver alguém na fila de espera, já pega o próximo pedido e atende 
            if (!filaEspera.empty() && !chefsLivres.empty()) {
                // pega o próximo cliente em espera(mesa que está esperando ser atendida)
                auto [mesaFila, filaPedidos] = std::move(filaEspera.front());
                filaEspera.pop();

                // obtém um chef livre e pega ele
                int idxLivre = chefsLivres.front();
                chefsLivres.pop();

                // atribui e serve todos os pedidos acumulados dessa mesa
                mesaParaChefe[mesaFila] = idxLivre;
                chefes[idxLivre]->iniciarAtendimento(mesaFila);
                while (!filaPedidos.empty()) {
                    chefes[idxLivre]->prepararPedido(filaPedidos.front());
                    filaPedidos.pop();
                }
            }
            return;
        }

        // enquanto mesa já está sendo atendida
        chefes[id]->prepararPedido(pedido);
        return;
    }

    
    if (pedido == "fim") {
        // mesa sem chefe que manda "fim" -> simplesmente ignora, pq é como se eles estivem pagando a conta
        return;
    }

    
    if (!chefsLivres.empty()) {
        int indiceLivre = chefsLivres.front(); // O(1)
        chefsLivres.pop();                     // O(1)

        // atribui o chef livre à mesa
        mesaParaChefe[mesa] = indiceLivre;
        chefes[indiceLivre]->iniciarAtendimento(mesa);
        chefes[indiceLivre]->prepararPedido(pedido);
        return;
    }

    // se por acaso não tiver nenhum chef livre, enfileira a mesa na fila de espera 
    // usamos uma fila de pedidos por mesa para manter pedidos 
    std::queue<std::string> filaPed;
    filaPed.push(pedido);
    filaEspera.push({mesa, std::move(filaPed)}); 

    // log  das mesas não atendidas 
    std::ofstream log("MesasNaoAtendidas.txt", std::ios::app);
    if (log.is_open()) {
        log << "Mesa " << mesa << " aguardando: " << pedido << "\n";
    }
}

// Função que libera um chefe após o fim
void Restaurante::liberarChefe(int mesa) {
    if (mesa < 1 || mesa >= (int)mesaParaChefe.size()) return;
    int id = mesaParaChefe[mesa];
    if (id != -1) {
        // encerra e marca mesa como sem chefe
        chefes[id]->encerrarMesa();
        mesaParaChefe[mesa] = -1;

        // coloca o chef liberado na fila de livres 
        chefsLivres.push(id);
    }

    // se houver fila de espera e houver chef livre, atende o próximo 
    if (!filaEspera.empty() && !chefsLivres.empty()) {
        auto [mesaFila, filaPedidos] = std::move(filaEspera.front());
        filaEspera.pop();

        int idxLivre = chefsLivres.front();
        chefsLivres.pop();

        mesaParaChefe[mesaFila] = idxLivre;
        chefes[idxLivre]->iniciarAtendimento(mesaFila);
        while (!filaPedidos.empty()) {
            chefes[idxLivre]->prepararPedido(filaPedidos.front());
            filaPedidos.pop();
        }
    }
}

// encerra tudo 
void Restaurante::finalizar() {
    for (auto& c : chefes) {
        c->encerrarMesa();
    }
}
