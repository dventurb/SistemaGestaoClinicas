// BIBLIOTECAS
#include "menu.h"

// MAIN 
int main(){
    ativarDesativarCursor(0);
    ST_CLIENTE clientes[MAX_CLIENTES];
    ST_MEDICO medicos[MAX_MEDICOS];
    ST_CONSULTA consultas[MAX_CONSULTAS];
    carregarFicheiroCliente(clientes);
    carregarFicheiroMedico(medicos);
    carregarFicheiroConsulta(consultas, clientes, medicos);
    menuPrincipal(clientes, medicos, consultas);   
    return 0;
}
