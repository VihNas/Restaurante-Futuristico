#include "mesa.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Mesa::Mesa(int id) : id(id) {}

int Mesa::getId() const {
    return id;
}

void Mesa::adicionarPedido(const string &pedido) {
    pedidos.push_back(pedido);
    salvarPedido(pedido);
}

const vector<string>& Mesa::getPedidos() const {
    return pedidos;
}

void Mesa::salvarPedido(const string &pedido) const {
    string nomeArquivo = "Mesa_" + to_string(id) + ".txt";
    ofstream arquivo(nomeArquivo, ios::app);
    if (arquivo.is_open()) {
        arquivo << "- " << pedido << endl;
        arquivo.close();
    } else {
        cerr << "Erro ao abrir arquivo da mesa " << id << endl;
    }
}
