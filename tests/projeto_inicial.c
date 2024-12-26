// BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

// CONSTANTES
#define STRING_MAX 100
#define MAX_CLIENTES 1000
#define MAX_MEDICOS 100
#define MAX_CONSULTAS 5000

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
  unsigned int NIF;
  unsigned int SNS;
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

// VARIÁVEIS GLOBAIS
const char *estadoConsulta[3] = { "Cancelado", "Agendado", "Realizado"};

// MENUS
void menuPrincipal(ST_CLIENTE *clientes, ST_MEDICO *medicos, ST_CONSULTA *consultas);
void menuClientes(ST_CLIENTE *clientes);
void menuMedicos(ST_MEDICO *medicos);
void menuConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);

// CLIENTES
int numeroClientes(ST_CLIENTE *clientes);
void inserirClientes(ST_CLIENTE *clientes);
void alterarDadosClientes(ST_CLIENTE *clientes);
void ativarDesativarClientes(ST_CLIENTE *clientes);
void consultarDadosClientes(ST_CLIENTE *clientes);
void obterListaClientesAtivos(ST_CLIENTE *clientes);
void procurarClientesNome(ST_CLIENTE *clientes);
void confirmarClientes(ST_CLIENTE *clientes, ST_CLIENTE cliente);
void infoClientes(ST_CLIENTE clientes);
ST_CLIENTE *obterCliente(ST_CLIENTE *clientes, unsigned int ID);

// MÉDICOS
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

// CONSULTAS
int numeroConsultas(ST_CONSULTA *consultas);
void agendarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);
void desmarcarConsultas(ST_CONSULTA *consultas);
void marcarConsultasRealizadas(ST_CONSULTA *consultas);
void atualizarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos);
void obterListaConsultasDiaAtualMedico(ST_CONSULTA *consulta, ST_MEDICO *medicos);
void obterHistoricoConsultasCliente(ST_CONSULTA *consulta, ST_CLIENTE *clientes);
void confirmarConsultas(ST_CONSULTA *consultas, ST_CONSULTA consulta);
int verificarDisponibilidade(ST_CONSULTA *consulta);
void infoConsultas(ST_CONSULTA consultas);
ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID);

// AUXILIARES
void clear(void);
void delay(int num);
void limparBuffer(void);
void dataAtual(ST_DATA *data_hora_atual);
void obterMorada(ST_CLIENTE *cliente);
void obterEspecialidade(ST_MEDICO *medico);
void listarEspecialidades(void);

// MAIN 
int main(){
    ST_CLIENTE clientes[MAX_CLIENTES];
    ST_MEDICO medicos[MAX_MEDICOS];
    ST_CONSULTA consultas[MAX_CONSULTAS];
    menuPrincipal(clientes, medicos, consultas);   
    return 0;
}

// FUNÇÕES MENUS
void menuPrincipal(ST_CLIENTE *clientes, ST_MEDICO *medicos, ST_CONSULTA *consultas){
  int opcao;
  do {
    clear();
    printf("[1] - Gestão de Clientes\n");
    printf("[2] - Gestão de Médicos\n");
    printf("[3] - Gestão de Consultas\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch (opcao){
    case 1:
      menuClientes(clientes);
      break;
    case 2:
      menuMedicos(medicos);
      break;
    case 3:
      menuConsultas(consultas, clientes, medicos);
      break;
    case 0:
      break;
    default:
      printf("Opção não é válida!\n");
      break;
    }
  } while (opcao != 0);
}

void menuClientes(ST_CLIENTE *clientes){
  int opcao;
  do {
    clear();
    printf("[1] - Inserir novo cliente\n");
    printf("[2] - Alterar dados de um cliente\n");
    printf("[3] - Ativar ou desativar um cliente\n");
    printf("[4] - Consultar dados de um cliente\n");
    printf("[5] - Obter uma lista de clientes ativos\n");
    printf("[6] - Procurar um cliente pelo nome\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch(opcao){
      case 1:
        inserirClientes(clientes);
        break;
      case 2:
        alterarDadosClientes(clientes);
        break;
      case 3:
        ativarDesativarClientes(clientes);
        break;
      case 4:
        consultarDadosClientes(clientes);
        break;
      case 5:
        obterListaClientesAtivos(clientes);
        break;
      case 6:
        procurarClientesNome(clientes);
      case 0:
        break;
      default: 
        printf("Opção não é válida!\n");
        break;
    }
  }while(opcao < 0 || opcao > 6);
}

void menuMedicos(ST_MEDICO *medicos){
  int opcao;
  do {
    clear();
    printf("[1] - Inserir novo médico\n");
    printf("[2] - Alterar dados de um médico\n");
    printf("[3] - Ativar ou desativar um médico\n");
    printf("[4] - Consultar dados de um médico\n");
    printf("[5] - Obter uma lista de todos os médicos\n");
    printf("[6] - Obter uma lista de médicos disponíveis\n");
    printf("[7] - Obter uma lista de médicos por especialidade\n");
    printf("[8] - Procurar um médico pelo nome\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch (opcao){
      case 1:
        inserirMedicos(medicos);
        break;
      case 2:
        alterarDadosMedicos(medicos);
        break;
      case 3:
        ativarDesativarMedicos(medicos);
        break;
      case 4:
        consultarDadosMedicos(medicos);
        break;
      case 5:
        obterListaTodosMedicos(medicos);
        break;
      case 6:
        obterListaMedicosAtivos(medicos);
        break;
      case 7:
        obterListaMedicosEspecialidade(medicos);
        break;
      case 8: 
        procurarMedicosNome(medicos);
        break;
      case 0:
        break;
      default: 
        printf("Opção não é válida!\n");
        break;
    }
  }while(opcao < 0 || opcao > 8);
}

void menuConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  int opcao;
  do {
    clear();
    printf("[1] - Agendar uma consulta\n");
    printf("[2] - Desmarcar uma consulta\n");
    printf("[3] - Marcar consulta como realizada\n");
    printf("[4] - Atualizar uma consulta\n");
    printf("[5] - Obter lista de consultas para o dia atual por médico\n");
    printf("[6] - Obter histórico de consultas por cliente\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch(opcao){
      case 1:
        agendarConsultas(consultas, clientes, medicos);
        break;
      case 2:
        desmarcarConsultas(consultas);
        break;
      case 3:
        marcarConsultasRealizadas(consultas);
        break;
      case 4:
        atualizarConsultas(consultas, clientes, medicos);
        break;
      case 5:
        obterListaConsultasDiaAtualMedico(consultas, medicos);
        break;
      case 6:
        obterHistoricoConsultasCliente(consultas, clientes);
        break;
      case 0:
        break;
      default:
        printf("Opção não é válida!\n");
        break;
    }
  }while(opcao < 0 || opcao > 6);
}

// FUNÇÕES CLIENTES
void inserirClientes(ST_CLIENTE *clientes){
  int opcao;
  if(numeroClientes(clientes) >= MAX_CLIENTES){
    printf("Número máximo de clientes atingido!\n");
    return;
  }else{
    clear();
    ST_CLIENTE cliente;
    cliente.ID = numeroClientes(clientes) + 1;
    printf("Nome do cliente: ");
    fgets(cliente.nome, STRING_MAX, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
    obterMorada(&cliente);
    printf("Rua: %s\n", cliente.morada.rua);
    printf("Cidade: %s\n", cliente.morada.cidade);
    printf("Data de nascimento (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &cliente.data_nascimento.dia, &cliente.data_nascimento.mes, &cliente.data_nascimento.ano);
    limparBuffer();
    printf("E-Mail: ");
    fgets(cliente.email, STRING_MAX, stdin);
    cliente.email[strcspn(cliente.email, "\n")] = '\0';
    printf("NIF: ");
    scanf("%d", &cliente.NIF);
    limparBuffer();
    printf("SNS: ");
    scanf("%d", &cliente.SNS);
    limparBuffer();
    cliente.estado = true;
  
    do {
    printf("Deseja confirmar inserção do cliente? [1] - SIM e [0] - NÃO: ");
    scanf("%d", &opcao);
    limparBuffer();
    } while(opcao != 0 && opcao != 1);
    if (opcao){
      confirmarClientes(clientes, cliente);
      printf("Cliente inserido com sucesso.\n");
      delay(1);
    }
  }
}

void alterarDadosClientes(ST_CLIENTE *clientes){
  int ID, opcao;
  clear();
  printf("ID do cliente: ");
  scanf("%d", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("O ID é inválido.\n");
    return;
  }
  ST_CLIENTE *cliente = &clientes[ID - 1];
  do {
    clear();
    printf("[1] - Nome\n");
    printf("[2] - Código Postal\n");
    printf("[3] - Data de nascimento\n");
    printf("[4] - E-Mail\n");
    printf("[5] - NIF\n");
    printf("[6] - SNS\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch(opcao){
      case 1:
        clear();
        printf("Nome: ");
        fgets(cliente->nome, STRING_MAX, stdin);
        cliente->nome[strcspn(cliente->nome, "\n")] = '\0';
        break;
      case 2:
        obterMorada(cliente);
        break;
      case 3: 
        clear();
        printf("Data de nascimento (dd-mm-aaaa): ");
        scanf("%d-%d-%d", &cliente->data_nascimento.dia, &cliente->data_nascimento.mes, &cliente->data_nascimento.ano);
        limparBuffer();
        break;
      case 4:
        clear();
        printf("E-Mail: ");
        fgets(cliente->email, STRING_MAX, stdin);
        cliente->email[strcspn(cliente->email, "\n")] = '\0';
        break;
      case 5:
        clear();
        printf("NIF: ");
        scanf("%d", &cliente->NIF);
        limparBuffer();
        break;
      case 6: 
        clear();
        printf("SNS: ");
        scanf("%d", &cliente->SNS);
        limparBuffer();
        break;
      case 0:
        break;
      default: 
        printf("Opção não é válida.\n");
        break;
    }
  }while (opcao != 0);
}

void ativarDesativarClientes(ST_CLIENTE *clientes){
  int ID;
  clear();
  printf("ID do cliente: ");
  scanf("%d", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("ID não é válido.\n");
    return;
  }
  clientes[ID - 1].estado = !clientes[ID - 1].estado;
  printf("Cliente %s com sucesso.\n", clientes[ID - 1].estado ? "ativado" : "desativado");
  return;
}

void consultarDadosClientes(ST_CLIENTE *clientes){
  int ID;
  clear();
  printf("ID do cliente: ");
  scanf("%d", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("ID não é válido.\n");
    return;
  }
  clear();
  infoClientes(clientes[ID - 1]);
  delay(5);
  return;
}

void obterListaClientesAtivos(ST_CLIENTE *clientes){
  int encontrados = 0;
  clear();
  printf("Lista de Clientes Ativos:\n");
  for (int i = 0; i < numeroClientes(clientes); i++){
    if (clientes[i].estado){
      infoClientes(clientes[i]);
      printf("\n");
      encontrados++;
    }
  }
  if (!encontrados){
    printf("Não existe clientes ativos.\n");
  }
  return;
}

void procurarClientesNome(ST_CLIENTE *clientes){
  char nome[STRING_MAX];
  int encontrados = 0;
  clear();
  printf("Nome do cliente: ");
  fgets(nome, STRING_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';
  for (int i = 0; i < numeroClientes(clientes); i++){
    if (strncmp(clientes[i].nome, nome, 4) == 0){
      infoClientes(clientes[i]);
      printf("\n");
      encontrados++;
    }
  }
  if (!encontrados){
  printf("Não existe clientes com o nome.\n");
  }
  return;
}


void confirmarClientes(ST_CLIENTE *clientes, ST_CLIENTE cliente){
  clientes[numeroClientes(clientes)] = cliente;
}

int numeroClientes(ST_CLIENTE *clientes){
  int i = 0;
  while (clientes[i].ID != 0){
    i++;
  }
  return i;
}

void infoClientes(ST_CLIENTE clientes){
  printf("ID: %d\n", clientes.ID);
  printf("Nome: %s\n", clientes.nome);
  printf("Código Postal: %ld\n", clientes.morada.codigo_postal);
  printf("E-Mail: %s\n", clientes.email);
  printf("Estado: %s\n", clientes.estado ? "Ativo" : "Inativo");
}

ST_CLIENTE *obterCliente(ST_CLIENTE *clientes, unsigned int ID){
  for (int i = 0; i < numeroClientes(clientes); i++){
    if(clientes[i].ID == ID){
      return &clientes[i];
    }
  }
  return NULL;
}

// FUNÇÕES MÉDICOS
void inserirMedicos(ST_MEDICO *medicos){
  int opcao;
  if(numeroMedicos(medicos) >= MAX_MEDICOS){
    printf("Número máximo de médicos atingido!\n");
    return;
  }else {
    clear();
    ST_MEDICO medico;
    medico.ID = numeroMedicos(medicos) + 1;
    printf("Nome do médico: ");
    fgets(medico.nome, STRING_MAX, stdin);
    medico.nome[strcspn(medico.nome, "\n")] = '\0';
    obterEspecialidade(&medico);
    medico.estado = true;

    do {
      printf("Deseja confirmar inserção do médico? [1] - SIM e [0] - NÃO: ");
      scanf("%d", &opcao);
      limparBuffer();
    }while(opcao!= 0 && opcao != 1);
    if(opcao){
      confirmarMedicos(medicos, medico);
      printf("Médico inserido com sucesso.\n");
      delay(1);
    }
  }
}

void alterarDadosMedicos(ST_MEDICO *medicos){
  int ID, opcao;
  clear();
  printf("ID do médico: ");
  scanf("%d", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("O ID é inválido.\n");
    return;
  }
  ST_MEDICO *medico = &medicos[ID - 1];
  do {
    clear();
    printf("[1] - Nome\n");
    printf("[2] - Especialidade\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch(opcao){
      case 1:
        clear();
        printf("Nome: ");
        fgets(medico->nome, STRING_MAX, stdin);
        medico->nome[strcspn(medico->nome, "\n")] = '\0';
        printf("Nome do médico alterado com sucesso.\n");
        delay(1);
        break;
      case 2:
        obterEspecialidade(medico);
        printf("Especialidade alterada com sucesso.\n");
        delay(1);
        break;
      case 0:
        break;
      default:
        printf("Opção não é válida.\n");
        break;
    }
  }while(opcao != 0);
}

void ativarDesativarMedicos(ST_MEDICO *medicos){
  int ID;
  clear();
  printf("ID do médico: ");
  scanf("%d", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("ID não é válido.\n");
    return;
  }
  medicos[ID - 1].estado = !medicos[ID - 1].estado;
  printf("Médico %s com sucesso.\n", medicos[ID - 1].estado ? "Disponível" : "Indisponível");
  return;
}

void consultarDadosMedicos(ST_MEDICO *medicos){
  int ID;
  clear();
  printf("ID do médico: ");
  scanf("%d", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("ID não é válido.\n");
    return;
  }
  clear();
  infoMedicos(medicos[ID - 1]);
  return;
}

void obterListaTodosMedicos(ST_MEDICO *medicos){
  int encontrados = 0;
  clear();
  printf("Lista de Médicos:\n");
  for (int i = 0; i < numeroMedicos(medicos); i++){
    infoMedicos(medicos[i]);
    printf("\n");
    encontrados++;
  }
  if(!encontrados){
    printf("Não há médicos registados.\n");
  }
}

void obterListaMedicosAtivos(ST_MEDICO *medicos){
  int encontrados = 0;
  clear();
  printf("Lista de Médicos Disponíveis:\n");
  for (int i = 0; i < numeroMedicos(medicos); i++){
    infoMedicos(medicos[i]);
    printf("\n");
    encontrados++;
  }
  if(!encontrados){
    printf("Não há médicos disponíveis.\n");
  }
}

void obterListaMedicosEspecialidade(ST_MEDICO *medicos){
  int encontrados = 0;
  char especialidade[STRING_MAX];
  clear();
  printf("Especialidade: ");
  fgets(especialidade, STRING_MAX, stdin);
  especialidade[strcspn(especialidade, "\n")] = '\0';
  clear();
  printf("Lista de Médicos de %s:\n", especialidade);
  for (int i = 0; i < numeroMedicos(medicos); i++){
    if(strncmp(medicos[i].especialidade, especialidade, 4) == 0){
      infoMedicos(medicos[i]);
      printf("\n");
      encontrados++;
    }
  }
  if (!encontrados){
    printf("Não há medicos com a especialidade %s.\n", especialidade);
  }
  return;
}

void procurarMedicosNome(ST_MEDICO *medicos){
  char nome[STRING_MAX];
  int encontrados = 0;
  clear();
  printf("Nome do médico: ");
  fgets(nome, STRING_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';
  for (int i = 0; i < numeroMedicos(medicos); i++){
    if(strncmp(medicos[i].nome, nome, 4) == 0){
      infoMedicos(medicos[i]);
      printf("\n");
      encontrados++;
    }
  }
  if(!encontrados){
    printf("Não há médicos com o nome %s.\n", nome);
  }
  return;
}

int numeroMedicos(ST_MEDICO *medicos){
  int i = 0;
  while (medicos[i].ID != 0){
    i++;
  }
  return i;
}

void confirmarMedicos(ST_MEDICO *medicos, ST_MEDICO medico){
  medicos[numeroMedicos(medicos)] = medico;
}

void infoMedicos(ST_MEDICO medicos){
  printf("ID: %d\n", medicos.ID);
  printf("Nome: %s\n", medicos.nome);
  printf("Especialidade: %s\n", medicos.especialidade);
  printf("Estado: %s\n", medicos.estado ? "Disponível" : "Indisponível");
}

ST_MEDICO *obterMedico(ST_MEDICO *medicos, unsigned int ID){
  for (int i = 0; i < numeroMedicos(medicos); i++){
    if(medicos[i].ID == ID){
      return &medicos[i];
    }
  }
  return NULL;
}

// FUNÇÕES CONSULTAS
void agendarConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  unsigned int clienteID, medicoID;
  int opcao;
  if(!numeroClientes(clientes)){
    printf("Não existe clientes registados.\n");
    return;
  }
  if (!numeroMedicos(medicos)){
    printf("Não existe médicos registados.\n");
    return;
  }
  clear();
  printf("ID do cliente: ");
  scanf("%d", &clienteID);
  limparBuffer();
  if(clientes[clienteID - 1].estado == false){
    printf("O cliente está inativo.\n");
    return;
  }
  printf("ID do médico: ");
  scanf("%d", &medicoID);
  if(medicos[medicoID - 1].estado == false){
    printf("O médico está indisponível.\n");
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
    if(!verificarDisponibilidade(&consulta)){
      printf("Horário não é válido.\n");
      delay(1);
    }
  }while(!verificarDisponibilidade(&consulta));
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
          if(!verificarDisponibilidade(consulta)){
            printf("Horário não é válido.\n");
            delay(1);
          }
        }while(!verificarDisponibilidade(consulta));
        infoConsultas(*consulta);
        delay(3);
        break;
      case 0:
        break;
      default:
        printf("Opção não é válida.\n");
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
  delay(10);
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
  delay(10);
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

int verificarDisponibilidade(ST_CONSULTA *consulta){
  ST_DATA data;
  dataAtual(&data);
  if(consulta->data_inicial.ano > data.ano || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes > data.mes) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia > data.dia) || (consulta->data_inicial.ano == data.ano && consulta->data_inicial.mes == data.mes && consulta->data_inicial.dia == data.dia && consulta->data_inicial.hora >= data.hora)){
    if(consulta->data_inicial.hora >= 8 || consulta->data_inicial.hora <= 18){
      if(consulta->medico->estado && consulta->cliente->estado){
        consulta->data_final.ano = consulta->data_inicial.ano;
        consulta->data_final.mes = consulta->data_inicial.mes;
        consulta->data_final.dia = consulta->data_inicial.dia;
        consulta->data_final.hora = consulta->data_inicial.hora + 1;
        return 1;
      }
    }
  }
  return 0;
}

void infoConsultas(ST_CONSULTA consultas){
  printf("ID: %d\n", consultas.ID);
  printf("Nome do cliente: %s\n", consultas.cliente->nome);
  printf("Nome do médico: %s\n", consultas.medico->nome);
  printf("Tipo de Consulta: %s\n", consultas.medico->especialidade);
  printf("Data: %d-%d-%d | Ás %dh até %dh\n", consultas.data_inicial.dia, consultas.data_inicial.mes, consultas.data_inicial.ano, consultas.data_inicial.hora, consultas.data_final.hora);
  printf("Estado: %s\n", estadoConsulta[consultas.estado]);
}

ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID){
  for (int i = 0; i < numeroConsultas(consultas); i++){
    if (consultas[i].ID == ID){
      return &consultas[i];
    }
  }
  return NULL;
}

// FUNÇÕES AUXILIARES
void clear(void){
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif
}

void delay(int num){
  #ifdef _WIN32
    Sleep(num * 1000);
  #else
    sleep(num);
  #endif
}

void limparBuffer(void){
  char c;
  while((c = getchar()) != '\n');
}

 void dataAtual(ST_DATA *data_hora_atual){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   data_hora_atual->hora = tm.tm_hour;
   data_hora_atual->dia = tm.tm_mday;
   data_hora_atual->mes = tm.tm_mon + 1;
   data_hora_atual->ano = tm.tm_year + 1900; 
 }

 void obterMorada(ST_CLIENTE *cliente){
   FILE *ficheiro;
   char linha[1024], *token;
   int encontrados = 0;
   unsigned long int codigo_postal;
   ficheiro = fopen("codigos.txt", "r");
   if (ficheiro == NULL){
    printf("Erro\n");
    return;
   }

    printf("Código Postal (1234567): ");
    scanf("%ld", &codigo_postal);
    limparBuffer();

   while (!feof(ficheiro)){
     fgets(linha, sizeof(linha), ficheiro);
     token = strtok(linha, ",");
     char *tokens[20];
     int total_tokens = 0;
     while(token != NULL){
       tokens[total_tokens] = token;
       total_tokens++;
       token = strtok(NULL, ",");
     }
     unsigned long int cod_postal = (atoi(tokens[total_tokens - 3]) * 1000) + atoi(tokens[total_tokens - 2]);
     if(cod_postal == codigo_postal){
       encontrados++;
       strcpy(cliente->morada.rua, tokens[3]);
       cliente->morada.rua[strcspn(cliente->morada.rua, "\n")] = '\0';
       strcpy(cliente->morada.cidade, tokens[total_tokens - 1]);
       cliente->morada.cidade[strcspn(cliente->morada.cidade, "\n")] = '\0';
       codigo_postal = cliente->morada.codigo_postal;
       break;
     }
   }
   if(encontrados == 0){
     printf("Código postal não encontrado.\n");
   }
   fclose(ficheiro);
   return;
 }

void obterEspecialidade(ST_MEDICO *medico){
  FILE *ficheiro;
  char linha[20], especialidade[20];
  int opcao;
  ficheiro = fopen("especialidade.txt", "r");
  if (ficheiro == NULL){
    printf("Erro\n");
    return;
  }
  clear();
  do { 
    clear();
    printf("[1] - Obter uma lista das especialidades\n");
    printf("[2] - Inserir a especialidade do médico\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
    switch (opcao){
      case 1:
        listarEspecialidades();
        break;
      case 2:
        clear();
        int especialidade_valida = 0;
        do{ 
          printf("Especialidade: ");
          fgets(especialidade, sizeof(especialidade), stdin);
          especialidade[strcspn(especialidade, "\n")] = '\0';
          while (fgets(linha, sizeof(linha), ficheiro) != NULL){
              linha[strcspn(linha, "\n")] = '\0';
              if(strncmp(especialidade, linha, 4) == 0){
              strcpy(medico->especialidade, especialidade);
              especialidade_valida = 1;
              break;
            }
          }
          if (!especialidade_valida){
            printf("Especialidade não é válida.\n");
          }
        }while(especialidade_valida != 1);
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
  }while(opcao != 2);
  fclose(ficheiro);
  return;
}

void listarEspecialidades(void){
  FILE *ficheiro;
  char linha[20];
  ficheiro = fopen("especialidade.txt", "r");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  clear();
  printf("Lista das Especialidades Disponíveis:\n\n");
  while(fgets(linha, sizeof(linha), ficheiro)){
    printf("%s", linha);
  }
  fclose(ficheiro);
  delay(5);
  return;
}
