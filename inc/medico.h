#ifndef MEDICO_H
#define MEDICO_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES MÉDICOS
int numeroMedicos(ST_MEDICO *medicos);
void inserirMedicos(ST_MEDICO *medicos);
void alterarDadosMedicos(ST_MEDICO *medicos);
void ativarDesativarMedicos(ST_MEDICO *medicos);
void consultarDadosMedicos(ST_MEDICO *medicos);
void obterListaTodosMedicos(ST_MEDICO *medicos);
void obterListaMedicosAtivos(ST_MEDICO *medicos);
void obterListaMedicosEspecialidade(ST_MEDICO *medicos);
void procurarMedicosNome(ST_MEDICO *medicos);
void confirmarMedicos(ST_MEDICO *medicos, ST_MEDICO medico);
void infoMedicos(ST_MEDICO medicos);
ST_MEDICO *obterMedico(ST_MEDICO *medicos, unsigned int ID);
void inserirFicheiroMedico(ST_MEDICO medico);
void carregarFicheiroMedico(ST_MEDICO *medicos);
void atualizarFicheiroMedico(ST_MEDICO *medicos);

#endif