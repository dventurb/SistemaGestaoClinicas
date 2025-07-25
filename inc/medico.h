#ifndef MEDICO_H
#define MEDICO_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES MÉDICOS
int numeroMedicos(ST_MEDICO *medicos);
int obterListaMedicosAtivos(ST_MEDICO *doctors, ST_MEDICO **doctors_active);
ST_MEDICO *procurarMedicosID(ST_MEDICO *doctors, unsigned int id);
ST_MEDICO *procurarMedicosEmail(ST_MEDICO *doctors, const char *email);
ST_MEDICO *procurarMedicosLicenseNumber(ST_MEDICO *doctors, unsigned int cedula);
int procurarMedicosNome(ST_MEDICO *doctors, ST_MEDICO **doctors_found, const char *name);int procurarMedicosEspecialidade(ST_MEDICO *doctors, ST_MEDICO **doctors_found, const char *speciality);
void confirmarMedicos(ST_MEDICO *medicos, ST_MEDICO medico);
void inserirFicheiroMedico(ST_MEDICO medico);
void carregarFicheiroMedico(ST_MEDICO *medicos);
void atualizarFicheiroMedico(ST_MEDICO *medicos);

#endif
