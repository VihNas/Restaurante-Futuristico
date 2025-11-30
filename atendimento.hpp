#pragma once

#include <string>
#include <fstream>
//necessarias para manipulação de processos (fork, pipe, read, write)
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>//para enviar sinais do sistema (kill)

class Atendimento {
public:
    Atendimento(unsigned int chefId, unsigned int mesaId);
    ~Atendimento();

    void enviarPedido(const std::string& pedido);
    void iniciar(); // roda do processo filho (bloqueante)

private:
    unsigned int chefId;//identifica chefe responsável
    unsigned int mesaId;//identifica mesa atendida
    int fd[2];
    pid_t pid;
    std::string nomeArquivo;
    std::string quemSou;
    std::ofstream log;
};
