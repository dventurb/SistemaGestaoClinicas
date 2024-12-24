// BIBLIOTECAS
#include "menu.h"

// MAIN 
int main(){
    ST_CLIENTE clientes[MAX_CLIENTES];
    ST_MEDICO medicos[MAX_MEDICOS];
    ST_CONSULTA consultas[MAX_CONSULTAS];
    menuPrincipal(clientes, medicos, consultas);   
    return 0;
}