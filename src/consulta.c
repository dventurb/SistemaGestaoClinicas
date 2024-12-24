// BIBLIOTECAS
#include "consulta.h"

// FUNÇÕES CONSULTAS
void agendarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  unsigned int clienteID, medicoID;
  int opcao;
  if(!numeroClientes(clientes)){
    printf("Não existe clientes registados.\n");
    delay(1);
    return;
  }
  if (!numeroMedicos(medicos)){
    printf("Não existe médicos registados.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do cliente: ");
  scanf("%d", &clienteID);
  limparBuffer();
  if(!clientes[clienteID - 1].estado){
    printf("O cliente está inativo.\n");
    delay(1);
    return;
  }
  if (clienteID <= 0 || clienteID > numeroClientes(clientes)){
    printf("O ID é inválido.\n");
    delay(1);
    return;
  }
  printf("ID do médico: ");
  scanf("%d", &medicoID);
  if(!medicos[medicoID - 1].estado){
    printf("O médico está indisponível.\n");
    delay(1);
    return;
  }
  if(medicoID <= 0 || medicoID > numeroMedicos(medicos)){
    printf("O ID é inválido.\n");
    delay(1);
    return;
  }
  ST_CONSULTA consulta;
  consulta.ID = numeroConsultas(consultas) + 1;
  consulta.cliente = obterCliente(clientes, clienteID);
  consulta.medico = obterMedico(medicos, medicoID);
  do {
  printf("Data da consulta (dd-mm-aaaa): ");
  scanf("%d-%d-%d", &consulta.data_inicial.dia, &consulta.data_inicial.mes, &consulta.data_inicial.ano);
  limparBuffer();
    printf("Hora (8h - 18h): ");
    scanf("%d", &consulta.data_inicial.hora);
    limparBuffer();
    if(!verificarDisponibilidade(consultas, &consulta)){
      printf("Horário não é válido.\n");
      delay(1);
    }
  }while(!verificarDisponibilidade(consultas, &consulta));
  printf("Data: %d-%d-%d  | Ás %dh até %dh\n", consulta.data_inicial.dia, consulta.data_inicial.mes, consulta.data_inicial.ano, consulta.data_inicial.hora, consulta.data_final.hora);
  consulta.estado = Agendado;
  do {
    printf("Deseja confirmar agendamento da consulta? [1] - SIM e [0] - NÃO: ");
    scanf("%d", &opcao);
    limparBuffer();
  }while(opcao != 0 && opcao != 1);
  if(opcao){
    confirmarConsultas(consultas, consulta);
    printf("Consulta agendada com sucesso.\n");
    delay(1);
  }
}

void desmarcarConsultas(ST_CONSULTA *consultas){
  unsigned int ID;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\n");
    delay(1);
    return;
  }
  consulta->estado = Cancelado;
  printf("Consulta desmarcada com sucesso.\n");
  delay(1);
  return;
}

void marcarConsultasRealizadas(ST_CONSULTA *consultas){
  unsigned int ID;
  if(!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\n");
    delay(1);
    return;
  }
  consulta->estado = Realizado;
  printf("Consulta marcada como realizada.\n");
  delay(1);
  return;
}

void atualizarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  unsigned int ID, clienteID, medicoID;
  int opcao;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\n");
    delay(1);
    return;
  }
  do {
    clear();
    printf("[1] - ID do cliente\n");
    printf("[2] - ID do médico\n");
    printf("[3] - Horário da consulta\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch(opcao){
      case 1:
        do { 
          clear();
          printf("ID do cliente: ");
          scanf("%d", &clienteID);
          limparBuffer();
          if(!clientes[clienteID - 1].estado){
            printf("O cliente está inativo.\n");
            delay(1);
          }
        }while(!clientes[clienteID - 1].estado);
        consulta->cliente = obterCliente(clientes, clienteID);
        break;
      case 2:
        do {
          clear();
          printf("ID do médico: ");
          scanf("%d", &medicoID);
          limparBuffer();
          if(!medicos[medicoID -1].estado){
            printf("O médico está indisponível.\n");
            delay(1);
          }
        }while(!medicos[medicoID -1].estado);
        consulta->medico = obterMedico(medicos, medicoID);
        break;
      case 3:
        do {
          clear();
          printf("Data da consulta (dd-mm-aaaa): ");
          scanf("%d-%d-%d", &consulta->data_inicial.dia, &consulta->data_inicial.mes, &consulta->data_inicial.ano);
          limparBuffer();
          printf("Hora (8h - 18h): ");
          scanf("%d", &consulta->data_inicial.hora);
          limparBuffer();
          if(!verificarDisponibilidade(consultas, consulta)){
            printf("Horário não é válido.\n");
            delay(1);
          }
        }while(!verificarDisponibilidade(consultas, consulta));
        infoConsultas(*consulta);
        delay(5);
        break;
      case 0:
        break;
      default:
        printf("Opção não é válida.\n");
        delay(1);
        break;
    }
  }while(opcao != 0);
}

void obterListaConsultasDiaAtualMedico(ST_CONSULTA *consultas, ST_MEDICO *medicos){
  ST_DATA data;
  dataAtual(&data);
  unsigned int medicoID, encontrados = 0;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do médico: ");
  scanf("%d", &medicoID);
  limparBuffer();
  if(!medicos[medicoID -1].estado){
    printf("O médico está indisponível.\n");
    delay(1);
    return;
  }
  clear();
  for (int i = 0; i < numeroConsultas(consultas); i++){
    if(consultas[i].medico->ID == medicoID && consultas[i].data_inicial.ano == data.ano && consultas[i].data_inicial.mes == data.mes && consultas[i].data_inicial.dia == data.dia){
      infoConsultas(consultas[i]);
      encontrados++;
    }
  }
  if (!encontrados){
    printf("Não há consultas para o médico no dia de hoje.\n");
    delay(1);
    return;
  }
  delay(15);
  return;
}

void obterHistoricoConsultasCliente(ST_CONSULTA *consultas, ST_CLIENTE *clientes){
  unsigned int clienteID, encontrados = 0;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do cliente: ");
  scanf("%d", &clienteID);
  limparBuffer();
  if (!clientes[clienteID - 1].estado){
    printf("O cliente está inativo.\n");
    delay(1);
    return;
  }
  clear();
  for (int i = 0; i < numeroConsultas(consultas); i++){
    if(consultas[i].cliente->ID == clienteID){
      infoConsultas(consultas[i]);
      encontrados++;
    }
  }
  if (!encontrados){
    printf("Não há consultas para o cliente.\n");
    delay(1);
    return;
  }
  delay(15);
  return;
}

int numeroConsultas(ST_CONSULTA *consultas){
  int i = 0;
  while(consultas[i].ID != 0){
    i++;
  }
  return i;
}

void confirmarConsultas(ST_CONSULTA *consultas, ST_CONSULTA consulta){
  consultas[numeroConsultas(consultas)] = consulta;
}

bool verificarDisponibilidade(ST_CONSULTA *consultas,ST_CONSULTA *consulta){
  ST_DATA data;
  dataAtual(&data);
  for(int i = 0; i < numeroConsultas(consultas); i++){
    if(consultas[i].medico == consulta->medico && consultas[i].data_inicial.ano == consulta->data_inicial.ano && consultas[i].data_inicial.mes == consulta->data_inicial.mes && consultas[i].data_inicial.dia == consulta->data_inicial.dia && consultas[i].data_inicial.hora == consulta->data_inicial.hora){
      return false;
    }
  }
  for(int i = 0; i < numeroConsultas(consultas); i++){
    if(consultas[i].cliente == consulta->cliente && consultas[i].data_inicial.ano == consulta->data_inicial.ano && consultas[i].data_inicial.mes == consulta->data_inicial.mes && consultas[i].data_inicial.dia == consulta->data_inicial.dia && consultas[i].data_inicial.hora == consulta->data_inicial.hora){
      return false;
    }
  }
  if(consulta->data_inicial.ano > data.ano || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes > data.mes) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia > data.dia) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia == data.dia && consulta->data_inicial.hora >= data.hora)){
    if(consulta->data_inicial.hora >= 8 && consulta->data_inicial.hora <= 18){
      if(consulta->medico->estado && consulta->cliente->estado){
        consulta->data_final.ano = consulta->data_inicial.ano;
        consulta->data_final.mes = consulta->data_inicial.mes;
        consulta->data_final.dia = consulta->data_inicial.dia;
        consulta->data_final.hora = consulta->data_inicial.hora + 1;
        return true;
      }
    }
  }
  return false;
}

void infoConsultas(ST_CONSULTA consultas){
  char *estadoConsulta[3] = { "Cancelado", "Agendado", "Realizado"};
  printf("ID: %d\n", consultas.ID);
  printf("Nome do cliente: %s\n", consultas.cliente->nome);
  printf("Nome do médico: %s\n", consultas.medico->nome);
  printf("Tipo de Consulta: %s\n", consultas.medico->especialidade);
  printf("Data: %d-%d-%d | Ás %dh até %dh\n", consultas.data_inicial.dia, consultas.data_inicial.mes, consultas.data_inicial.ano, consultas.data_inicial.hora, consultas.data_final.hora);
  printf("Estado: %s\n\n", estadoConsulta[consultas.estado]);
}

ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID){
  for (int i = 0; i < numeroConsultas(consultas); i++){
    if (consultas[i].ID == ID){
      return &consultas[i];
    }
  }
  return NULL;
}