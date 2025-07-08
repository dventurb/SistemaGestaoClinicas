#ifndef AUXILIARES_H
#define AUXILIARES_H

// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include "structs.h"
#include "cliente.h"

// PROTÓTIPOS DAS FUNÇÕES AUXILIARES
void dataAtual(ST_DATA *data_hora_atual);
bool obterMorada(ST_CLIENTE *cliente, long  unsigned int codigo_postal);
const char *obterCidade(int cod_distrito, int cod_concelho);
void obterEspecialidade(ST_MEDICO *medico);
void listarEspecialidades(void);
int numberOf(void *data, TYPE_STRUCT type);
bool validarFormatoData(const char *data);
bool validarData(const char *data);
bool validarCodigoPostal(const char *codigo_postal);
bool validarEmail(const char *email, void *data, TYPE_STRUCT type);
bool validarNIF(const char *nif, ST_CLIENTE *clients);
bool validarSNS(const char *sns, ST_CLIENTE *clients);
bool validarLicenseNumber(const char *license_number, ST_MEDICO *doctors);
const char *convertToUppercase(const char *input);
void generateSalt(char *string, size_t length);

#endif
