// BIBLIOTECAS
#include "funcionario.h"

// FUNÇÕES FUNCIONARIOS 
bool authValidate(ST_FUNCIONARIO *staff, const char *username, const char *password) {
  for (int i = 0; i < numberOf(staff, TYPE_STAFF); i++) {
    if(strcmp(staff[i].username, username) == 0) {
      struct crypt_data data = {0};
      const char *hash = crypt_rn(password, staff[i].password, &data, sizeof(data));
      
      if(strcmp(staff[i].password, hash) == 0) {
        return true;
      }
    }
  }
  return false;
}

bool usernameValidate(ST_FUNCIONARIO *staff, const char *username) {
  for (int i = 0; i < numberOf(staff, TYPE_STAFF); i++) {
    if(strcmp(staff[i].username, username) == 0) {
      return false;
    }
  }
  return true;
}

bool encryptPassword(ST_FUNCIONARIO *new, const char *password) {
  struct crypt_data data = {0};

  char salt[16];
  generateSalt(salt, sizeof(salt));

  char full[20];
  snprintf(full, sizeof(full), "$5$%s", salt); // $5$ -> SHA-256 

  char *output = crypt_rn(password, full, &data, sizeof(data));
  if(!output) {
    return false;
  }

  strncpy(new->password, output, PASSWORD_MAX - 1);
  new->password[PASSWORD_MAX - 1] = '\0';

  return true;
} 

void createUser(ST_FUNCIONARIO *staff, ST_FUNCIONARIO new) {
  staff[numberOf(staff, TYPE_STAFF)] = new;
}

ST_FUNCIONARIO *getCurrentUser(ST_FUNCIONARIO *staff, const char *username) {
  for(int i = 0; i < numberOf(staff, TYPE_STAFF); i++) {
    if(strcmp(staff[i].username, username) == 0) {
      return &staff[i];
    }
  }
  return NULL;
} 

void insertUserFile(ST_FUNCIONARIO *new) {
  FILE *file = fopen("data/staff.txt", "a");
  if(!file) {
    return;
  }

  fprintf(file, "%u,%s,%s,%s,%s\n", new->ID, new->nome, new->username, new->password, new->pathToImage);
  fclose(file);
}

void loadUserFile(ST_FUNCIONARIO *staff) {
  FILE *file = fopen("data/staff.txt", "r");
  if(!file) {
    return;
  }

  char row[1024];
  int i = 0;
  while(fgets(row, sizeof(row), file) && i < MAX_FUNCIONARIOS) {
    row[strcspn(row, "\n")] = '\0';

    char *token = strtok(row, ",");
    staff[i].ID = strtoul(token, NULL, 10);

    token = strtok(NULL, ",");
    strncpy(staff[i].nome, token, STRING_MAX - 1);
    staff[i].nome[STRING_MAX - 1] = '\0';

    token = strtok(NULL, ",");
    strncpy(staff[i].username, token, STRING_MAX - 1);
    staff[i].username[STRING_MAX - 1] = '\0';

    token = strtok(NULL, ",");
    strncpy(staff[i].password, token, PASSWORD_MAX - 1);
    staff[i].password[PASSWORD_MAX - 1] = '\0';
    
    token = strtok(NULL, ",");
    strncpy(staff[i].pathToImage, token, STRING_MAX - 1);
    staff[i].pathToImage[STRING_MAX - 1] = '\0';

    i++;
  }

  fclose(file);
}

void updateUserFile(ST_FUNCIONARIO *staff) {
  FILE *file;
  file = fopen("data/staff.txt", "w");
  if(!file) {
    return;
  }

  for(int i = 0; i < numberOf(staff, TYPE_STAFF); i++) {
    fprintf(file, "%u,%s,%s,%s,%s\n", staff[i].ID, staff[i].nome, staff[i].username, staff[i].password, staff[i].pathToImage);
  }
  fclose(file);
}
