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
#ifdef _WIN32
  #include <windows.h>  // Função Sleep em sistemas Windows
  #include <conio.h>    // Função getch em sistemas Windows
#else
  #include <unistd.h>   // Função sleep em sistemas Unix
  #include <termios.h>  // Desativar o echo e modo canônico em sistemas Unix
#endif

// PROTÓTIPOS DAS FUNÇÕES AUXILIARES
void clear(void);
void delay(int num);
void limparBuffer(void);
void dataAtual(ST_DATA *data_hora_atual);
bool obterMorada(ST_CLIENTE *cliente, long  unsigned int codigo_postal);
void obterEspecialidade(ST_MEDICO *medico);
void listarEspecialidades(void);
void pressionarEnter(void);
void navegarMenu(int *opcao, int tecla, int n);
void selecionarOpcao(int *opcao, int tecla);
int getKey(void);
void ativarDesativarCursor(int n);
int numberOf(void *data, TYPE_STRUCT type);
bool validarFormatoData(const char *data);
bool validarCodigoPostal(const char *codigo_postal);
bool validarEmail(const char *email, void *data, TYPE_STRUCT type);
bool validarNIF(const char *nif, ST_CLIENTE *clients);
bool validarSNS(const char *sns, ST_CLIENTE *clients);
bool validarLicenseNumber(const char *license_number, ST_MEDICO *doctors);
const char *convertToUppercase(const char *input);

#endif
