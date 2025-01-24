#ifndef AUXILIARES_H
#define AUXILIARES_H

// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "structs.h"
#ifdef _WIN32
  #include <windows.h> // Função Sleep em sistemas Windows
#else
  #include <unistd.h> // Função sleep em sistemas Unix
#endif

// PROTÓTIPOS DAS FUNÇÕES AUXILIARES
void clear(void);
void delay(int num);
void limparBuffer(void);
void dataAtual(ST_DATA *data_hora_atual);
void obterMorada(ST_CLIENTE *cliente);
void obterEspecialidade(ST_MEDICO *medico);
void listarEspecialidades(void);
void pressionarEnter(void);

#endif