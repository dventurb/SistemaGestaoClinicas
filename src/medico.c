// BIBLIOTECAS
#include "medico.h"

// FUNÇÕES MÉDICOS
int obterListaMedicosAtivos(ST_MEDICO *doctors, ST_MEDICO **doctors_active){
  int counter = 0;
  *doctors_active = NULL;

  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++){
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
  return counter;
}

ST_MEDICO *procurarMedicosID(ST_MEDICO *doctors, unsigned int id) {
  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    if(doctors[i].ID == id) {
      return &doctors[i];
    }
  }
  return NULL;
}

ST_MEDICO *procurarMedicosEmail(ST_MEDICO *doctors, const char *email) {
  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    if(strcmp(doctors[i].email, email) == 0) {
      return &doctors[i];
    }
  }
  return NULL;
}

ST_MEDICO *procurarMedicosLicenseNumber(ST_MEDICO *doctors, unsigned int cedula) {
  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    if(doctors[i].cedula == cedula) {
      return &doctors[i];
    }   
  }
  return NULL;
}

int procurarMedicosNome(ST_MEDICO *doctors, ST_MEDICO **doctors_found, const char *name) {
  int counter = 0;
  *doctors_found = NULL;

  const char *cmp = convertToUppercase(name);

  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    if (strncmp(doctors[i].nome, cmp, 2) == 0) {
      ST_MEDICO *temp = realloc(*doctors_found, (counter + 1) * sizeof(ST_MEDICO));
      if(!temp) {
        free(*doctors_found);
        *doctors_found = NULL;
        return 0;
      }
      *doctors_found = temp;

      (*doctors_found)[counter] = doctors[i];
      counter++;
    } 
  }
  return counter;
}

int procurarMedicosEspecialidade(ST_MEDICO *doctors, ST_MEDICO **doctors_found, const char *speciality) {
  int counter = 0;
  *doctors_found = NULL;

  const char *cmp = convertToUppercase(speciality);

  for(int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    if (strncmp(doctors[i].especialidade, cmp, 2) == 0) {
      ST_MEDICO *temp = realloc(*doctors_found, (counter + 1) * sizeof(ST_MEDICO));
      if(!temp) {
        free(*doctors_found);
        *doctors_found = NULL;
        return 0;
      }
      *doctors_found = temp;
      (*doctors_found)[counter] = doctors[i];
      counter++;
    }
  }
  return counter;
}

void confirmarMedicos(ST_MEDICO *medicos, ST_MEDICO medico){
  medicos[numberOf(medicos, TYPE_DOCTORS)] = medico;
}

void inserirFicheiroMedico(ST_MEDICO medico){
  FILE *ficheiro = fopen("data/medicos.txt", "a");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  fprintf(ficheiro, "%u,%s,%s,%u,%s,%s\n", medico.ID, medico.nome, medico.email, medico.cedula, medico.especialidade, medico.estado ? "Disponível" : "Indisponível");
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
    medicos[i].ID = atoi(token);
    token = strtok(NULL, ",");
    strncpy(medicos[i].nome, token, STRING_MAX - 1);
    medicos[i].nome[STRING_MAX - 1] = '\0';
    token = strtok(NULL, ",");
    strncpy(medicos[i].email, token, STRING_MAX - 1);
    medicos[i].email[STRING_MAX - 1] = '\0';
    token = strtok(NULL, ",");
    medicos[i].cedula = atoi(token);
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
  for (int i = 0; i < numberOf(medicos, TYPE_DOCTORS); i++){
    fprintf(ficheiro, "%u,%s,%s,%u,%s,%s\n", medicos[i].ID, medicos[i].nome, medicos[i].email, medicos[i].cedula, medicos[i].especialidade, medicos[i].estado ? "Disponível" : "Indisponível");
  }
  fclose(ficheiro);
  return;
}
