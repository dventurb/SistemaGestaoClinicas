#include "ui_appointments.h"

// CALLBACKS
static void clickedButtonAdd(GtkButton *button, gpointer data);
static void clickedButtonEdit(GtkButton *button, gpointer data);
static void clickedButtonToggle(GtkButton *button, gpointer data);
static void clickedButtonView(GtkButton *button, gpointer data);

static void clickedButtonBack(GtkButton *button, gpointer data);
static void changedSearchAppointment(GtkSearchEntry *search_entry, gpointer data);
static void clickedButtonSubmitAdd(GtkButton *button, gpointer data);
static void activateSearchEditAppointment(GtkSearchEntry *search_entry, gpointer data);
static void clickedButtonSubmitEdit(GtkButton *button, gpointer data);
static void activateSearchToggleAppointment(GtkSearchEntry *search_entry, gpointer data);
static void clickedButtonSubmitToggle(GtkButton *button, gpointer data);
static void toggledButton(GtkToggleButton *toggle, gpointer data);
static void changedSearchViewAppointment(GtkSearchEntry *search_entry, gpointer data); 

/** 
 *  @brief Initializes the interface for the appointments. 
 *
 *  @param stack      A pointer to the stack widget used to manage different UI pages.
 *  @param doctors    Pointer to the ST_CONSULTA struct.
 *
 */
void initializeUIAppointments(GtkWidget *stack, ST_CONSULTA *appointments) {
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
  g_signal_connect(search_entry, "search-changed", G_CALLBACK(changedSearchAppointment), appointments);

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

  addAppointmentButtonsToGrid(grid, appointments);

  GtkWidget *scrolled = gtk_scrolled_window_new();
  gtk_widget_set_vexpand(scrolled, true);
  g_object_set_data(G_OBJECT(rigth_box), "Scrolled", scrolled);
  gtk_box_append(GTK_BOX(rigth_box), scrolled);

  ST_CONSULTA *appointments_scheduled = NULL;
  int counter = obterListaConsultasAgendadas(appointments, &appointments_scheduled);
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
void addAppointmentButtonsToGrid(GtkWidget *grid, ST_CONSULTA *appointments) {
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
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonAdd), appointments);
        break;
      case 1:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonEdit), appointments);
        break;
      case 2:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonToggle), appointments);
        break;
      case 3:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonView), appointments);
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
  gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

  const char *headers[] = {"ID", "Client", "Doctor", "Start Date", "End Date", "Status" };
  for (int i = 0; i < 6; i++) {
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
      gtk_label_new(start_date),
      gtk_label_new(end_date),
      gtk_label_new(status)
    };

    for (int z = 0; z < 6; z++) {
      gtk_grid_attach(GTK_GRID(grid), labels[z], z, i + 1, 1, 1);
      if(z < 5) gtk_label_set_selectable(GTK_LABEL(labels[z]), true);  // get selectable all the labels except the status (emoji).
    }
  }
  
  return grid;
}

static void clickedButtonAdd(GtkButton *button, gpointer data) {
  ST_CONSULTA *appointments = (ST_CONSULTA *)data;
  
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
  snprintf(id, sizeof(id), "%d", numberOf(appointments, TYPE_APPOINTMENTS) + 1);

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
  
  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name"); 
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_NAME);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "ClientName", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 8, 1);  

  label = gtk_label_new("NIF");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 10, 2, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "ClientNIF", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 11, 2, 1, 1);
  
  label = gtk_label_new("Doctor ID");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "DoctorID", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 3, 1, 1);

  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
  
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name");  
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_NAME);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "DoctorName", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 4, 8, 1);

  label = gtk_label_new("License Number");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 6);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "LicenseNumber", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 5, 1, 1);

  label = gtk_label_new("Specialty");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 2, 5, 1, 1);
  
  GtkStringList *list = loadSpecialty();
  
  GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(list), NULL);  
  gtk_widget_set_sensitive(dropdown, false);
  gtk_editable_set_editable(GTK_EDITABLE(dropdown), false);
  gtk_widget_set_hexpand(dropdown, true);
  gtk_widget_add_css_class(dropdown, "form-dropdown");
  g_object_set_data(G_OBJECT(rigth_box), "Specialty", dropdown);
  gtk_grid_attach(GTK_GRID(grid), dropdown, 3, 5, 1, 1);
  
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 80);
  gtk_box_append(GTK_BOX(rigth_box), spacer);

  createButtonWithImageLabel(&btn, SUBMIT_PATH,"SUBMIT", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_LABEL);  
  gtk_widget_add_css_class(btn.button, "submit-button");
  gtk_widget_add_css_class(btn.label, "submit-button-label");
  gtk_widget_set_size_request(btn.button, 40, 40);
  gtk_widget_set_halign(btn.button, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(rigth_box), btn.button);
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitAdd), appointments);
}

static void clickedButtonEdit(GtkButton *button, gpointer data) {

}

static void clickedButtonToggle(GtkButton *button, gpointer data) {
  
}

static void clickedButtonView(GtkButton *button, gpointer data) {

}

static void clickedButtonBack(GtkButton *button, gpointer data) {

}

static void changedSearchAppointment(GtkSearchEntry *search_entry, gpointer data) {

}

static void clickedButtonSubmitAdd(GtkButton *button, gpointer data) {

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


