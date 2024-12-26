/* Este ficheiro foi implementado durante a realização de um projeto de desenvolvimento de um sistema de gestão de clínicas parte da disciplina de Algoritmia e Programação.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codigoPostal(int codigo);

int main(){
    int cod_postal, num_cod_postal, ext_cod_postal;

    printf("Código Postal (1234-567): ");
    scanf("%d-%d", &num_cod_postal, &ext_cod_postal);
    getchar();
    
    cod_postal = (num_cod_postal * 1000) + ext_cod_postal;
    codigoPostal(cod_postal);  
    return 0;
}

void codigoPostal(int codigo){
    FILE *ficheiro;
    char linha[1024];
    char *token;
    int encontrado = 0;
    ficheiro = fopen("data/codigos_postais.txt", "r");
    if (ficheiro == NULL){
        printf("Erro ao abrir.\n");
    }else {
        while (!feof(ficheiro)){ 
        fgets(linha, sizeof(linha), ficheiro);
        token = strtok(linha, ",");
        char *tokens[100];
        int total_tokens = 0;
        while(token != NULL){
            tokens[total_tokens] = token;
            total_tokens++;
            token = strtok(NULL, ",");
        }
        if (total_tokens >= 3 && tokens[total_tokens - 3] != NULL && tokens[total_tokens - 2] != NULL){ 
            int num = (atoi(tokens[total_tokens - 3]) * 1000) + atoi(tokens[total_tokens -2]);
            if (num == codigo){
                printf("\nEncontrado!\n");
                printf("Rua: %s\n", tokens[3]);
                printf("Cidade: %s", tokens[total_tokens - 1]);
                printf("Código-Postal: %s-%s\n", tokens[total_tokens - 3], tokens[total_tokens - 2]);
                encontrado = 1;
                break;
            }
        }
    }
    }
    fclose(ficheiro);
    if(!encontrado){
        printf("Não foi encontrado!\n");
    }
}
