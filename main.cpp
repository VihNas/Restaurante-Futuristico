#include <iostream>
#include "restaurante.hpp"

int main() {
    Restaurante r(15, 60);//cria os 15 chefs e as 60 mesas

    std::string entrada;

    std::cout << "Digite: <mesa> <pedido>\n";

    while (true) {
        std::cout << "> ";
        getline(std::cin, entrada);//lê entrada

        if (entrada == "sair"){
            break;
        }
        auto espaco = entrada.find(' ');//procura espaço entre mesa e pedido
        if (espaco == std::string::npos){
            continue;
        }
        int mesa = stoi(entrada.substr(0, espaco));//converte n° da mesa
        std::string pedido = entrada.substr(espaco + 1);//lê pedido

        r.processarPedido(mesa, pedido);//envia pedido pro restaurante
    }

    r.finalizar();
}
