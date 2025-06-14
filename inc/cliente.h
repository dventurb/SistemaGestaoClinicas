#ifndef CLIENTES_H
#define CLIENTES_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES CLIENTES
int numeroClientes(ST_CLIENTE *clientes);
void inserirClientes(ST_CLIENTE *clientes);
void alterarDadosClientes(ST_CLIENTE *clientes);
void ativarDesativarClientes(ST_CLIENTE *clientes);
void consultarDadosClientes(ST_CLIENTE *clientes);
int obterListaClientesAtivos(ST_CLIENTE *clients, ST_CLIENTE **clients_found);
ST_CLIENTE *procurarClientesID(ST_CLIENTE *clients, unsigned int id);
ST_CLIENTE *procurarClientesEmail(ST_CLIENTE *clients, const char *email);
ST_CLIENTE *procurarClientesNIF(ST_CLIENTE *clients, unsigned int nif);
ST_CLIENTE *procurarClientesSNS(ST_CLIENTE *clients, unsigned int sns);
int procurarClientesNome(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *name);
int procurarClientesData(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *data);
int procurarClientesCodigoPostal(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *input);
void confirmarClientes(ST_CLIENTE *clientes, ST_CLIENTE cliente);
void infoClientes(ST_CLIENTE clientes);
ST_CLIENTE *obterCliente(ST_CLIENTE *clientes, unsigned int ID);
void inserirFicheiroCliente(ST_CLIENTE cliente);
void carregarFicheiroCliente(ST_CLIENTE *clientes);
void atualizarFicheiroCliente(ST_CLIENTE *clientes);

#endif
