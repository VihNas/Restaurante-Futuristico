#include <iostream>
#include "restaurante.hpp"

int main() {
    Restaurante r(15, 60);

    std::string entrada;

    std::cout << "Digite: <mesa> <pedido>\n";

    while (true) {
        std::cout << "> ";
        getline(std::cin, entrada);

        if (entrada == "sair") break;

        auto espaco = entrada.find(' ');
        if (espaco == std::string::npos) continue;

        int mesa = stoi(entrada.substr(0, espaco));
        std::string pedido = entrada.substr(espaco + 1);

        r.processarPedido(mesa, pedido);
    }

    r.finalizar();
}
