#include "ui_appointments.h"

// CALLBACKS
static void clickedButtonAdd(GtkButton *button, gpointer data);
static void clickedButtonEdit(GtkButton *button, gpointer data);
static void clickedButtonToggle(GtkButton *button, gpointer data);
static void clickedButtonView(GtkButton *button, gpointer data);

static void clickedButtonBack(GtkButton *button, gpointer data);
static void clickedButtonSubmitAdd(GtkButton *button, gpointer data);
static void clickedButtonSubmitEdit(GtkButton *button, gpointer data);
static void clickedButtonSubmitToggle(GtkButton *button, gpointer data);

static void changedSearchAppointment(GtkSearchEntry *search_entry, gpointer data);
static void changedSearchViewAppointment(GtkSearchEntry *search_entry, gpointer data); 

static void activateSearchEditAppointment(GtkSearchEntry *search_entry, gpointer data);
static void activateSearchToggleAppointment(GtkSearchEntry *search_entry, gpointer data);

static void toggledButton(GtkToggleButton *toggle, gpointer data);

static void changedEntryClientID(GtkEntry *entry, gpointer data);
static void changedEntryClientNIF(GtkEntry *entry, gpointer data);
static void changedEntryDoctorID(GtkEntry *entry, gpointer data);
static void changedEntryDoctorLicense(GtkEntry *entry, gpointer data);
static void changedEntryStartDate(GtkEntry *entry, gpointer data);
static void changedDropdownStartHour(GtkDropDown *dropdown, GParamSpec *pspec, gpointer data);

/** 
 *  @brief Initializes the interface for the appointments. 
 *
 *  @param stack      A pointer to the stack widget used to manage different UI pages.
 *  @param doctors    Pointer to the ST_CONSULTA struct.
 *
 */
void initializeUIAppointments(GtkWidget *stack, ST_APPLICATION *application) {
  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "appointments");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search for appointments");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);
  g_signal_connect(search_entry, "search-changed", G_CALLBACK(changedSearchAppointment), application->appointments);

  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 10);
  gtk_box_append(GTK_BOX(rigth_box), spacer);
  
  GtkWidget *label = gtk_label_new("");
  gtk_widget_add_css_class(label, "label-error");
  gtk_widget_set_visible(label, false);
  g_object_set_data(G_OBJECT(rigth_box), "label-error", label);
  gtk_box_append(GTK_BOX(spacer), label);
  
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_box), grid);

  addAppointmentButtonsToGrid(grid, application);

  GtkWidget *scrolled = gtk_scrolled_window_new();
  gtk_widget_set_vexpand(scrolled, true);
  g_object_set_data(G_OBJECT(rigth_box), "Scrolled", scrolled);
  gtk_box_append(GTK_BOX(rigth_box), scrolled);

  ST_CONSULTA *appointments_scheduled = NULL;
  int counter = obterListaConsultasAgendadas(application->appointments, &appointments_scheduled);
  grid = createAppointmentTable(appointments_scheduled, counter);
  g_object_set_data(G_OBJECT(rigth_box), "AppointmentTable", grid);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), grid);
}

/** 
 * @brief Creates and attaches the buttons to a specific position within a GtkGrid.
 *
 * This function helps reduce code duplication and encapsulates the creation and configuration of buttons.
 *
 * @param GtkWidget      GtkGrid widget where the buttons will be placed.
 * @param appointments   Pointer to the ST_CONSULTA struct. 
 *
 */
void addAppointmentButtonsToGrid(GtkWidget *grid, ST_APPLICATION *application) {
  ST_BUTTON button;
  
  const char *labels[] = {
    "Add", "Edit", "Toggle", "View"
  };

  const char *paths[] = {
    ADD_CLIENT_PATH, 
    EDIT_CLIENT_PATH, 
    TOGGLE_CLIENT_PATH, 
    VIEW_CLIENT_PATH
  };
  
  for (int i = 0; i <= 3; i++) {
    createButtonWithImageLabel(&button, paths[i], labels[i], BUTTON_ORIENTATION_VERTICAL, BUTTON_POSITION_FIRST_IMAGE);
    gtk_widget_set_size_request(button.button, 96, 96);
    gtk_widget_set_size_request(button.image, 48, 48);
    gtk_widget_add_css_class(button.button, "button");
    gtk_widget_add_css_class(button.label, "button-label");
    gtk_grid_attach(GTK_GRID(grid), button.button, i, 0, 1, 1);

    switch(i) {
      case 0:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonAdd), application);
        break;
      case 1:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonEdit), application);
        break;
      case 2:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonToggle), application);
        break;
      case 3:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonView), application);
        break;
    }
  }
}

/** 
  * @brief Creates a table to display the information for all the appointments.
  *
  * @param appointments     Pointer to the ST_CONSULTA struct. 
  * @param n_appointments   Total number of appointments.
  *
  * @return GtkWidget   GtkGrid widget which represents the table.
  *
  */
GtkWidget *createAppointmentTable(ST_CONSULTA *appointments, int n_appointments) {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 14);

  const char *headers[] = {"ID", "Client", "Doctor", "Specialty", "Start Date", "End Date", "Status" };
  for (int i = 0; i < 7; i++) {
    GtkWidget *label = gtk_label_new(headers[i]);
    gtk_widget_add_css_class(label, "header-label");
    gtk_grid_attach(GTK_GRID(grid), label, i, 0, 1, 1);
  }

  for (int i = 0; i < n_appointments; i++) {
    ST_CONSULTA j = appointments[i];
    
    char id[5];
    snprintf(id, sizeof(id), "%u", j.ID);

    char start_date[20];
    snprintf(start_date, sizeof(start_date), "%02u-%02u-%04u %02u:00", j.data_inicial.dia, j.data_inicial.mes, j.data_inicial.ano, j.data_inicial.hora);

    char end_date[20];
    snprintf(end_date, sizeof(end_date), "%02u-%02u-%04u %02u:00", j.data_final.dia, j.data_final.mes, j.data_final.ano, j.data_final.hora);
    

    char status[10];
    if (j.estado == Cancelado) {
      strcpy(status,  "🔴");
    } else if (j.estado == Agendado) {
      strcpy(status, "🟡");
    } else if(j.estado == Realizado) {
      strcpy(status, "🟢");
    }
    
    GtkWidget *labels[] = {
      gtk_label_new(id),
      gtk_label_new(j.cliente->nome),
      gtk_label_new(j.medico->nome),
      gtk_label_new(j.medico->especialidade),
      gtk_label_new(start_date),
      gtk_label_new(end_date),
      gtk_label_new(status)
    };

    for (int z = 0; z < 7; z++) {
      gtk_grid_attach(GTK_GRID(grid), labels[z], z, i + 1, 1, 1);
      if(z < 5) gtk_label_set_selectable(GTK_LABEL(labels[z]), true);  // get selectable all the labels except the status (emoji).
    }
  }
  
  return grid;
}

static void clickedButtonAdd(GtkButton *button, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;
  
  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) {
    return;
  }

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "AddAppointments");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "AddAppointments");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
 
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 30);
  gtk_box_append(GTK_BOX(rigth_box), spacer);

  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, BACK_ICON_PATH,"BACK", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "back-button");
  gtk_widget_add_css_class(btn.label, "back-button-label");
  gtk_widget_set_size_request(btn.button, 25, 25);
  gtk_widget_set_halign(btn.button, GTK_ALIGN_START);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(rigth_box), btn.button);
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonBack), stack);
  
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 14);
  gtk_widget_set_hexpand(grid, true);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_box), grid);
  
  GtkWidget *label = gtk_label_new("ID");
  gtk_widget_set_hexpand(label, true);
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  GtkWidget *entry = gtk_entry_new();
  gtk_widget_set_hexpand(entry, true);
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  g_object_set_data(G_OBJECT(rigth_box), "ID", entry);
  gtk_widget_add_css_class(entry, "form-entry-disabled");

  char id[15];
  snprintf(id, sizeof(id), "%d", numberOf(application->appointments, TYPE_APPOINTMENTS) + 1);

  GtkEntryBuffer *buffer = gtk_entry_buffer_new(id, -1);
  gtk_entry_set_buffer(GTK_ENTRY(entry), buffer);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
  
  label = gtk_label_new("Client ID");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_widget_set_hexpand(entry, true);
  g_object_set_data(G_OBJECT(rigth_box), "ClientID", entry);
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryClientID), application->clients);
    
  label = gtk_label_new("NIF");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 2, 1, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "ClientNIF", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 3, 1, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryClientNIF), application->clients);
  
  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name"); 
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "ClientName", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 2, 1);  
  
  label = gtk_label_new("Doctor ID");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "DoctorID", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 3, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryDoctorID), application->doctors);

  label = gtk_label_new("License Number");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 2, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 6);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "LicenseNumber", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 3, 3, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryDoctorLicense), application->doctors);
  
  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name");  
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "DoctorName", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 4, 2, 1);

  label = gtk_label_new("Specialty");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 3, 4, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Pediatria");  
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "DoctorSpecialty", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 4, 4, 1, 1);
  
  label = gtk_label_new("Start Date");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);

  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "01-01-2025");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "StartDate", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 6, 1, 1);  
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryStartDate), application);
  
  const char *start_hour[] = {"10h00", NULL};
  GtkWidget *dropdown = gtk_drop_down_new_from_strings(start_hour);  
  gtk_widget_set_sensitive(dropdown, false);
  gtk_widget_set_hexpand(dropdown, true);
  gtk_widget_add_css_class(dropdown, "form-dropdown");
  g_object_set_data(G_OBJECT(rigth_box), "StartHour", dropdown);
  gtk_grid_attach(GTK_GRID(grid), dropdown, 2, 6, 1, 1);
  g_signal_connect(dropdown, "notify::selected", G_CALLBACK(changedDropdownStartHour), NULL);
  
  label = gtk_label_new("End Date");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 3, 6, 1, 1);

  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "01-01-2025");
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "EndDate", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 4, 6, 1, 1);  
 
  const char *end_hour[] = {"11h00", NULL};
  dropdown = gtk_drop_down_new_from_strings(end_hour);  
  gtk_widget_set_sensitive(dropdown, false);
  gtk_widget_set_hexpand(dropdown, true);
  gtk_widget_add_css_class(dropdown, "form-dropdown");
  g_object_set_data(G_OBJECT(rigth_box), "EndHour", dropdown);
  gtk_grid_attach(GTK_GRID(grid), dropdown, 5, 6, 1, 1);

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), spacer);
 
  label = gtk_label_new("");
  gtk_widget_add_css_class(label, "label-error");
  g_object_set_data(G_OBJECT(rigth_box), "label-error", label);
  gtk_widget_set_visible(label, false);
  gtk_box_append(GTK_BOX(rigth_box), label);
  
  createButtonWithImageLabel(&btn, SUBMIT_PATH,"SUBMIT", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_LABEL);  
  gtk_widget_add_css_class(btn.button, "submit-button");
  gtk_widget_add_css_class(btn.label, "submit-button-label");
  gtk_widget_set_size_request(btn.button, 40, 40);
  gtk_widget_set_halign(btn.button, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(rigth_box), btn.button);
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitAdd), application);
}

static void clickedButtonEdit(GtkButton *button, gpointer data) {

}

static void clickedButtonToggle(GtkButton *button, gpointer data) {
  
}

static void clickedButtonView(GtkButton *button, gpointer data) {

}

static void clickedButtonBack(GtkButton *button, gpointer data) {
  (void)button; // unused 

  GtkWidget *stack = (GtkWidget *)data;
  
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddAppointments");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
   
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "EditAppointments");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "ToggleAppointments");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
 
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "ViewAppointments");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "appointments");
}

static void changedSearchAppointment(GtkSearchEntry *search_entry, gpointer data) {
  
}

static void clickedButtonSubmitAdd(GtkButton *button, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;
  
  ST_CLIENTE *clients = application->clients;
  ST_MEDICO *doctors = application->doctors;
  ST_CONSULTA *appointments = application->appointments;
  
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(button));

  ST_CLIENTE *clients_active = NULL;
  obterListaClientesAtivos(clients, &clients_active);
  
  GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "ClientID");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *client_id = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(client_id) != SEARCH_BY_ID) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_CLIENTE *client_found = procurarClientesID(clients_active, atoi(client_id));
  if(!client_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  entry = g_object_get_data(G_OBJECT(rigth_box), "ClientNIF");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *client_nif = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(client_nif) != SEARCH_BY_NIF) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");    
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  client_found = procurarClientesNIF(clients_active, atoi(client_nif));
  if(!client_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_MEDICO *doctors_active = NULL;
  obterListaMedicosAtivos(doctors, &doctors_active);
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "DoctorID");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *doctor_id = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(doctor_id) != SEARCH_BY_ID) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_MEDICO *doctor_found = procurarMedicosID(doctors_active, atoi(doctor_id));
  if(!doctor_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }
 
  entry = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *doctor_license = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(doctor_license) != SEARCH_BY_LICENSE_NUMBER) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");    
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  doctor_found = procurarMedicosLicenseNumber(doctors_active, atoi(doctor_license));
  if(!doctor_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  if(client_found->ID != atoi(client_id) || doctor_found->ID != atoi(doctor_id)) {
    return;
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "StartDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *start_date = gtk_entry_buffer_get_text(buffer);
  if(!validarFormatoData(start_date) || validarData(start_date)) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  GObject *item = gtk_drop_down_get_selected_item(GTK_DROP_DOWN(dropdown));
  if(!item) {
    return;
  }
  const char *start_hour = gtk_string_object_get_string(GTK_STRING_OBJECT(item));
  char *cpy = strdup(start_hour);
  
  ST_CONSULTA new_appointment = {
    .ID = numberOf(appointments, TYPE_APPOINTMENTS) + 1,
    .cliente = client_found,
    .medico = doctor_found,
    .estado = Agendado,
  };
  
  sscanf(start_date, "%02u-%02u-%04u", &new_appointment.data_inicial.dia, &new_appointment.data_inicial.mes, &new_appointment.data_inicial.ano);

  char *token = strtok(cpy, "h");
  int hour_int = atoi(token);
  new_appointment.data_inicial.hora = hour_int;
  
  free(cpy);
  cpy = NULL;

  if(!verificarDisponibilidade(appointments, &new_appointment)) {
    GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
    gtk_label_set_text(GTK_LABEL(label), "Unavailable time. Please check and try again.");
    gtk_widget_set_visible(label, true);
    return;
  }

  GtkWidget *stack = gtk_widget_get_parent(rigth_box);
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddAppointments");
  if(child) {
    // Confirm the new appointments by adding it to the appointments list.
    confirmarConsultas(appointments, new_appointment);

    // Save the new appointments to the file.
    inserirFicheiroConsulta(new_appointment);
    
    // Remove the "AddAppointments" page from the stack.
    gtk_stack_remove(GTK_STACK(stack), child);
  }
  
  // Remove the "appointments" page from the stack to update the table with new information.
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "appointments");
  gtk_stack_remove(GTK_STACK(stack), child);
  
  // Reinitialize with the updated appointments list.
  initializeUIAppointments(stack, application);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "appointments");
}

static void activateSearchEditAppointment(GtkSearchEntry *search_entry, gpointer data) {

}

static void clickedButtonSubmitEdit(GtkButton *button, gpointer data) {

}

static void activateSearchToggleAppointment(GtkSearchEntry *search_entry, gpointer data) {

}
static void clickedButtonSubmitToggle(GtkButton *button, gpointer data) {

}

static void toggledButton(GtkToggleButton *toggle, gpointer data) {

}

static void changedSearchViewAppointment(GtkSearchEntry *search_entry, gpointer data) {

}

static void changedEntryClientID(GtkEntry *entry, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data; 
  
  ST_CLIENTE *clients_active = NULL;
  obterListaClientesAtivos(clients, &clients_active);
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *input = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(input) != SEARCH_BY_ID) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_CLIENTE *client_found = procurarClientesID(clients_active, atoi(input));
  if(!client_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  GtkWidget *entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientNIF");
  g_signal_handlers_disconnect_by_func(entry_st, G_CALLBACK(changedEntryClientNIF), clients);  // Temporarily disconnect the signal to set the text for NIF GtkEntry. 

  char nif[10];
  snprintf(nif, sizeof(nif), "%lu", client_found->NIF);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, nif, -1);
  gtk_widget_remove_css_class(entry_st, "entry-error");
  gtk_widget_add_css_class(entry_st, "form-entry");

  g_signal_connect(entry_st, "changed", G_CALLBACK(changedEntryClientNIF), clients); 

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientName");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, client_found->nome, -1);
  
  entry_st = g_object_get_data(G_OBJECT(rigth_box), "StartDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, "", -1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_st), "01-01-2025");
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  gtk_widget_set_sensitive(dropdown, false);
}

static void changedEntryClientNIF(GtkEntry *entry, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data; 
  
  ST_CLIENTE *clients_active = NULL;
  obterListaClientesAtivos(clients, &clients_active);
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *input = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(input) != SEARCH_BY_NIF) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");    
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_CLIENTE *client_found = procurarClientesNIF(clients_active, atoi(input));
  if(!client_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  GtkWidget *entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientID");
  g_signal_handlers_disconnect_by_func(entry_st, G_CALLBACK(changedEntryClientID), clients);  // Temporarily disconnect the signal to set the text for ID GtkEntry. 
  
  char id[10];
  snprintf(id, sizeof(id), "%u", client_found->ID);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, id, -1);
  gtk_widget_remove_css_class(entry_st, "entry-error");
  gtk_widget_add_css_class(entry_st, "form-entry");

  g_signal_connect(entry_st, "changed", G_CALLBACK(changedEntryClientID), clients); 
  
  entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientName");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, client_found->nome, -1);      

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "StartDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, "", -1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_st), "01-01-2025");
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  gtk_widget_set_sensitive(dropdown, false);
}

static void changedEntryDoctorID(GtkEntry *entry, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data; 
  
  ST_MEDICO *doctors_active = NULL;
  obterListaMedicosAtivos(doctors, &doctors_active);
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *input = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(input) != SEARCH_BY_ID) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_MEDICO *doctor_found = procurarMedicosID(doctors_active, atoi(input));
  if(!doctor_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  GtkWidget *entry_st = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
  g_signal_handlers_disconnect_by_func(entry_st, G_CALLBACK(changedEntryDoctorLicense), doctors);  // Temporarily disconnect the signal to set the text for NIF GtkEntry. 

  char license_number[7];
  snprintf(license_number, sizeof(license_number), "%u", doctor_found->cedula);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, license_number, -1);
  gtk_widget_remove_css_class(entry_st, "entry-error");
  gtk_widget_add_css_class(entry_st, "form-entry");

  g_signal_connect(entry_st, "changed", G_CALLBACK(changedEntryDoctorLicense), doctors); 

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorName");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, doctor_found->nome, -1);

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorSpecialty");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, doctor_found->especialidade, -1);

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "StartDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, "", -1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_st), "01-01-2025");
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  gtk_widget_set_sensitive(dropdown, false);
}

static void changedEntryDoctorLicense(GtkEntry *entry, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data; 
  
  ST_MEDICO *doctors_active = NULL;
  obterListaMedicosAtivos(doctors, &doctors_active);
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *input = gtk_entry_buffer_get_text(buffer);
  if(detectSearchType(input) != SEARCH_BY_LICENSE_NUMBER) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  ST_MEDICO *doctor_found = procurarMedicosLicenseNumber(doctors_active, atoi(input));
  if(!doctor_found) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }

  GtkWidget *entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorID");
  g_signal_handlers_disconnect_by_func(entry_st, G_CALLBACK(changedEntryDoctorID), doctors);  // Temporarily disconnect the signal to set the text for NIF GtkEntry. 

  char id[10];
  snprintf(id, sizeof(id), "%u", doctor_found->ID);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, id, -1);
  gtk_widget_remove_css_class(entry_st, "entry-error");
  gtk_widget_add_css_class(entry_st, "form-entry");

  g_signal_connect(entry_st, "changed", G_CALLBACK(changedEntryDoctorID), doctors); 

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorName");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, doctor_found->nome, -1);  

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorSpecialty");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, doctor_found->especialidade, -1);

  entry_st = g_object_get_data(G_OBJECT(rigth_box), "StartDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, "", -1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_st), "01-01-2025");
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  gtk_widget_set_sensitive(dropdown, false);
}

static void changedEntryStartDate(GtkEntry *entry, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;
  
  ST_CLIENTE *clients = application->clients;
  ST_MEDICO *doctors = application->doctors;
  ST_CONSULTA *appointments = application->appointments;
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  ST_CLIENTE *clients_active = NULL;
  obterListaClientesAtivos(clients, &clients_active);

  ST_CLIENTE *client_found = NULL;
  
  GtkWidget *entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientID");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  if(detectSearchType(gtk_entry_buffer_get_text(buffer)) != SEARCH_BY_ID) {
    return;
  }else {
    client_found = procurarClientesID(clients_active, atoi(gtk_entry_buffer_get_text(buffer)));
    if(client_found) {
      entry_st = g_object_get_data(G_OBJECT(rigth_box), "ClientNIF");
      buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
      if(client_found->NIF != strtoul(gtk_entry_buffer_get_text(buffer), NULL, 10)) {
        return;
      }
    }else {
      return;
    }
  }
  
  ST_MEDICO *doctors_active = NULL;
  obterListaMedicosAtivos(doctors, &doctors_active);
  
  ST_MEDICO *doctor_found = NULL;
  
  entry_st = g_object_get_data(G_OBJECT(rigth_box), "DoctorID");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  if(detectSearchType(gtk_entry_buffer_get_text(buffer)) != SEARCH_BY_ID) {
    return;
  }else {
    doctor_found = procurarMedicosID(doctors_active, atoi(gtk_entry_buffer_get_text(buffer)));
    if(doctor_found) {
      entry_st = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
      buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
      if(doctor_found->cedula != strtoul(gtk_entry_buffer_get_text(buffer), NULL, 10)) {
        return;
      }
    }else {
      return;
    }
  }
  
  buffer = gtk_entry_get_buffer(entry);
  const char *start_date = gtk_entry_buffer_get_text(buffer);
  if(!validarFormatoData(start_date) || validarData(start_date)) {
    gtk_widget_add_css_class(GTK_WIDGET(entry), "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(GTK_WIDGET(entry), "entry-error");
    gtk_widget_add_css_class(GTK_WIDGET(entry), "form-entry");
  }
  
  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "StartHour");
  
  char **start_hour = obterHorario(appointments, clients, doctors, start_date);
  if(start_hour[0] == NULL) {
    gtk_widget_set_sensitive(dropdown, false);
    return;
  }

  GtkStringList *list = gtk_string_list_new(NULL);

  for(int i = 0; start_hour[i] != NULL; i++) {
    gtk_string_list_append(list, start_hour[i]);  
  }

  gtk_drop_down_set_model(GTK_DROP_DOWN(dropdown), G_LIST_MODEL(list));  
  gtk_widget_set_sensitive(dropdown, true);
  
  entry_st = g_object_get_data(G_OBJECT(rigth_box), "EndDate"); 
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_st));
  gtk_entry_buffer_set_text(buffer, start_date, -1);
  
  GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
  gtk_label_set_text(GTK_LABEL(label), "");
  gtk_widget_set_visible(label, false);
  
  for(int i = 0; start_hour[i] != NULL; i++) {
    free(start_hour[i]);  
  }
  free(start_hour);
}

static void changedDropdownStartHour(GtkDropDown *dropdown, GParamSpec *pspec, gpointer data) { 
  (void)pspec; // unused
  (void)data;  // unused
  
  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(dropdown));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));

  GObject *item = gtk_drop_down_get_selected_item(dropdown);
  if(!item) return;

  const char **str = malloc(2 * sizeof(char *));
  if(!str) return;
 
  const char *hour = gtk_string_object_get_string(GTK_STRING_OBJECT(item));
  char *cpy = strdup(hour);

  char *token = strtok(cpy, "h");
  int hour_int = atoi(token) + 1;
  
  char new_hour[16]; // Never exceeds 6 bytes, but this silence compiler warning.
  snprintf(new_hour, sizeof(new_hour), "%02dh00", hour_int);
  
  GtkStringList *list = gtk_string_list_new(NULL);
  gtk_string_list_append(list, new_hour);

  GtkWidget *dropdown_st = g_object_get_data(G_OBJECT(rigth_box), "EndHour");  
  gtk_drop_down_set_model(GTK_DROP_DOWN(dropdown_st), G_LIST_MODEL(list));
 
  GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
  gtk_label_set_text(GTK_LABEL(label), "");
  gtk_widget_set_visible(label, false);
  
  free(cpy);
  cpy = NULL;
}


