#pragma once
#include <string>
#include <fstream>

class Atendimento;

class Chef {
public:
    Chef(unsigned int id, const std::string& nome);//construtor
    ~Chef();//destrutor

    void iniciarAtendimento(unsigned int mesa);
    void prepararPedido(const std::string& pedido);//registra preparo do pedido
    void encerrarMesa();
    bool livre() const;

private:
    unsigned int id;//identificador o chef
    std::string nome;//nome do chef
    unsigned int mesaAtual;
    Atendimento* atendimento = nullptr;//fila vinculada ao atendimento

    std::string nomeArquivo;
    std::ofstream log;

    void registrarInicio(unsigned int mesa);
    void registrarPedido(const std::string& pedido);
    void registrarFim();
};

