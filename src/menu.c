// BIBLIOTECAS
#include "menu.h"

// FUNÇÕES MENUS
void menuPrincipal(ST_CLIENTE *clientes, ST_MEDICO *medicos, ST_CONSULTA *consultas){
  ativarDesativarCursor(0);
  int opcao = 1, tecla;
  do {
    clear();
    printf("%s%sGestão de Clientes\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sGestão de Médicos\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sGestão de Consultas\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 4) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch (opcao){
      case 1:
        menuClientes(clientes);
        break;
      case 2:
        menuMedicos(medicos);
        break;
      case 3:
        menuConsultas(consultas, clientes, medicos);
        break;
      case 4:
        return;
      }
    }else{
    navegarMenu(&opcao, tecla, 4);
    }
  } while (opcao != 4 || tecla != 10);
}

void menuClientes(ST_CLIENTE *clientes){
  int opcao = 1, tecla;
  do {
    clear();
    printf("%s%sInserir novo cliente\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sAlterar dados de um cliente\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sAtivar ou desativar um cliente\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    printf("%s%sConsultar dados de um cliente\n", (opcao == 4) ? GREEN "▶" : "", RESET);
    printf("%s%sObter uma lista de clientes ativos\n", (opcao == 5) ? GREEN "▶" : "", RESET);
    printf("%s%sProcurar um cliente pelo nome\n", (opcao == 6) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 7) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch(opcao){
        case 1:
          inserirClientes(clientes);
          break;
        case 2:
          alterarDadosClientes(clientes);
          break;
        case 3:
          ativarDesativarClientes(clientes);
          break;
        case 4:
          consultarDadosClientes(clientes);
          break;
        case 5:
          obterListaClientesAtivos(clientes);
          break;
        case 6:
          procurarClientesNome(clientes);
        case 7:
          return;
      }
    }
    navegarMenu(&opcao, tecla, 7);
  }while(opcao != 7 || tecla != 10);
}

void menuMedicos(ST_MEDICO *medicos){
  int opcao = 1, tecla;
  do {
    clear();
    printf("%s%sInserir novo médico\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sAlterar dados de um médico\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sAtivar ou desativar um médico\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    printf("%s%sConsultar dados de um médico\n", (opcao == 4) ? GREEN "▶" : "", RESET);
    printf("%s%sObter uma lista de todos os médicos\n", (opcao == 5) ? GREEN "▶" : "", RESET);
    printf("%s%sObter uma lista de médicos disponíveis\n", (opcao == 6) ? GREEN "▶" : "", RESET);
    printf("%s%sObter uma lista de médicos por especialidade\n", (opcao == 7) ? GREEN "▶" : "", RESET);
    printf("%s%sProcurar um médico pelo nome\n", (opcao == 8) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 9) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch (opcao){
        case 1:
          inserirMedicos(medicos);
          break;
        case 2:
          alterarDadosMedicos(medicos);
          break;
        case 3:
          ativarDesativarMedicos(medicos);
          break;
        case 4:
          consultarDadosMedicos(medicos);
          break;
        case 5:
          obterListaTodosMedicos(medicos);
          break;
        case 6:
          obterListaMedicosAtivos(medicos);
          break;
        case 7:
          obterListaMedicosEspecialidade(medicos);
          break;
        case 8: 
          procurarMedicosNome(medicos);
          break;
        case 9:
          return;
      }
    }
    navegarMenu(&opcao, tecla, 9);
  }while(opcao != 9 || tecla != 10);
}

void menuConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  int opcao = 1, tecla;
  do {
    clear();
    printf("%s%sAgendar uma consulta\n", (opcao == 1) ? GREEN "▶" : "", RESET);
    printf("%s%sDesmarcar uma consulta\n", (opcao == 2) ? GREEN "▶" : "", RESET);
    printf("%s%sMarcar consulta como realizada\n", (opcao == 3) ? GREEN "▶" : "", RESET);
    printf("%s%sAtualizar uma consulta\n", (opcao == 4) ? GREEN "▶" : "", RESET);
    printf("%s%sObter lista de consultas para o dia atual por médico\n", (opcao == 5) ? GREEN "▶" : "", RESET);
    printf("%s%sObter histórico de consultas por cliente\n", (opcao == 6) ? GREEN "▶" : "", RESET);
    printf("%s%sSair\n", (opcao == 7) ? GREEN "▶" : "", RESET);
    tecla = getKey();
    if(tecla == 10){ 
      switch(opcao){
        case 1:
          agendarConsultas(consultas, clientes, medicos);
          break;
        case 2:
          desmarcarConsultas(consultas);
          break;
        case 3:
          marcarConsultasRealizadas(consultas);
          break;
        case 4:
          atualizarConsultas(consultas, clientes, medicos);
          break;
        case 5:
          obterListaConsultasDiaAtualMedico(consultas, medicos);
          break;
        case 6:
          obterHistoricoConsultasCliente(consultas, clientes);
          break;
        case 7:
          return;
      }
    }
    navegarMenu(&opcao, tecla, 7);
  }while(opcao != 7 || tecla != 10);
}
