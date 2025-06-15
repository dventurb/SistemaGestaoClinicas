// BIBLIOTECAS
#include "medico.h"

// FUNÇÕES MÉDICOS
void inserirMedicos(ST_MEDICO *medicos){
  int opcao = 2, tecla;
  if(numeroMedicos(medicos) >= MAX_MEDICOS){
    printf("Número máximo de médicos atingido!\a\n");
    delay(1);
    return;
  }else {
    clear();
    ST_MEDICO medico;
    medico.ID = numeroMedicos(medicos) + 1;
    printf("Nome do médico: ");
    fgets(medico.nome, STRING_MAX, stdin);
    medico.nome[strcspn(medico.nome, "\n")] = '\0';
    medico.nome[0] = toupper(medico.nome[0]);
    obterEspecialidade(&medico);
    medico.estado = true;

    do {
      clear();
      printf("Deseja confirmar inserção do médico?\n   [%s%s] - SIM   [%s%s] - NÃO\n", (opcao == 1) ? GREEN "X" : "", RESET, (opcao == 2) ? GREEN "X" : "", RESET);
      tecla = getKey();
      selecionarOpcao(&opcao, tecla);
    }while((opcao!= 1 && opcao != 2) || tecla != 10);
    if(opcao == 1){
      clear();
      confirmarMedicos(medicos, medico);
      inserirFicheiroMedico(medico);
      printf("Médico inserido com sucesso.\n");
      delay(1);
    }
  }
}

void alterarDadosMedicos(ST_MEDICO *medicos){
  int ID, opcao = 1, tecla;
  clear();
  printf("ID do médico: ");
  scanf("%u", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("O ID é inválido.\a\n");
    delay(1);
    return;
  }
  ST_MEDICO *medico = &medicos[ID - 1];
  do {
    clear();
    printf("%s%sNome\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sEspecialidade\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch(opcao){
        case 1:
          clear();
          printf("Nome: ");
          fgets(medico->nome, STRING_MAX, stdin);
          medico->nome[strcspn(medico->nome, "\n")] = '\0';
          medico->nome[0] = toupper(medico->nome[0]);
          printf("Nome do médico alterado com sucesso.\n");
          delay(1);
          break;
        case 2:
          obterEspecialidade(medico);
          printf("Especialidade alterada com sucesso.\n");
          delay(1);
          break;
        case 3:
          atualizarFicheiroMedico(medicos);
          return;
    }
  }
  navegarMenu(&opcao, tecla, 3);
  }while(opcao != 3 || tecla != 10);
}

void ativarDesativarMedicos(ST_MEDICO *medicos){
  int ID;
  clear();
  printf("ID do médico: ");
  scanf("%u", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("ID não é válido.\a\n");
    delay(1);
    return;
  }
  medicos[ID - 1].estado = !medicos[ID - 1].estado;
  atualizarFicheiroMedico(medicos);
  printf("Médico %s com sucesso.\n", medicos[ID - 1].estado ? "Disponível" : "Indisponível");
  delay(1);
  return;
}

void consultarDadosMedicos(ST_MEDICO *medicos){
  int ID;
  clear();
  printf("ID do médico: ");
  scanf("%u", &ID);
  limparBuffer();
  if(ID <= 0 || ID > numeroMedicos(medicos)){
    printf("ID não é válido.\a\n");
    delay(1);
    return;
  }
  clear();
  infoMedicos(medicos[ID - 1]);
  pressionarEnter();
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
    printf("Não há médicos registados.\a\n");
    delay(1);
    return;
  }
  pressionarEnter();
}

int obterListaMedicosAtivos(ST_MEDICO *doctors, ST_MEDICO **doctors_active){
  int counter = 0;
  
  *doctors_active = NULL;

  for (int i = 0; i < numeroMedicos(doctors); i++){
    if(doctors[i].estado) {
      ST_MEDICO *temp = realloc(*doctors_active, (counter + 1) * sizeof(ST_MEDICO));
      if(!temp) {
        free(*doctors_active);
        *doctors_active = NULL;
        return 0;
      }
      *doctors_active = temp;
      (*doctors_active)[counter] = doctors[i];
      counter++;
    }
  }
  return 0;
}

void obterListaMedicosEspecialidade(ST_MEDICO *medicos){
  int encontrados = 0;
  char especialidade[STRING_MAX];
  clear();
  printf("Especialidade: ");
  fgets(especialidade, STRING_MAX, stdin);
  especialidade[strcspn(especialidade, "\n")] = '\0';
  especialidade[0] = toupper(especialidade[0]);
  clear();
  printf("Lista de Médicos de %s:\n", especialidade);
  for (int i = 0; i < numeroMedicos(medicos); i++){
    if(strncmp(medicos[i].especialidade, especialidade, 2) == 0){
      infoMedicos(medicos[i]);
      printf("\n");
      encontrados++;
    }
  }
  if (!encontrados){
    clear();
    printf("Não há medicos com a especialidade %s.\a\n", especialidade);
    delay(1);
    return;
  }
  pressionarEnter();
}

void procurarMedicosNome(ST_MEDICO *medicos){
  char nome[STRING_MAX];
  int encontrados = 0;
  clear();
  printf("Nome do médico: ");
  fgets(nome, STRING_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';
  nome[0] = toupper(nome[0]);
  for (int i = 0; i < numeroMedicos(medicos); i++){
    if(strncmp(medicos[i].nome, nome, 4) == 0){
      infoMedicos(medicos[i]);
      printf("\n");
      encontrados++;
    }
  }
  if(!encontrados){
    clear();
    printf("Não há médicos com o nome %s.\a\n", nome);
    delay(1);
    return;
  }
  pressionarEnter();
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
  printf("ID: %u\n", medicos.ID);
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

void inserirFicheiroMedico(ST_MEDICO medico){
  FILE *ficheiro = fopen("data/medicos.txt", "a");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  fprintf(ficheiro, "%u,%s,%s,%s\n", medico.ID, medico.nome, medico.especialidade, medico.estado ? "Disponível" : "Indisponível");
  fclose(ficheiro);
  return;
}

void carregarFicheiroMedico(ST_MEDICO *medicos){
  char linha[1024], *token;
  int i = 0;
  FILE *ficheiro;
  ficheiro = fopen("data/medicos.txt", "r");
  if(ficheiro == NULL){
    printf("Erro\n");
    return;
  }
  while(fgets(linha, sizeof(linha), ficheiro) && i < MAX_MEDICOS){
    linha[strcspn(linha, "\n")] = '\0';
    token = strtok(linha, ",");
    medicos[i].ID = (atoi(token));
    token = strtok(NULL, ",");
    strncpy(medicos[i].nome, token, STRING_MAX);
    token = strtok(NULL, ",");
    strncpy(medicos[i].especialidade, token, STRING_MAX);
    token = strtok(NULL, ",");
    medicos[i].estado = (strcmp(token, "Disponível") == 0);
    i++;
  }
  fclose(ficheiro);
  return;
}

void atualizarFicheiroMedico(ST_MEDICO *medicos){
  FILE *ficheiro;
  ficheiro = fopen("data/medicos.txt", "w");
  if (ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  for (int i = 0; i < numeroMedicos(medicos); i++){
    fprintf(ficheiro, "%u,%s,%s,%s\n", medicos[i].ID, medicos[i].nome, medicos[i].especialidade, medicos[i].estado ? "Disponível" : "Indisponível");
  }
  fclose(ficheiro);
  return;
}
