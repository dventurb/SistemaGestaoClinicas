#ifndef MENU_H
#define MENU_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include "structs.h"
#include "cliente.h"
#include "auxiliares.h"
#include "medico.h"
#include "consulta.h"

// PROTÓTIPOS DAS FUNÇÕES MENUS
void menuPrincipal(ST_CLIENTE *clientes, ST_MEDICO *medicos, ST_CONSULTA *consultas);
void menuClientes(ST_CLIENTE *clientes);
void menuMedicos(ST_MEDICO *medicos);
void menuConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);

#endif