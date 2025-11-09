#pragma once
#include <string>
#include <vector>
using namespace std;

class Mesa {
    int id;
    vector<string> pedidos;
public:
    explicit Mesa(int id);
    int getId() const;
    void adicionarPedido(const string& pedido);
    const vector<string>& getPedidos() const;
    void salvarPedido(const string& pedido) const;
};

