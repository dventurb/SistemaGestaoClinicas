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
   ficheiro = fopen("data/codigos_postais.txt", "r");
   if (ficheiro == NULL){
    printf("Erro\n");
    return;
   }
    printf("Código Postal (1234567): ");
    scanf("%lu", &codigo_postal);
    limparBuffer();
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
     printf("Código postal não encontrado.\a\n");
   }
   fclose(ficheiro);
   return;
 }

void obterEspecialidade(ST_MEDICO *medico){
  FILE *ficheiro;
  char linha[20], especialidade[20];
  int opcao;
  ficheiro = fopen("data/especialidade.txt", "r");
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
            printf("Especialidade não é válida.\a\n");
          }
        }while(especialidade_valida != 1);
        break;
      default:
        printf("Opção inválida!\a\n");
        break;
    }
  }while(opcao != 2);
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
  delay(10);
  return;
}