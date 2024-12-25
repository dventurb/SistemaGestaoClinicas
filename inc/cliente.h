#ifndef CLIENTES_H
#define CLIENTES_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES CLIENTES
int numeroClientes(ST_CLIENTE *clientes);
void inserirClientes(ST_CLIENTE *clientes);
void alterarDadosClientes(ST_CLIENTE *clientes);
void ativarDesativarClientes(ST_CLIENTE *clientes);
void consultarDadosClientes(ST_CLIENTE *clientes);
void obterListaClientesAtivos(ST_CLIENTE *clientes);
void procurarClientesNome(ST_CLIENTE *clientes);
void confirmarClientes(ST_CLIENTE *clientes, ST_CLIENTE cliente);
void infoClientes(ST_CLIENTE clientes);
ST_CLIENTE *obterCliente(ST_CLIENTE *clientes, unsigned int ID);
void inserirFicheiroCliente(ST_CLIENTE cliente);
void carregarFicheiroCliente(ST_CLIENTE *clientes);
void atualizarFicheiroCliente(ST_CLIENTE *clientes);

#endif