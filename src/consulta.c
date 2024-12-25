// BIBLIOTECAS
#include "consulta.h"

// FUNÇÕES CONSULTAS
void agendarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  unsigned int clienteID, medicoID;
  int opcao;
  if(!numeroClientes(clientes)){
    printf("Não existe clientes registados.\a\n");
    delay(1);
    return;
  }
  if (!numeroMedicos(medicos)){
    printf("Não existe médicos registados.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do cliente: ");
  scanf("%d", &clienteID);
  limparBuffer();
  if (clienteID <= 0 || clienteID > numeroClientes(clientes)){
    printf("O ID é inválido.\a\n");
    delay(1);
    return;
  }
  if(!clientes[clienteID - 1].estado){
    printf("O cliente está inativo.\a\n");
    delay(1);
    return;
  }
  printf("ID do médico: ");
  scanf("%d", &medicoID);
  if(medicoID <= 0 || medicoID > numeroMedicos(medicos)){
    printf("O ID é inválido.\a\n");
    delay(1);
    return;
  }
  if(!medicos[medicoID - 1].estado){
    printf("O médico está indisponível.\a\n");
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
      printf("Horário não é válido.\a\n");
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
    inserirFicheiroConsulta(consulta);
    printf("Consulta agendada com sucesso.\n");
    delay(1);
  }
}

void desmarcarConsultas(ST_CONSULTA *consultas){
  unsigned int ID;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\a\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\a\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\a\n");
    delay(1);
    return;
  }
  consulta->estado = Cancelado;
  atualizarFicheiroConsulta(consultas);
  printf("Consulta desmarcada com sucesso.\n");
  delay(1);
  return;
}

void marcarConsultasRealizadas(ST_CONSULTA *consultas){
  unsigned int ID;
  if(!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\a\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\a\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\a\n");
    delay(1);
    return;
  }
  consulta->estado = Realizado;
  atualizarFicheiroConsulta(consultas);
  printf("Consulta marcada como realizada.\n");
  delay(1);
  return;
}

void atualizarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  unsigned int ID, clienteID, medicoID;
  int opcao;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID da consulta: ");
  scanf("%d", &ID);
  limparBuffer();
  ST_CONSULTA *consulta = obterConsulta(consultas, ID);
  if (consulta == NULL){
    printf("Consulta não foi encontrada.\a\n");
    delay(1);
    return;
  }
  if (consulta->estado == Realizado){
    printf("Consulta já foi realizada.\n");
    delay(1);
    return;
  }
  if (consulta->estado == Cancelado){
    printf("Consulta já foi cancelada.\a\n");
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
            printf("O cliente está inativo.\a\n");
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
            printf("O médico está indisponível.\a\n");
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
            printf("Horário não é válido.\a\n");
            delay(1);
          }
        }while(!verificarDisponibilidade(consultas, consulta));
        infoConsultas(*consulta);
        delay(5);
        break;
      case 0:
        atualizarFicheiroConsulta(consultas);
        break;
      default:
        printf("Opção não é válida.\a\n");
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
    printf("Não há consultas registadas.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do médico: ");
  scanf("%d", &medicoID);
  limparBuffer();
  if(!medicos[medicoID -1].estado){
    printf("O médico está indisponível.\a\n");
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
    printf("Não há consultas para o médico no dia de hoje.\a\n");
    delay(1);
    return;
  }
  delay(15);
  return;
}

void obterHistoricoConsultasCliente(ST_CONSULTA *consultas, ST_CLIENTE *clientes){
  unsigned int clienteID, encontrados = 0;
  if (!numeroConsultas(consultas)){
    printf("Não há consultas registadas.\a\n");
    delay(1);
    return;
  }
  clear();
  printf("ID do cliente: ");
  scanf("%d", &clienteID);
  limparBuffer();
  if (!clientes[clienteID - 1].estado){
    printf("O cliente está inativo.\a\n");
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
    printf("Não há consultas para o cliente.\a\n");
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

  if(consulta->data_inicial.ano > data.ano || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes > data.mes) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia > data.dia) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia == data.dia && consulta->data_inicial.hora > data.hora)){
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

void inserirFicheiroConsulta(ST_CONSULTA consulta){
  char *estadoConsulta[3] = { "Cancelado", "Agendado", "Realizado"};
  FILE *ficheiro = fopen("data/consultas.txt", "a");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  fprintf(ficheiro, "%d,%d,%s,%d,%s,%s,%d,%d,%d,%d,%d,%s\n", consulta.ID, consulta.cliente->ID, consulta.cliente->nome, consulta.medico->ID, consulta.medico->nome, consulta.medico->especialidade, consulta.data_inicial.dia, consulta.data_inicial.mes, consulta.data_inicial.ano, consulta.data_inicial.hora, consulta.data_final.hora, estadoConsulta[consulta.estado]);
  fclose(ficheiro);
  return;
}

void carregarFicheiroConsulta(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
char linha[1024], *token;
unsigned int clienteID, medicoID;
int i = 0;
FILE *ficheiro;
ficheiro = fopen("data/consultas.txt", "r");
if (ficheiro == NULL){
  printf("Erro\n");
  return;
}
while(fgets(linha, sizeof(linha), ficheiro) && i < MAX_CONSULTAS){
  linha[strcspn(linha, "\n")] = '\0';
  token = strtok(linha, ",");
  consultas[i].ID = (atoi(token));
  token = strtok(NULL, ",");
  clienteID = (atoi(token));
  consultas[i].cliente = obterCliente(clientes, clienteID);
  token = strtok(NULL, ",");
  token = strtok(NULL, ",");
  medicoID = (atoi(token));
  consultas[i].medico = obterMedico(medicos, medicoID);
  token = strtok(NULL, ",");
  token = strtok(NULL, ",");
  token = strtok(NULL, ",");
  consultas[i].data_inicial.dia = (atoi(token));
  token = strtok(NULL, ",");
  consultas[i].data_inicial.mes = (atoi(token));
  token = strtok(NULL, ",");
  consultas[i].data_inicial.ano = (atoi(token));
  token = strtok(NULL, ",");
  consultas[i].data_inicial.hora = (atoi(token));
  token = strtok(NULL, ",");
  consultas[i].data_final.hora = (atoi(token));
  token = strtok(NULL, ",");
  if(strcmp(token, "Cancelado") == 0){
    consultas[i].estado = 0;
  }else if(strcmp(token, "Agendado") == 0){
    consultas[i].estado = 1;
  }else if(strcmp(token, "Realizado") == 0){
    consultas[i].estado = 2;
  }
  consultas[i].data_final.dia = consultas[i].data_inicial.dia;
  consultas[i].data_final.mes = consultas[i].data_inicial.mes;
  consultas[i].data_final.ano = consultas[i].data_inicial.ano;
  i++;
}
fclose(ficheiro);
return;
}

void atualizarFicheiroConsulta(ST_CONSULTA *consultas){
  char *estadoConsulta[3] = {"Cancelado", "Agendado", "Realizado"};
  FILE *ficheiro;
  ficheiro = fopen("data/consultas.txt", "w");
  if (ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  for (int i = 0; i < numeroConsultas(consultas); i++){
    fprintf(ficheiro, "%d,%s,%s,%s,%d,%d,%d,%d,%d,%s\n", consultas[i].ID, consultas[i].cliente->nome, consultas[i].medico->nome, consultas[i].medico->especialidade, consultas[i].data_inicial.dia, consultas[i].data_inicial.mes, consultas[i].data_inicial.ano, consultas[i].data_inicial.hora, consultas[i].data_final.hora, estadoConsulta[consultas[i].estado]);
  }
  fclose(ficheiro);
  return;
}