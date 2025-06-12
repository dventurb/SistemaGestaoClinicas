// BIBLIOTECAS
#include "auxiliares.h"

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
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

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
   ficheiro = fopen("data/codigos_postais.txt", "r");
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
        strcpy(cliente->morada.cidade, tokens[total_tokens - 1]);
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

void obterEspecialidade(ST_MEDICO *medico){
  FILE *ficheiro;
  char linha[20], especialidade[20];
  int opcao = 1, tecla;
  ficheiro = fopen("data/especialidade.txt", "r");
  if (ficheiro == NULL){
    printf("Erro\n");
    return;
  }
  clear();
  do { 
    clear();
    printf("%s%sObter uma lista das especialidades\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sInserir a especialidade do médico\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
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
            especialidade[0] = toupper(especialidade[0]);
            rewind(ficheiro);
            while (fgets(linha, sizeof(linha), ficheiro)){
              linha[strcspn(linha, "\n")] = '\0';
              if(strncmp(especialidade, linha, 5) == 0){
                strcpy(medico->especialidade, linha);
                especialidade_valida = 1;
                break;
              }
            }
            if (!especialidade_valida){
              printf("Especialidade não é válida.\a\n");
            }
          }while(especialidade_valida != 1);
          break;
      }
    }
    navegarMenu(&opcao, tecla, 2);
  }while((opcao != 2) || tecla != 10);
  fclose(ficheiro);
  return;
}

void listarEspecialidades(void){
  FILE *ficheiro;
  char linha[20];
  ficheiro = fopen("data/especialidade.txt", "r");
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
  pressionarEnter();
  return;
}

void pressionarEnter(void){
  printf("\nPressionar Enter para sair.\n");
  while (getchar() != '\n');
}

void navegarMenu(int *opcao, int tecla, int n){
  #ifdef _WIN32
    if(tecla == 224){
      tecla = getKey();
      if (tecla == 72){        // Tecla seta de cima
        *opcao = (*opcao == 1) ? 1 : (*opcao - 1);
      }else if (tecla == 80){  // Tecla seta de baixo
        *opcao = (*opcao == n) ? n : (*opcao + 1);
      }
    }
#else 
    if(tecla == 27){
      if(getKey() == 91){
        tecla = getKey();
        if(tecla == 65){       // Tecla seta de cima
          *opcao = (*opcao == 1) ? 1 : (*opcao - 1);
        }else if(tecla == 66){  // Tecla seta de baixo
          *opcao = (*opcao == n) ? n : (*opcao + 1); 
        }
      }
    }
#endif
}

void selecionarOpcao(int *opcao, int tecla){
  #ifdef _WIN32
    if(tecla == 224){
      tecla = getKey();
      if(tecla == 75){
        *opcao = (*opcao == 1) ? 1 : (*opcao - 1);
      }else if(tecla == 77){
        *opcao = (*opcao == 2) ? 2 : (*opcao + 1);
      }
    }
  #else
    if(tecla == 27){
      if(getKey() == 91){
        tecla = getKey();
        if(tecla == 68){
          *opcao = (*opcao == 1) ? 1 : (*opcao - 1);
        }else if (tecla == 67){
          *opcao = (*opcao == 2) ? 2 : (*opcao + 1);
        }
      }
    }
#endif
}

int getKey(void){
  #ifdef _WIN32
    int ch;
    ch = _getch();
    if (ch == 13){   // Enter em sistemas Windows
      return 10;
    }else{
      return ch;
    }
  #else
    struct termios old, new;  // old - Configurações antigas; new - Configurações novas
    int ch;
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ECHO | ICANON);  // Desativar exibição do stdin e necessidade do Enter
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
  #endif
}

void ativarDesativarCursor(int n){
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(hConsole, &cursorInfo);
  cursorInfo.bVisible = (n != 0);
  setConsoleCursorInfo(hConsole, &cursorInfo);
#else 
  if(n == 0){
    printf("\e[?25l");
  }else {
    printf("\e[?25h");
  }
#endif
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
  
  ST_DATA data_atual;
  dataAtual(&data_atual);

  if(ano < 1900) return false;
  if(mes < 1 || mes > 12) return false;
  if(dia < 1 || dia > 31) return false;
  
  if(ano > data_atual.ano || (ano == data_atual.ano && mes > data_atual.mes) ||
    (ano == data_atual.ano && dia > data_atual.dia)) {
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
  * @brief Validates an email format and check for duplicates in clients. 
  *
  * @param email    The email to validate.
  * @param clients  Pointer to the ST_CLIENTE struct. 
  * 
  * @note Requires the regex lib (regex.h). 
  * 
*/
bool validarEmail(const char *email, ST_CLIENTE *clients) {
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

  for(int i = 0; i < numeroClientes(clients); i++) {
    if(strcmp(email, clients[i].email) == 0) {
      return false;
    }
  }

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
