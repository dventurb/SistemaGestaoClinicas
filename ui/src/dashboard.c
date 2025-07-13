#include "dashboard.h"

void initializeDashboard(GtkWidget *stack, ST_APPLICATION *application) {
  ST_CLIENTE *clients = application->clients;

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "dashboard");
  gtk_widget_add_css_class(rigth_box, "box");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "dashboard");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search for declaration");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);

  initializeUserMenu(rigth_top_box, application, "dashboard");
 
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_box), grid);
  
  addCardsToGrid(grid, application);
}

void addCardsToGrid(GtkWidget *grid, ST_APPLICATION *application) {
  
  char total_doctors[16];
  snprintf(total_doctors, sizeof(total_doctors), "%d", numberOf(application->doctors, TYPE_DOCTORS));

  ST_MEDICO *doctors_active = NULL;
  int counter = obterListaMedicosAtivos(application->doctors, &doctors_active);
  char available_doctors[30];
  snprintf(available_doctors, sizeof(available_doctors), "%d currently available", counter);

  char total_clients[16];
  snprintf(total_clients, sizeof(total_clients), "%d", numberOf(application->clients, TYPE_CLIENTS));

  ST_CLIENTE *clients_active = NULL;
  counter = obterListaClientesAtivos(application->clients, &clients_active);
  char available_clients[30];
  snprintf(available_clients, sizeof(available_clients), "%d currently active", counter);
  
  ST_CONSULTA *appointments_scheduled = NULL;
  counter = obterListaConsultasAgendadas(application->appointments, &appointments_scheduled);
  char scheduled_appointments[16];
  snprintf(scheduled_appointments, sizeof(scheduled_appointments), "%d", counter);
  
  ST_DATA date;
  dataAtual(&date);
  char data[11];
  snprintf(data, sizeof(data), "%02u-%02u-%04u", date.dia, date.mes, date.ano);

  ST_CONSULTA *appointments_today = NULL;
  counter = procurarConsultasData(appointments_scheduled, &appointments_today, data);
  char today_appointments[16];
  snprintf(today_appointments, sizeof(today_appointments), "%d today", counter);
  
  GtkStringList *list = loadSpecialty();
  char specialties[16];
  snprintf(specialties, sizeof(specialties), "%d", g_list_model_get_n_items(G_LIST_MODEL(list)));

  const char *image[] = {
    DOCTOR_CARD_PATH,
    CLIENT_CARD_PATH,
    APPOINTMENT_CARD_PATH,
    SPECIALTY_CARD_PATH
  };

  const char *title[] = {
    "Doctors Registered",
    "Clients",
    "Scheduled Appointments",
    "Active Specialties"
  };

  const char *info[] = {
    total_doctors,
    total_clients,
    scheduled_appointments,
    specialties
  };

  const char *subtitle[] = {
    available_doctors,
    available_clients,
    today_appointments,
    NULL
  };

  for (int i = 0; i < 4; i++) {
    GtkWidget *card_box = createAnalyticCard(i, image[i], title[i], info[i], subtitle[i]);
    gtk_grid_attach(GTK_GRID(grid), card_box, i, 0, 1, 1);
  }
}
