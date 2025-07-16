// BIBLIOTECAS
#include "auxiliares.h"

// FUNÇÕES AUXILIARES
 void dataAtual(ST_DATA *data_hora_atual){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   data_hora_atual->semana = tm.tm_wday + 1;
   data_hora_atual->hora = tm.tm_hour;
   data_hora_atual->dia = tm.tm_mday;
   data_hora_atual->mes = tm.tm_mon + 1;
   data_hora_atual->ano = tm.tm_year + 1900; 
 }

const char *getMonthString(int month) {
  const char *strings[] = {
    "January", "February", "March",
    "April", "May", "June", 
    "July", "August","September",
    "October", "November", "December"
  };
  
  return strings[month - 1]; // Index 0 it's January
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
  * @brief Generates a PDF report for the appointments.
  *
  * This function creates a PDF report with information
  * about the appointments and doctors. 
  * 
  * @param application    Pointer to the ST_APPLICATION struct.
  *
  *
*/
void createReportPDF(ST_APPLICATION *application) {
  ST_CONSULTA *appointments = application->appointments;
  ST_MEDICO *doctors = application->doctors;

  HPDF_Doc pdf = HPDF_New(NULL, NULL);

  HPDF_Page cover = HPDF_AddPage(pdf);
  HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, MONTHLY_REPORT_COVER);

  HPDF_REAL img_width = HPDF_Image_GetWidth(image);
  HPDF_REAL img_height = HPDF_Image_GetHeight(image);

  HPDF_Page_SetWidth(cover, img_width);
  HPDF_Page_SetHeight(cover, img_height);

  HPDF_Page_DrawImage(cover, image, 0, 0, img_width, img_height);
  
  HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);

  HPDF_Page page = HPDF_AddPage(pdf);
  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 20);
  
  const char *title = "Hospital Management Monthly Report";
  
  HPDF_Page_TextRect(page, 50, 750, 550, 720, title, HPDF_TALIGN_LEFT, NULL);
  HPDF_Page_EndText(page);

  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 18);

  const char *subtitle_1 = "Overview";
  
  HPDF_Page_TextRect(page, 50, 710, 550, 690, subtitle_1, HPDF_TALIGN_LEFT, NULL);
  HPDF_Page_EndText(page);

  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 12);

  ST_DATA date;
  dataAtual(&date);
  const char *month = getMonthString(date.mes);

  char text[512];

  snprintf(text, sizeof(text), "This report provides a comprehensive overview of the hospital operations for the %s %u, "
           "focusing on the appointments managed by our doctors. Detailed insights into the "
           "appointment counts for each doctor and their respective specialities are provided "
           "to ensure a clear understanding of team performance.", month, date.ano);

  HPDF_Page_TextRect(page, 50, 680, 550, 620, text, HPDF_TALIGN_JUSTIFY, NULL);
  HPDF_Page_EndText(page);

  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 18);

  const char *subtitle_2 = "Appointments Summary";
  
  HPDF_Page_TextRect(page, 50, 610, 550, 590, subtitle_2, HPDF_TALIGN_LEFT, NULL);
  HPDF_Page_EndText(page);
  
  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 12);
  
  ST_CONSULTA *appointments_found = NULL;
  int counter = obterListaConsultasMesAtual(appointments, &appointments_found);
  appointments_found[counter].ID = 0; // Terminator

  snprintf(text, sizeof(text), "The total number of appointments scheduled for this month was %d, "
           "with a breakdown into individual doctor’s contributions outlined below.", counter);

  HPDF_Page_TextRect(page, 50, 580, 550, 520, text, HPDF_TALIGN_JUSTIFY, NULL);
  HPDF_Page_EndText(page);

  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 16);

  const char *subtitle_3 = "Appointments by Doctor";
  
  HPDF_Page_TextRect(page, 50, 510, 550, 490, subtitle_3, HPDF_TALIGN_LEFT, NULL);
  HPDF_Page_EndText(page);
  
  float ypos = 480;

  createTablePDF(appointments_found, doctors, &pdf, &page, &ypos);
  ypos -= 20;
  
  // To low for the new subtitle
  if(ypos < 80) {
    page = HPDF_AddPage(pdf);
    ypos = 750;
  }
  
  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 18);
  
  const char *subtitle_4 = "Speciality Insights";

  HPDF_Page_TextRect(page, 50, ypos, 550, ypos - 20, subtitle_4, HPDF_TALIGN_LEFT, NULL);
  HPDF_Page_EndText(page);

  ypos -= 30;

  if(ypos < 60) {
    page = HPDF_AddPage(pdf);
    ypos = 750;
  }

  HPDF_Page_BeginText(page);
  HPDF_Page_SetFontAndSize(page, font, 12);

  snprintf(text, sizeof(text), "The specialities in our hospital are diverse, each contributing significantly to our" 
           "monthly operations. Below is a summary of appointments by speciality:");
  
  HPDF_Page_TextRect(page, 50, ypos, 550, ypos - 40, text, HPDF_TALIGN_JUSTIFY, NULL);
  HPDF_Page_EndText(page);
  
  ypos -= 50;
  
  GtkStringList *list = loadSpecialty();
  for(unsigned int i = 0; i < g_list_model_get_n_items(G_LIST_MODEL(list)); i++) {
    counter = obterNumeroConsultasEspecialidade(appointments_found, gtk_string_list_get_string(list, i));
    if(counter > 0) {
      
      if(ypos < 40) {
        page = HPDF_AddPage(pdf);
        ypos = 750;
      }

      snprintf(text, sizeof(text), "· %s: %d appointments", gtk_string_list_get_string(list, i), counter);
      
      HPDF_Page_BeginText(page);
      HPDF_Page_SetFontAndSize(page, font, 12);
      HPDF_Page_TextRect(page, 60, ypos, 550, ypos - 15, text, HPDF_TALIGN_LEFT, NULL);
      HPDF_Page_EndText(page);

      ypos -= 20;
    }
  }

    if(ypos < 80) {
      page = HPDF_AddPage(pdf);
      ypos = 750;
    }

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 18);
  
    const char *subtitle_5 = "Conclusion";
    
    ypos -= 30;

    HPDF_Page_TextRect(page, 50, ypos, 550, ypos - 20, subtitle_5, HPDF_TALIGN_LEFT, NULL);
    HPDF_Page_EndText(page);
    
    ypos -= 30;
    
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 12);
    
    snprintf(text, sizeof(text), "%s %u illustrates a robust schedule and effective planning by the hospital " 
             "management team across various specialities. Attention to the individual performances"
            "of doctors and departments can guide future strategic initiatives to optimize operations further.", month, date.ano);
    
    HPDF_Page_TextRect(page, 50, ypos, 550, ypos - 100, text, HPDF_TALIGN_JUSTIFY, NULL);
    HPDF_Page_EndText(page);

    g_object_unref(list);
    free(appointments_found);

    char filename[30];
    snprintf(filename, sizeof(filename), "%s_%d_report.pdf", month, date.ano);
    
    HPDF_SaveToFile(pdf, filename);
    HPDF_Free(pdf);
  }

/** 
  * @brief Creates a table of doctors and their appointments in PDF.
  *
  * This function creates a table within the given PDF page.
  * 
  * @param appointments   Pointer to the ST_CONSULTA struct.
  * @param doctors        Pointer to the ST_MEDICO struct.
  * @param pdf            Pointer to the PDF document.
  * @param page           Pointer to the current page (HPDF_Page).
  * @param ypos           Pointer to the current vertical position.
  *
  *
*/
void createTablePDF(ST_CONSULTA *appointments, ST_MEDICO *doctors, HPDF_Doc *pdf, HPDF_Page *page, float *ypos) {
  int rows = 0; 

  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    int counter = obterNumeroConsultasMedico(appointments, doctors[i]);
    if(counter > 0) {
      rows++;
    }
  }

  if(rows == 0) return;
  
  bool first_page = true; // Max 30 rows on first page and y position start in 480

  HPDF_REAL xpos = hpdftbl_cm2dpi(2);
  
  HPDF_REAL width = hpdftbl_cm2dpi(A4PAGE_WIDTH_CM - 4); // 2cm in each side 
  HPDF_REAL height = 0; 
  
  hpdftbl_t tbl;
  if(rows > 30) {
    tbl = hpdftbl_create(30, 3);

  }else {
    tbl = hpdftbl_create(rows + 1, 3);
  }
  
  hpdftbl_set_colwidth_percent(tbl, 0, 33);
  hpdftbl_set_colwidth_percent(tbl, 1, 33);
  hpdftbl_set_colwidth_percent(tbl, 2, 34);
  
  hpdftbl_use_header(tbl, true);

  hpdftbl_set_cell(tbl, 0, 0, NULL, "Doctor Name");
  hpdftbl_set_cell(tbl, 0, 1, NULL, "Speciality");
  hpdftbl_set_cell(tbl, 0, 2, NULL, "Appointments Made");

  int current_row = 1;
  int processed_rows = 0;

  for (int i = 0; i < numberOf(doctors, TYPE_DOCTORS); i++) {
    int counter = obterNumeroConsultasMedico(appointments, doctors[i]);
    int max_rows = first_page ? 30 : 50;
    if(counter > 0) {
      char name[105];
      snprintf(name, sizeof(name), "Dr. %s", doctors[i].nome);
      hpdftbl_set_cell(tbl, current_row, 0, NULL,  name);

      hpdftbl_set_cell(tbl, current_row, 1, NULL, doctors[i].especialidade);

      char buffer[16];
      snprintf(buffer, sizeof(buffer), "%d", counter);
      hpdftbl_set_cell(tbl, current_row, 2, NULL, buffer);

      current_row++;
      processed_rows++;

      if(current_row >= max_rows && processed_rows < rows) {
        hpdftbl_stroke(*pdf, *page, tbl, xpos, *ypos, width, height);

        *page = HPDF_AddPage(*pdf);
        *ypos = 750;
        
        int remainer = rows - processed_rows;
        int next_page_rows = remainer > 50 ? 50 : remainer;

        tbl = hpdftbl_create(next_page_rows, 3);

        hpdftbl_set_colwidth_percent(tbl, 0, 33);
        hpdftbl_set_colwidth_percent(tbl, 1, 33);
        hpdftbl_set_colwidth_percent(tbl, 2, 34);
  
        hpdftbl_use_header(tbl, false);

        first_page = false;
        current_row = 0;
      }
    }
  }

  if(current_row > 0 && processed_rows > 0) {
    hpdftbl_stroke(*pdf, *page, tbl, xpos, *ypos, width, height);
    *ypos -= current_row * 20; 
  }
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
