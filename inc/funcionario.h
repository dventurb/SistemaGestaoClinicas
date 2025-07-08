#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

// BIBLIOTECAS
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <crypt.h>
#include "auxiliares.h"

// PROTÓTIPOS DAS FUNÇÕES FUNCIONARIO 
bool authValidate(ST_FUNCIONARIO *staff, const char *username, const char *password);
bool usernameValidate(ST_FUNCIONARIO *staff, const char *username);
bool encryptPassword(ST_FUNCIONARIO *new, const char *password);
void createUser(ST_FUNCIONARIO *staff, ST_FUNCIONARIO new);
void insertUserFile(ST_FUNCIONARIO *new);
void loadUserFile(ST_FUNCIONARIO *staff);
void updateUserFile(ST_FUNCIONARIO *staff);

#endif
