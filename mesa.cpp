#include "mesa.hpp"
#include <fstream>
#include <iostream>

Mesa::Mesa(int id) : id(id) {}

int Mesa::getId() const {
    return id;
}

void Mesa::adicionarPedido(const std::string &pedido) {
    pedidos.push_back(pedido);
    salvarPedido(pedido);
}

const std::vector<std::string>& Mesa::getPedidos() const {
    return pedidos;
}

void Mesa::salvarPedido(const std::string& pedido) const {
    std::string nomeArquivo = "Mesa_" + std::to_string(id) + ".txt";
    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "- " << pedido << std::endl;
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir arquivo da mesa " << id << std::endl;
    }
}
