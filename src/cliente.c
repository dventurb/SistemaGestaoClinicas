// BIBLIOTECAS
#include "cliente.h"

// FUNÇÕES CLIENTES
void inserirClientes(ST_CLIENTE *clientes){
  int opcao;
  if(numeroClientes(clientes) >= MAX_CLIENTES){
    printf("Número máximo de clientes atingido!\a\n");
    delay(1);
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
    scanf("%2u-%2u-%4u", &cliente.data_nascimento.dia, &cliente.data_nascimento.mes, &cliente.data_nascimento.ano);
    limparBuffer();
    printf("E-Mail: ");
    fgets(cliente.email, STRING_MAX, stdin);
    cliente.email[strcspn(cliente.email, "\n")] = '\0';
    printf("NIF: ");
    scanf("%9lu", &cliente.NIF);
    limparBuffer();
    printf("SNS: ");
    scanf("%9lu", &cliente.SNS);
    limparBuffer();
    cliente.estado = true;
  
    do {
    printf("Deseja confirmar inserção do cliente? [1] - SIM e [0] - NÃO: ");
    scanf("%1d", &opcao);
    limparBuffer();
    } while(opcao != 0 && opcao != 1);
    if (opcao){
      confirmarClientes(clientes, cliente);
      inserirFicheiroCliente(cliente);
      printf("Cliente inserido com sucesso.\n");
      delay(1);
    }
  }
}

void alterarDadosClientes(ST_CLIENTE *clientes){
  int ID, opcao;
  clear();
  printf("ID do cliente: ");
  scanf("%u", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("O ID é inválido.\a\n");
    delay(1);
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
    scanf("%1d", &opcao);
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
        scanf("%2u-%2u-%4u", &cliente->data_nascimento.dia, &cliente->data_nascimento.mes, &cliente->data_nascimento.ano);
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
        scanf("%9lu", &cliente->NIF);
        limparBuffer();
        break;
      case 6: 
        clear();
        printf("SNS: ");
        scanf("%9lu", &cliente->SNS);
        limparBuffer();
        break;
      case 0:
        atualizarFicheiroCliente(clientes);
        break;
      default: 
        printf("Opção não é válida.\a\n");
        delay(1);
        break;
    }
  }while (opcao != 0);
}

void ativarDesativarClientes(ST_CLIENTE *clientes){
  int ID;
  clear();
  printf("ID do cliente: ");
  scanf("%u", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("ID não é válido.\a\n");
    delay(1);
    return;
  }
  clientes[ID - 1].estado = !clientes[ID - 1].estado;
  atualizarFicheiroCliente(clientes);
  printf("Cliente %s com sucesso.\n", clientes[ID - 1].estado ? "ativado" : "inativado");
  delay(1);
  return;
}

void consultarDadosClientes(ST_CLIENTE *clientes){
  int ID;
  clear();
  printf("ID do cliente: ");
  scanf("%u", &ID);
  limparBuffer();
  if (ID <= 0 || ID > numeroClientes(clientes)){
    printf("ID não é válido.\a\n");
    delay(1);
    return;
  }
  clear();
  infoClientes(clientes[ID - 1]);
  pressionarEnter();
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
    clear();
    printf("Não existe clientes ativos.\a\n");
    delay(1);
    return;
  }
  pressionarEnter();
}

void procurarClientesNome(ST_CLIENTE *clientes){
  char nome[STRING_MAX];
  int encontrados = 0;
  clear();
  printf("Nome do cliente: ");
  fgets(nome, STRING_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';
  nome[0] = toupper(nome[0]);
  for (int i = 0; i < numeroClientes(clientes); i++){
    if (strncmp(clientes[i].nome, nome, 2) == 0){
      infoClientes(clientes[i]);
      printf("\n");
      encontrados++;
    }
  }
  if (!encontrados){
    clear();
    printf("Não existe clientes com o nome.\a\n");
    delay(1);
    return;
  }
  pressionarEnter();
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
  printf("ID: %u\n", clientes.ID);
  printf("Nome: %s\n", clientes.nome);
  printf("Código Postal: %lu | Rua: %s | Cidade: %s\n", clientes.morada.codigo_postal, clientes.morada.rua, clientes.morada.cidade);
  printf("Data de Nascimento: %2u-%2u-%4u\n", clientes.data_nascimento.dia, clientes.data_nascimento.mes, clientes.data_nascimento.ano);
  printf("E-Mail: %s\n", clientes.email);
  printf("NIF: %lu\n", clientes.NIF);
  printf("SNS: %lu\n", clientes.SNS);
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

void inserirFicheiroCliente(ST_CLIENTE cliente){
  FILE *ficheiro = fopen("data/clientes.txt", "a");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  fprintf(ficheiro, "%u,%s,%lu,%s,%s,%2u,%2u,%4u,%s,%9lu,%9lu,%s\n", cliente.ID, cliente.nome, cliente.morada.codigo_postal, cliente.morada.rua, cliente.morada.cidade, cliente.data_nascimento.dia, cliente.data_nascimento.mes, cliente.data_nascimento.ano, cliente.email, cliente.NIF, cliente.SNS, cliente.estado ? "Ativo" : "Inativo");
  fclose(ficheiro);
  return;
}

void carregarFicheiroCliente(ST_CLIENTE *clientes){
  char linha[1024], *token;
  int i = 0;
  FILE *ficheiro;
  ficheiro = fopen("data/clientes.txt", "r");
  if(ficheiro == NULL){
    return;
  }
  while(fgets(linha, sizeof(linha), ficheiro) && i < MAX_CLIENTES){
    linha[strcspn(linha, "\n")] = '\0';
    token = strtok(linha, ",");
    clientes[i].ID = (atoi(token));
    token = strtok(NULL, ",");
    strncpy(clientes[i].nome, token, STRING_MAX);
    token = strtok(NULL, ",");
    clientes[i].morada.codigo_postal = (atoi(token));
    token = strtok(NULL, ",");
    strncpy(clientes[i].morada.rua, token, STRING_MAX);
    token = strtok(NULL, ",");
    strncpy(clientes[i].morada.cidade, token, STRING_MAX);
    token = strtok(NULL, ",");
    clientes[i].data_nascimento.dia = (atoi(token));
    token = strtok(NULL, ",");
    clientes[i].data_nascimento.mes = (atoi(token));
    token = strtok(NULL, ",");
    clientes[i].data_nascimento.ano = (atoi(token));
    token = strtok(NULL, ",");
    strncpy(clientes[i].email, token, STRING_MAX);
    token = strtok(NULL, ",");
    clientes[i].NIF = (atoi(token));
    token = strtok(NULL, ",");
    clientes[i].SNS = (atoi(token));
    token = strtok(NULL, ",");
    clientes[i].estado = (strcmp(token, "Ativo") == 0);
    i++;
  }
  fclose(ficheiro);
  return;
}

void atualizarFicheiroCliente(ST_CLIENTE *clientes){
  FILE *ficheiro;
  ficheiro = fopen("data/clientes.txt", "w");
  if (ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  for (int i = 0; i < numeroClientes(clientes); i++){
   fprintf(ficheiro, "%u,%s,%lu,%s,%s,%2u,%2u,%4u,%s,%9lu,%9lu,%s\n", clientes[i].ID, clientes[i].nome, clientes[i].morada.codigo_postal, clientes[i].morada.rua, clientes[i].morada.cidade, clientes[i].data_nascimento.dia, clientes[i].data_nascimento.mes, clientes[i].data_nascimento.ano, clientes[i].email, clientes[i].NIF, clientes[i].SNS, clientes[i].estado ? "Ativo" : "Inativo");
  }
  fclose(ficheiro);
  return;
}
