#pragma once
#include <string>
#include <vector>

class Mesa {
    int id;
    std::vector<std::string> pedidos;
public:
    explicit Mesa(int id);
    int getId() const;
    void adicionarPedido(const std::string& pedido);
    const std::vector<std::string>& getPedidos() const;
    void salvarPedido(const std::string& pedido) const;
};
