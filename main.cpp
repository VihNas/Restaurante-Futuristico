#include <iostream>
#include <string>
#include <vector>
#include "restaurante.hpp"

int main() {
    int nChefes = 3;
    int nMesas = 10;
    Restaurante restaurante(nChefes);

    std::cout << "=== SIMULAÇÃO AUTOMÁTICA DO RESTAURANTE FUTURÍSTICO ===\n";
    std::cout << "Chefes: " << nChefes << " | Mesas: " << nMesas << "\n\n";

    // Simulação conforme o exemplo do PDF
    std::vector<std::pair<int, std::string>> pedidos = {
        {4, "hamburguer com batatas fritas"},
        {3, "bife acebolado"},
        {8, "salada de tomate"},
        {3, "suco natural de laranja (250ml)"},
        {5, "picanha na chapa"},
        {4, "cachorro quente"},
        {8, "espaguete ao molho branco"},
        {5, "porcao de batatas fritas"},
        {5, "fim"},
        {3, "bolo de chocolate"},
        {4, "fim"},
        {3, "fim"},
        {8, "suco natural de acerola (500ml)"},
        {4, "bife a parmegiana"},
        {4, "salada de alface"},
        {1, "pizza de calabresa"},
        {4, "fim"},
        {8, "pudim de leite condensado"},
        {1, "pizza de lombo ao creme"},
        {1, "fim"},
        {8, "fim"}
    };

    for (auto &[mesa, pedido] : pedidos) {
        restaurante.processarPedido(mesa, pedido);
    }

    std::cout << "\nFIM - encerrando restaurante futurístico.\n";
    restaurante.finalizar();

    std::cout << "\n=== Logs gerados ===\n";
    std::cout << "ChefeCozinha_1.txt\nChefeCozinha_2.txt\nChefeCozinha_3.txt\n";
    std::cout << "MesasNaoAtendidas.txt (se houver filas)\n";
    return 0;
}
