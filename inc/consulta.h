#ifndef CONSULTA_H
#define CONSULTA_H

//BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "cliente.h"
#include "medico.h"
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES CONSULTAS
int numeroConsultas(ST_CONSULTA *consultas);
void agendarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);
void desmarcarConsultas(ST_CONSULTA *consultas);
void marcarConsultasRealizadas(ST_CONSULTA *consultas);
void atualizarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);
void obterListaConsultasDiaAtualMedico(ST_CONSULTA *consulta, ST_MEDICO *medicos);
void obterHistoricoConsultasCliente(ST_CONSULTA *consulta, ST_CLIENTE *clientes);
void confirmarConsultas(ST_CONSULTA *consultas, ST_CONSULTA consulta);
bool verificarDisponibilidade(ST_CONSULTA *consultas, ST_CONSULTA *consulta);
void infoConsultas(ST_CONSULTA consultas);
ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID);

#endif