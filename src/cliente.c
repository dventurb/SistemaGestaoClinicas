// BIBLIOTECAS
#include "cliente.h"

// FUNÇÕES CLIENTES
void inserirClientes(ST_CLIENTE *clientes){
  int opcao;
  if(numeroClientes(clientes) >= MAX_CLIENTES){
    printf("Número máximo de clientes atingido!\n");
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
        delay(1);
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
    delay(1);
    return;
  }
  clientes[ID - 1].estado = !clientes[ID - 1].estado;
  printf("Cliente %s com sucesso.\n", clientes[ID - 1].estado ? "ativado" : "desativado");
  delay(1);
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
    delay(1);
    return;
  }
  clear();
  infoClientes(clientes[ID - 1]);
  delay(10);
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
    printf("Não existe clientes ativos.\n");
    delay(1);
    return;
  }
  delay(10);
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
    clear();
    printf("Não existe clientes com o nome.\n");
    delay(1);
    return;
  }
  delay(10);
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
  printf("Código Postal: %ld | Rua: %s | Cidade: %s\n", clientes.morada.codigo_postal, clientes.morada.rua, clientes.morada.cidade);
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
