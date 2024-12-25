// BIBLIOTECAS
#include "menu.h"

// FUNÇÕES MENUS
void menuPrincipal(ST_CLIENTE *clientes, ST_MEDICO *medicos, ST_CONSULTA *consultas){
  int opcao;
  do {
    clear();
    printf("[1] - Gestão de Clientes\n");
    printf("[2] - Gestão de Médicos\n");
    printf("[3] - Gestão de Consultas\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
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
    case 0:
      break;
    default:
      printf("Opção não é válida!\a\n");
      delay(1);
      break;
    }
  } while (opcao != 0);
}

void menuClientes(ST_CLIENTE *clientes){
  int opcao;
  do {
    clear();
    printf("[1] - Inserir novo cliente\n");
    printf("[2] - Alterar dados de um cliente\n");
    printf("[3] - Ativar ou desativar um cliente\n");
    printf("[4] - Consultar dados de um cliente\n");
    printf("[5] - Obter uma lista de clientes ativos\n");
    printf("[6] - Procurar um cliente pelo nome\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
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
      case 0:
        break;
      default: 
        printf("Opção não é válida!\a\n");
        delay(1);
        break;
    }
  }while(opcao != 0);
}

void menuMedicos(ST_MEDICO *medicos){
  int opcao;
  do {
    clear();
    printf("[1] - Inserir novo médico\n");
    printf("[2] - Alterar dados de um médico\n");
    printf("[3] - Ativar ou desativar um médico\n");
    printf("[4] - Consultar dados de um médico\n");
    printf("[5] - Obter uma lista de todos os médicos\n");
    printf("[6] - Obter uma lista de médicos disponíveis\n");
    printf("[7] - Obter uma lista de médicos por especialidade\n");
    printf("[8] - Procurar um médico pelo nome\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
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
      case 0:
        break;
      default: 
        printf("Opção não é válida!\a\n");
        delay(1);
        break;
    }
  }while(opcao != 0);
}

void menuConsultas(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  int opcao;
  do {
    clear();
    printf("[1] - Agendar uma consulta\n");
    printf("[2] - Desmarcar uma consulta\n");
    printf("[3] - Marcar consulta como realizada\n");
    printf("[4] - Atualizar uma consulta\n");
    printf("[5] - Obter lista de consultas para o dia atual por médico\n");
    printf("[6] - Obter histórico de consultas por cliente\n");
    printf("[0] - Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);
    limparBuffer();
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
      case 0:
        break;
      default:
        printf("Opção não é válida!\a\n");
        delay(1);
        break;
    }
  }while(opcao != 0);
}