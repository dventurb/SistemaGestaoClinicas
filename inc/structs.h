#ifndef STRUCTS_H
#define STRUCTS_H

// BIBLIOTECAS
#include <stdbool.h>

// CONSTANTES
#define STRING_MAX 100
#define MAX_CLIENTES 1000
#define MAX_MEDICOS 100
#define MAX_CONSULTAS 5000
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

// ESTRUTURAS E ENUMERADORES
typedef enum {
  Cancelado = 0,
  Agendado = 1,
  Realizado = 2
}ESTADO;

typedef struct {
  char rua[STRING_MAX];
  unsigned long int codigo_postal;
  char cidade[STRING_MAX];
}ST_MORADA;

typedef struct {
  unsigned int hora;
  unsigned int dia;
  unsigned int mes;
  unsigned int ano;
}ST_DATA;

typedef struct {
  unsigned int ID;
  char nome[STRING_MAX];
  char email[STRING_MAX];
  ST_MORADA morada;
  ST_DATA data_nascimento;
  unsigned long int NIF;
  unsigned long int SNS;
  bool estado;
}ST_CLIENTE;

typedef struct {
  unsigned int ID;
  char nome[STRING_MAX];
  char especialidade[STRING_MAX];
  bool estado;
}ST_MEDICO;

typedef struct {
  unsigned int ID;
  ST_CLIENTE *cliente;
  ST_MEDICO *medico;
  ST_DATA data_inicial;
  ST_DATA data_final;
  ESTADO estado;
}ST_CONSULTA;


typedef struct {
  ST_CLIENTE *clientes;
  ST_MEDICO *medicos;
  ST_CONSULTA *consultas;
} ST_APPLICATION;

#endif
