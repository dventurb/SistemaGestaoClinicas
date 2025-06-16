// BIBLIOTECAS
#include "cliente.h"

// FUNÇÕES CLIENTES
void inserirClientes(ST_CLIENTE *clientes){
  int opcao = 2, tecla;
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
    //obterMorada(&cliente);
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
      clear();
      printf("Deseja confirmar inserção do cliente?\n   [%s%s] - SIM   [%s%s] - NÃO", (opcao == 1) ? GREEN "X" : "", RESET, (opcao == 2) ? GREEN "X" : "", RESET);
      tecla = getKey();
      selecionarOpcao(&opcao, tecla);
    } while((opcao != 1 && opcao!= 2) || tecla != 10);
    if (opcao == 1){
      clear();
      confirmarClientes(clientes, cliente);
      inserirFicheiroCliente(cliente);
      printf("Cliente inserido com sucesso.\n");
      delay(1);
    }
  }
}

void alterarDadosClientes(ST_CLIENTE *clientes){
  int ID, opcao = 1, tecla;
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
    printf("%s%sNome\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sCódigo Postal\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sData de nascimento\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    printf("%s%sE-Mail\n", (opcao == 4) ? GREEN "▶" : "", RESET);
    printf("%s%sNIF\n", (opcao == 5) ? GREEN "▶" : "", RESET);
    printf("%s%sSNS\n", (opcao == 6) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 7) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch(opcao){
        case 1:
          clear();
          printf("Nome: ");
          fgets(cliente->nome, STRING_MAX, stdin);
          cliente->nome[strcspn(cliente->nome, "\n")] = '\0';
          break;
        case 2:
          //obterMorada(cliente);
          printf("Rua: %s\n", cliente->morada.rua);
          printf("Cidade: %s\n", cliente->morada.cidade);
          delay(1);
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
        case 7:
          atualizarFicheiroCliente(clientes);
          return;
      }
    }
    navegarMenu(&opcao, tecla, 7);
  }while(opcao != 7 || tecla != 10);
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

int obterListaClientesAtivos(ST_CLIENTE *clients, ST_CLIENTE **clients_found) {
  int counter = 0;
  *clients_found = NULL;

  for (int i = 0; i < numberOf(clients, TYPE_CLIENTS); i++){
    if(clients[i].estado) {
      ST_CLIENTE *tmp = realloc(*clients_found, (counter + 1) * sizeof(ST_CLIENTE));
      if(!tmp) {
        free(*clients_found);
        *clients_found = NULL;
        return 0;
      }
      *clients_found = tmp;
      (*clients_found)[counter] = clients[i];
      counter++;
    }
  }
  return counter;
}

ST_CLIENTE *procurarClientesID(ST_CLIENTE *clients, unsigned int id) {
  for (int i = 0; i < numeroClientes(clients); i++) {
    if(id == clients[i].ID) {
      return &clients[i];
    }
  }
  return NULL;
}

ST_CLIENTE *procurarClientesEmail(ST_CLIENTE *clients, const char *email) {
  for (int i = 0; i < numeroClientes(clients); i++) {
    if(strcmp(email, clients[i].email) == 0) {
      return &clients[i];
    }
  }
  return NULL;
}

ST_CLIENTE *procurarClientesNIF(ST_CLIENTE *clients, unsigned int nif) {
  for (int i = 0; i < numeroClientes(clients); i++) {
    if(nif == clients[i].NIF) {
      return &clients[i];
    }
  }
  return NULL;
}

ST_CLIENTE *procurarClientesSNS(ST_CLIENTE *clients, unsigned int sns) {
  for (int i = 0; i < numeroClientes(clients); i++) {
    if(sns == clients[i].SNS) {
      return &clients[i];
    }
  }
  return NULL;
}

int procurarClientesNome(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *name){
  int counter = 0;
  *clients_found = NULL;
 
  // Converter first char to uppercase
  char cmp[STRING_MAX];
  strncpy(cmp, name, STRING_MAX - 1);
  cmp[STRING_MAX - 1] = '\0';
  cmp[0] = toupper(cmp[0]);

  for (int i = 0; i < numeroClientes(clients); i++){
    if (strncmp(clients[i].nome, cmp, 2) == 0){
      ST_CLIENTE *temp = realloc(*clients_found, (counter + 1) * sizeof(ST_CLIENTE));
      if(!temp) {
        free(*clients_found);
        *clients_found = NULL;
        return 0;
      }
      *clients_found = temp;

      (*clients_found)[counter] = clients[i];
      counter++;
    }
  }
  return counter;
}

int procurarClientesData(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *data) {
  int counter = 0;
  *clients_found = NULL;
  
  unsigned int day, month, year;
  sscanf(data, "%02u-%02u-%04u", &day, &month, &year);

  for(int i = 0; i < numeroClientes(clients); i++) {
    if(clients[i].data_nascimento.dia == day && clients[i].data_nascimento.mes == month && clients[i].data_nascimento.ano == year) {
      ST_CLIENTE *temp = realloc(*clients_found, (counter + 1) * sizeof(ST_CLIENTE));
      if(!temp) {
        free(*clients_found);
        *clients_found = NULL;
        return 0;
      }
      *clients_found = temp;
      (*clients_found)[counter] = clients[i];
      counter++;
    }
  }
  return counter;
}

int procurarClientesCodigoPostal(ST_CLIENTE *clients, ST_CLIENTE **clients_found, const char *input) {
  int counter = 0;
  *clients_found = NULL;

  for(int i = 0; i < numeroClientes(clients); i++) {
    if(clients[i].morada.codigo_postal == strtoul(input, NULL, 10)) {
      ST_CLIENTE *temp = realloc(*clients_found, (counter + 1) * sizeof(ST_CLIENTE));
      if(!temp) {
        free(*clients_found);
        *clients_found = NULL;
        return 0;
      }
      *clients_found = temp;
      (*clients_found)[counter] = clients[i];
      counter++;
    }
  }
  return counter;
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
  printf("Data de Nascimento: %02u-%02u-%04u\n", clientes.data_nascimento.dia, clientes.data_nascimento.mes, clientes.data_nascimento.ano);
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
  fprintf(ficheiro, "%u,%s,%lu,%s,%s,%02u,%02u,%04u,%s,%9lu,%9lu,%s\n", cliente.ID, cliente.nome, cliente.morada.codigo_postal, cliente.morada.rua, cliente.morada.cidade, cliente.data_nascimento.dia, cliente.data_nascimento.mes, cliente.data_nascimento.ano, cliente.email, cliente.NIF, cliente.SNS, cliente.estado ? "Ativo" : "Inativo");
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
   fprintf(ficheiro, "%u,%s,%lu,%s,%s,%02u,%02u,%04u,%s,%9lu,%9lu,%s\n", clientes[i].ID, clientes[i].nome, clientes[i].morada.codigo_postal, clientes[i].morada.rua, clientes[i].morada.cidade, clientes[i].data_nascimento.dia, clientes[i].data_nascimento.mes, clientes[i].data_nascimento.ano, clientes[i].email, clientes[i].NIF, clientes[i].SNS, clientes[i].estado ? "Ativo" : "Inativo");
  }
  fclose(ficheiro);
  return;
}
