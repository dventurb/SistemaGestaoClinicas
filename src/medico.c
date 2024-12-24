// BIBLIOTECAS
#include "medico.h"

// FUNÇÕES MÉDICOS
void inserirMedicos(ST_MEDICO *medicos){
  int opcao;
  if(numeroMedicos(medicos) >= MAX_MEDICOS){
    printf("Número máximo de médicos atingido!\n");
    delay(1);
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
    delay(1);
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
        delay(1);
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
    delay(1);
    return;
  }
  medicos[ID - 1].estado = !medicos[ID - 1].estado;
  printf("Médico %s com sucesso.\n", medicos[ID - 1].estado ? "Disponível" : "Indisponível");
  delay(1);
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
    delay(1);
    return;
  }
  clear();
  infoMedicos(medicos[ID - 1]);
  delay(10);
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
    clear();
    printf("Não há médicos registados.\n");
    delay(1);
    return;
  }
  delay(10);
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
    clear();
    printf("Não há médicos disponíveis.\n");
    delay(1);
    return;
  }
  delay(10);
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
    clear();
    printf("Não há medicos com a especialidade %s.\n", especialidade);
    delay(1);
    return;
  }
  delay(10);
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
    clear();
    printf("Não há médicos com o nome %s.\n", nome);
    delay(1);
    return;
  }
  delay(10);
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