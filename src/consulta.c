// BIBLIOTECAS
#include "consulta.h"

// FUNÇÕES CONSULTAS
ST_CONSULTA *procurarConsultasID(ST_CONSULTA *appointments, unsigned int id) {
  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(id == appointments[i].ID) {
      return &appointments[i];
    }
  }
  return NULL;
}

int procurarConsultasNome(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, const char *name) {
  int counter = 0;
  *appointments_found = NULL;
 
  // Converter to uppercase
  const char *cmp = convertToUppercase(name);

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(appointments[i].cliente && appointments[i].medico) {
    if (strncmp(appointments[i].cliente->nome, cmp, 2) == 0 || strncmp(appointments[i].medico->nome, cmp, 2) == 0) {
      ST_CONSULTA *temp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
      if(!temp) {
        free(*appointments_found);
        *appointments_found = NULL;
        return 0;
      }
      *appointments_found = temp;

      (*appointments_found)[counter] = appointments[i];
      counter++;
    }
  }
  }
  return counter;
}

int procurarConsultasCliente(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, ST_CLIENTE *client, int numberClients) {
  int counter = 0;
  *appointments_found = NULL;

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    for (int j = 0; j < numberClients; j++) {
      if(client[j].ID == appointments[i].cliente->ID) {
        ST_CONSULTA *temp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
        if(!temp) {
          free(*appointments_found);
          *appointments_found = NULL;
          return 0;
        }
        *appointments_found = temp;
        (*appointments_found)[counter] = appointments[i];
        counter++;
      }
    }
  }
  return counter;
}

int procurarConsultasMedico(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, ST_MEDICO *doctor, int numberDoctors) {
  int counter = 0;
  *appointments_found = NULL;

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    for(int j = 0; j < numberDoctors; j++) {
      if(doctor[j].ID == appointments[i].medico->ID) {
        ST_CONSULTA *temp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
        if(!temp) {
          free(*appointments_found);
          *appointments_found = NULL;
          return 0;
        }
        *appointments_found = temp;
        (*appointments_found)[counter] = appointments[i];
        counter++;
      }
    }
  }
  return counter;
}

int procurarConsultasData(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found, const char *data) {
  int counter = 0;
  *appointments_found = NULL;
  
  unsigned int day, month, year;
  sscanf(data, "%02u-%02u-%04u", &day, &month, &year);

  for(int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(appointments[i].data_inicial.dia == day && appointments[i].data_inicial.mes == month && appointments[i].data_inicial.ano == year) {
      ST_CONSULTA *temp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
      if(!temp) {
        free(*appointments_found);
        *appointments_found = NULL;
        return 0;
      }
      *appointments_found = temp;
      (*appointments_found)[counter] = appointments[i];
      counter++;
    }
  }
  return counter;
}

int obterListaConsultasAgendadas(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found) {
  int counter = 0;
  *appointments_found = NULL;

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++){
    if(appointments[i].estado == Agendado) {
      ST_CONSULTA *tmp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
      if(!tmp) {
        free(*appointments_found);
        *appointments_found = NULL;
        return 0;
      }
      *appointments_found = tmp;
      (*appointments_found)[counter] = appointments[i];
      counter++;
    }
  }
  return counter;
}

int obterListaConsultasMesAtual(ST_CONSULTA *appointments, ST_CONSULTA **appointments_found) {
  int counter = 0;
  *appointments_found = NULL;
  
  ST_DATA data;
  dataAtual(&data);

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++){
    if(appointments[i].estado == Realizado) {
      if(appointments[i].data_inicial.ano == data.ano && appointments[i].data_inicial.mes == data.mes) {
        ST_CONSULTA *tmp = realloc(*appointments_found, (counter + 1) * sizeof(ST_CONSULTA));
        if(!tmp) {
          free(*appointments_found);
          *appointments_found = NULL;
          return 0;
        }
        *appointments_found = tmp;
        (*appointments_found)[counter] = appointments[i];
        counter++;
      }
    }
  }
  return counter;
}

int obterNumeroConsultasMedico(ST_CONSULTA *appointments, ST_MEDICO doctor) {
  int counter = 0;

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(appointments[i].medico->ID == doctor.ID) {
      counter++;
    }
  }
  return counter;
}

int obterNumeroConsultasEspecialidade(ST_CONSULTA *appointments, const char *speciality) {
  int counter = 0;

  for (int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(strcmp(appointments[i].medico->especialidade, speciality) == 0) {
      counter++;
    }
  }
  return counter;
}

void confirmarConsultas(ST_CONSULTA *consultas, ST_CONSULTA consulta){
  consultas[numberOf(consultas, TYPE_APPOINTMENTS)] = consulta;
}

char **obterHorario(ST_CONSULTA *appointments, ST_CLIENTE *client, ST_MEDICO *doctor, const char *date) {
  unsigned int dia, mes, ano;
  
  sscanf(date, "%02u-%02u-%04u", &dia, &mes, &ano);

  bool occupied_hour[12] = {0};

  for(int i = 0; i < numberOf(appointments, TYPE_APPOINTMENTS); i++) {
    if(appointments[i].data_inicial.ano == ano && 
      appointments[i].data_inicial.mes == mes && 
      appointments[i].data_inicial.dia == dia) {
      
      int index = appointments[i].data_inicial.hora - 8;

      if(appointments[i].medico->ID == doctor->ID || appointments[i].cliente->ID == client->ID) {
          
        occupied_hour[index] = true;
      }
    }
  }

  ST_DATA data;
  dataAtual(&data);
  
  for(unsigned int i = 0; i < 11; i++) {
    if(ano == data.ano && mes == data.mes && dia == data.dia) {
      if(data.hora >= (i + 8)) {
        occupied_hour[i] = true;
      }
    }
  }

  char **str = malloc(12 * sizeof(char *));
  if(!str) {
    return NULL;
  }

  int counter = 0;
  for(int i = 0; i < 11; i++) {
    if(!occupied_hour[i]) {
      char hour[6];
      snprintf(hour, sizeof(hour), "%02dh00", i + 8);
      str[counter] = strdup(hour);
      counter++;
    }
  }
  str[counter] = NULL;
  
  return str;
}

bool verificarDisponibilidade(ST_CONSULTA *consultas,ST_CONSULTA *consulta) {
  ST_DATA data;
  dataAtual(&data);
  
  if (consulta->data_inicial.ano == data.ano && 
    consulta->data_inicial.mes == data.mes && 
    consulta->data_inicial.dia == data.dia && 
    consulta->data_inicial.hora <= data.hora) {
      return false;
  }

  for(int i = 0; i < numberOf(consultas, TYPE_APPOINTMENTS); i++){
    if(consultas[i].medico == consulta->medico && 
      consultas[i].data_inicial.ano == consulta->data_inicial.ano && 
      consultas[i].data_inicial.mes == consulta->data_inicial.mes && 
      consultas[i].data_inicial.dia == consulta->data_inicial.dia && 
      consultas[i].data_inicial.hora == consulta->data_inicial.hora) {
        return false;
    }
  }

  for(int i = 0; i < numberOf(consultas, TYPE_APPOINTMENTS); i++){
    if(consultas[i].cliente == consulta->cliente && 
      consultas[i].data_inicial.ano == consulta->data_inicial.ano && 
      consultas[i].data_inicial.mes == consulta->data_inicial.mes && 
      consultas[i].data_inicial.dia == consulta->data_inicial.dia && 
      consultas[i].data_inicial.hora == consulta->data_inicial.hora) {
        return false;
    }
  }
  
  if(consulta->medico->estado && consulta->cliente->estado) {
    consulta->data_final.ano = consulta->data_inicial.ano;
    consulta->data_final.mes = consulta->data_inicial.mes;
    consulta->data_final.dia = consulta->data_inicial.dia;
    consulta->data_final.hora = consulta->data_inicial.hora + 1;
    return true;
  }

  return false;
}

ST_CONSULTA *obterConsulta(ST_CONSULTA *consultas, unsigned int ID){
  for (int i = 0; i < numberOf(consultas, TYPE_APPOINTMENTS); i++){
    if (consultas[i].ID == ID){
      return &consultas[i];
    }
  }
  return NULL;
}

void inserirFicheiroConsulta(ST_CONSULTA consulta){
  char *estadoConsulta[3] = { "Cancelado", "Agendado", "Realizado"};
  FILE *ficheiro = fopen("data/consultas.txt", "a");
  if(ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  fprintf(ficheiro, "%u,%u,%s,%u,%s,%s,%02u,%02u,%04u,%02u,%02u,%s\n", consulta.ID, consulta.cliente->ID, consulta.cliente->nome, consulta.medico->ID, consulta.medico->nome, consulta.medico->especialidade, consulta.data_inicial.dia, consulta.data_inicial.mes, consulta.data_inicial.ano, consulta.data_inicial.hora, consulta.data_final.hora, estadoConsulta[consulta.estado]);
  fclose(ficheiro);
  return;
}

void carregarFicheiroConsulta(ST_CONSULTA *consultas, ST_CLIENTE *clientes, ST_MEDICO *medicos){
  char linha[1024], *token;
  int i = 0;
  FILE *ficheiro;
  ficheiro = fopen("data/consultas.txt", "r");
  if (ficheiro == NULL){
    return;
  }
  while(fgets(linha, sizeof(linha), ficheiro) && i < MAX_CONSULTAS){
    linha[strcspn(linha, "\n")] = '\0';
    token = strtok(linha, ",");
    consultas[i].ID = (atoi(token));
    token = strtok(NULL, ",");
    consultas[i].cliente = procurarClientesID(clientes, atoi(token));
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    consultas[i].medico = procurarMedicosID(medicos, atoi(token));
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    consultas[i].data_inicial.dia = (atoi(token));
    token = strtok(NULL, ",");
    consultas[i].data_inicial.mes = (atoi(token));
    token = strtok(NULL, ",");
    consultas[i].data_inicial.ano = (atoi(token));
    token = strtok(NULL, ",");
    consultas[i].data_inicial.hora = (atoi(token));
    token = strtok(NULL, ",");
    consultas[i].data_final.hora = (atoi(token));
    token = strtok(NULL, ",");

    if(strcmp(token, "Cancelado") == 0){
      consultas[i].estado = Cancelado;
    }else if(strcmp(token, "Agendado") == 0){
      consultas[i].estado = Agendado;
    }else if(strcmp(token, "Realizado") == 0){
      consultas[i].estado = Realizado;
    }

    ST_DATA date;
    dataAtual(&date);
    if(date.ano >= consultas[i].data_inicial.ano && 
      date.mes >= consultas[i].data_inicial.mes && 
      date.dia >= consultas[i].data_inicial.dia && 
      date.hora >= consultas[i].data_final.hora) {
        consultas[i].estado = Realizado;
    }

    consultas[i].data_final.dia = consultas[i].data_inicial.dia;
    consultas[i].data_final.mes = consultas[i].data_inicial.mes;
    consultas[i].data_final.ano = consultas[i].data_inicial.ano;
    i++;
  }

  atualizarFicheiroConsulta(consultas);
  fclose(ficheiro);
}

void atualizarFicheiroConsulta(ST_CONSULTA *consultas){
  char *estadoConsulta[3] = {"Cancelado", "Agendado", "Realizado"};
  FILE *ficheiro;
  ficheiro = fopen("data/consultas.txt", "w");
  if (ficheiro == NULL){
    printf("Erro.\n");
    return;
  }
  for (int i = 0; i < numberOf(consultas, TYPE_APPOINTMENTS); i++){
    fprintf(ficheiro, "%u,%u,%s,%u,%s,%s,%02u,%02u,%04u,%02u,%02u,%s\n", 
            consultas[i].ID, 
            consultas[i].cliente->ID, 
            consultas[i].cliente->nome, 
            consultas[i].medico->ID, 
            consultas[i].medico->nome, 
            consultas[i].medico->especialidade, 
            consultas[i].data_inicial.dia, 
            consultas[i].data_inicial.mes, 
            consultas[i].data_inicial.ano, 
            consultas[i].data_inicial.hora, 
            consultas[i].data_final.hora, 
            estadoConsulta[consultas[i].estado]);
  }
  fclose(ficheiro);
  return;
}
