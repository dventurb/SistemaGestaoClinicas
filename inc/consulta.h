#ifndef CONSULTA_H
#define CONSULTA_H

//BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cliente.h"
#include "medico.h"
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES CONSULTAS
int obterListaConsultasAgendadas(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found);
ST_CONSULTA *procurarConsultasID(ST_CONSULTA *appointments, unsigned int id);
int procurarConsultasNome(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, const char *name);
int procurarConsultasCliente(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, ST_CLIENTE *client, int numberClients);
int procurarConsultasMedico(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, ST_MEDICO *doctor, int numberDoctors);
int procurarConsultasData(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, const char *data);
void obterListaConsultasDiaAtualMedico(ST_CONSULTA *consulta, ST_MEDICO *medicos);
void obterHistoricoConsultasCliente(ST_CONSULTA *consulta, ST_CLIENTE *clientes);
int obterListaConsultasMesAtual(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found);
int obterNumeroConsultasMedico(ST_CONSULTA *appointments, ST_MEDICO doctor);
int obterNumeroConsultasEspecialidade(ST_CONSULTA *appointments, const char *speciality);
char **obterHorario(ST_CONSULTA *appointments, ST_CLIENTE *client, ST_MEDICO *doctor, const char *date);
void confirmarConsultas(ST_CONSULTA *consultas, ST_CONSULTA consulta);
bool verificarDisponibilidade(ST_CONSULTA *consultas, ST_CONSULTA *consulta);
ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID);
void inserirFicheiroConsulta(ST_CONSULTA consulta);
void carregarFicheiroConsulta(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);
void atualizarFicheiroConsulta(ST_CONSULTA *consultas);

#endif
