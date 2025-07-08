// BIBLIOTECAS
#include "auxiliares.h"

// FUNÇÕES AUXILIARES
 void dataAtual(ST_DATA *data_hora_atual){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   data_hora_atual->hora = tm.tm_hour;
   data_hora_atual->dia = tm.tm_mday;
   data_hora_atual->mes = tm.tm_mon + 1;
   data_hora_atual->ano = tm.tm_year + 1900; 
 }

 bool obterMorada(ST_CLIENTE *cliente, long unsigned int codigo_postal){
   FILE *ficheiro;
   char linha[1024], *token;
   int encontrados = 0;
   ficheiro = fopen("data/codigos_postais.csv", "r");
   if (ficheiro == NULL){
    printf("Erro\n");
    return false;
   }
    while (fgets(linha, sizeof(linha), ficheiro)){
     token = strtok(linha, ",");
     char *tokens[20];
     int total_tokens = 0;
     while(token != NULL){
       tokens[total_tokens] = token;
       total_tokens++;
       token = strtok(NULL, ",");
     }
    if (total_tokens >= 3 && tokens[total_tokens - 3] != NULL && tokens[total_tokens - 2] != NULL){
      unsigned long int cod_postal = (atoi(tokens[total_tokens - 3]) * 1000) + atoi(tokens[total_tokens - 2]);
      if(cod_postal == codigo_postal){
        encontrados++;
        strcpy(cliente->morada.rua, tokens[3]);
        cliente->morada.rua[strcspn(cliente->morada.rua, "\n")] = '\0';

        strcpy(cliente->morada.cidade, obterCidade(atoi(tokens[0]), atoi(tokens[1])));
        cliente->morada.cidade[strcspn(cliente->morada.cidade, "\n")] = '\0';
        cliente->morada.codigo_postal = codigo_postal;
        break;
      }
    }
   }
   if(!encontrados){
      fclose(ficheiro);
      return false; 
   }

   fclose(ficheiro);
   return true;
 }

const char *obterCidade(int cod_distrito, int cod_concelho) {
  FILE *file;
  char row[128];
  char *token;

  file = fopen("data/concelhos.csv", "r");
  if(!file) {
    return NULL;
  }
  
  while(fgets(row, sizeof(row), file)) {
    token = strtok(row, ",");
    
    char **tokens = malloc(3 * sizeof(char *));
    if(!tokens) {
      return NULL;
    }

    int total = 0;

    while(token != NULL && total < 3) {
      tokens[total] = strdup(token);
      total++;
      token = strtok(NULL, ",");
    }
    if(atoi(tokens[0]) == cod_distrito && atoi(tokens[1]) == cod_concelho && total == 3) {
      char *city = strdup(tokens[2]);

      for(int i = 0; i < total; i++) {
        free(tokens[i]);
      }
      free(tokens);
      fclose(file);
      
      return city;
    }

    for(int i = 0; i < total; i++) {
      free(tokens[i]);
    }
    free(tokens);
  }
  fclose(file);
  return NULL;
}

/** 
 * @brief Returns the total number of elements in a given data.
 *
 *  @param data  A pointer to the array of structs (ST_CLIENTE, ST_MEDICO, ST_CONSULTA).
 *  @param type  The type of data to check (TYPE_CLIENTS, TYPE_DOCTORS, TYPE_APPOINTMENTS). 
 *
 *  @return The number of elements in a given data.
 *
*/
int numberOf(void *data, TYPE_STRUCT type) {
  int i = 0;

  switch (type) {
    case TYPE_CLIENTS:
      ST_CLIENTE *clients = (ST_CLIENTE *)data;
      while (clients[i].ID != 0){
        i++;
      }
      return i;
    case TYPE_DOCTORS:
      ST_MEDICO *doctors = (ST_MEDICO *)data;
      while (doctors[i].ID != 0) {
        i++;
      }
      return i;
    case TYPE_APPOINTMENTS:
      ST_CONSULTA *appointments = (ST_CONSULTA *)data;
      while (appointments[i].ID != 0) {
        i++;
      }
      return i;
    case TYPE_STAFF:
      ST_FUNCIONARIO *staff = (ST_FUNCIONARIO *)data;
      while(staff[i].ID != 0) {
        i++;
      }
      return i;
    default:
      return 0;
  }
}

bool validarFormatoData(const char *data) {
  unsigned int dia, mes, ano;

  if(strlen(data) != 10) return false;

  for(int i = 0; i < 10; i++) {
    if(i == 2 || i == 5) {
      if(data[i] != '-') return false;
    }else {
      if(!isdigit((unsigned char)data[i])) {
        return false;
      }
    }
  }
  
  sscanf(data, "%02u-%02u-%04u", &dia, &mes, &ano);
  
  if(ano < 1900) return false;
  if(mes < 1 || mes > 12) return false;
  if(dia < 1 || dia > 31) return false;
  
  return true; 
}

bool validarData(const char *data) {  
  unsigned int dia, mes, ano;

  sscanf(data, "%02u-%02u-%04u", &dia, &mes, &ano);
  
  ST_DATA data_atual;
  dataAtual(&data_atual);
  
  if(ano > data_atual.ano || (ano == data_atual.ano && mes > data_atual.mes) ||
    (ano == data_atual.ano && mes == data_atual.mes && dia >= data_atual.dia )) {
    return false;
  }
  
  return true;
}

bool validarCodigoPostal(const char *codigo_postal) {
  if(strlen(codigo_postal) != 7) return false;

  for(int i = 0; i < 7; i++) {
    if(!isdigit((unsigned char)codigo_postal[i])) return false;
  }
  return true;
}

/** 
  * @brief Validates an email format and check for duplicates in clients or doctors. 
  *
  * @param email    The email to validate.
  * @param data     Pointer to the array of structs (ST_CLIENTE or ST_MEDICO).
  * @param type     Type of data to check (TYPE_CLIENTS or TYPE_DOCTORS).
  * 
  * @note Requires the regex lib (regex.h). 
  * 
*/
bool validarEmail(const char *email, void *data, TYPE_STRUCT type) {
  switch (type) {
    case TYPE_CLIENTS:
      ST_CLIENTE *clients = (ST_CLIENTE *)data;
      for(int i = 0; i < numberOf(clients, type); i++) {
        if(strcmp(email, clients[i].email) == 0) {
          return false;
        }
      }
      break;
    case TYPE_DOCTORS:
      ST_MEDICO *doctors = (ST_MEDICO *)data;      
      for(int i = 0; i < numberOf(doctors, type); i++) {
        if(strcmp(email, doctors[i].email) == 0) {
          return false;
        }
      }
      break;
    case TYPE_APPOINTMENTS:
      return false;
    default:
      return false;
  }
  const char *email_regex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

  regex_t regex;
  int reti = regcomp(&regex, email_regex, REG_EXTENDED);
  if(reti) {
    return false;
  }

  reti = regexec(&regex, email, 0, NULL, 0);
  
  if(reti == REG_NOMATCH) {
    regfree(&regex);
    return false;
  }else if(reti) {
    regfree(&regex);
    return false;
  }
  regfree(&regex);



  return true;
}

/** 
  * @brief Validates an NIF number and check for duplicates in clients. 
  *
  * The NIF is a 9-digit number where the last digit is a checksum,
  * calculated from the first 8 digits using modulo 11: 
  * d1 * 9 + d2 * 8 + d3 * 7 + d4 * 6 + ... + d8 * 2
  *
  * @param nif      NIF to validate.
  * @param clients  Pointer to the ST_CLIENTE struct. 
  * 
*/
bool validarNIF(const char *nif, ST_CLIENTE *clients) {
  if(strlen(nif) != 9) {
    return false;
  }

  for(int i = 0; i < 9; i++) {
    if(!isdigit((unsigned char)nif[i])) return false;
  }

  for(int i = 0; i < numeroClientes(clients); i++) {
    char str[10];
    snprintf(str, sizeof(str), "%lu", clients[i].NIF);

    if(strcmp(nif, str) == 0) {
      return false;
    }
  }
  
  
  int digit[8] = {9, 8, 7, 6, 5, 4, 3, 2 };
  int sum = 0;
  for(int i = 0; i < 8; i++) {
    sum += (nif[i] - '0') * digit[i];
  }

  int remainer = sum % 11;
  int checksum = (remainer == 0 || remainer == 1) ? 0 : 11 - remainer;

  if((11 - remainer) != (nif[8] - '0')) {
    return false;
  }

  return true;
}

/** 
  * @brief Validates an SNS number and check for duplicates in clients. 
  *
  * @param sns      SNS to validate.
  * @param clients  Pointer to the ST_CLIENTE struct. 
  * 
*/
bool validarSNS(const char *sns, ST_CLIENTE *clients) {
  if(strlen(sns) != 9) {
    return false;
  }

  for(int i = 0; i < 9; i++) {
    if(!isdigit((unsigned char)sns[i])) return false;
  }

  for(int i = 0; i < numeroClientes(clients); i++) {
    char str[10];
    snprintf(str, sizeof(str), "%lu", clients[i].SNS);

    if(strcmp(sns, str) == 0) {
      return false;
    }
  }

  return true;
}

/** 
  * @brief Validates the license number and check for duplicates in doctors. 
  * 
  * @param input      The input string.
  * @param doctors    Pointer to the ST_MEDICO struct.
  *
  *
*/
bool validarLicenseNumber(const char *license_number, ST_MEDICO *doctors) {
  if(strlen(license_number) != 6) {
    return false;
  }

  for (int i = 0; i < 6; i++) {
    if(!isdigit((unsigned char)license_number[i])) return false;
  }

  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    char str[7];
    snprintf(str, sizeof(str), "%u", doctors[i].cedula);

    if(strcmp(license_number, str) == 0) {
      return false;
    }
  }

  return true;
}



/** 
  * @brief Converts the first letter of each word in uppercase.
  * 
  * @param input   The input string.
  * @return        The modified string.
  *
*/
const char *convertToUppercase(const char *input) {
  char *upper = malloc(STRING_MAX);
  if(!upper) {
    return NULL;
  }

  strncpy(upper, input, STRING_MAX - 1);
  upper[STRING_MAX - 1] = '\0';
  upper[0] = toupper(upper[0]);

  for(int i = 1; upper[i] != '\0'; i++) {
    if(isspace(upper[i-1])) {
      upper[i] = toupper(upper[i]); 
    }else {
      upper[i] = tolower(upper[i]);  
    }
  }
  return upper;
}

void generateSalt(char *string, size_t length) {
  const char alphanum[] =
  "0123456789"
  "!@#$%^&*"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";

  int len = sizeof(alphanum) - 1;
  
  for (size_t i = 0; i < length - 1; i++) {
    string[i] = alphanum[rand() % len];
  }
  string[length - 1] = '\0';
}
