#include "ui_doctors.h"

static void clickedButtonAdd(GtkButton *button, gpointer data);
static void clickedButtonEdit(GtkButton *button, gpointer data);
static void clickedButtonToggle(GtkButton *button, gpointer data);
static void clickedButtonView(GtkButton *button, gpointer data);

static void clickedButtonBack(GtkButton *button, gpointer data);
static void clickedButtonSubmitAdd(GtkButton *button, gpointer data);
static void activateSearchEditDoctor(GtkSearchEntry *search_entry, gpointer data);
static void clickedButtonSubmitEdit(GtkButton *button, gpointer data);

void initializeUIDoctors(GtkWidget *stack, ST_MEDICO *doctors) {
  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "doctors");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search for doctors");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);

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

  addDoctorButtonsToGrid(grid, doctors);

  GtkWidget *scrolled = gtk_scrolled_window_new();
  gtk_widget_set_vexpand(scrolled, true);
  g_object_set_data(G_OBJECT(rigth_box), "Scrolled", scrolled);
  gtk_box_append(GTK_BOX(rigth_box), scrolled);

  ST_MEDICO *doctors_active = NULL;
  int counter = obterListaMedicosAtivos(doctors, &doctors_active);
  grid = createDoctorTable(doctors_active, counter);
  g_object_set_data(G_OBJECT(rigth_box), "DoctorTable", grid);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), grid);
}

/** 
 * @brief Creates and attaches the buttons to a specific position within a GtkGrid.
 *
 * This function helps reduce code duplication and encapsulates the creation and configuration of buttons.
 *
 * @param GtkWidget    GtkGrid widget where the buttons will be placed.
 * @param doctors      Pointer to the ST_MEDICO struct. 
 *
 */
void addDoctorButtonsToGrid(GtkWidget *grid, ST_MEDICO *doctors) {
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
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonAdd), doctors);
        break;
      case 1:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonEdit), doctors);
        break;
      case 2:
        //g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonToggle), doctors);
        break;
      case 3:
        //g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonView), doctors);
        break;
    }
  }
}

/** 
  * @brief Creates a table to display the information for all the doctors.
  *
  * @param doctors      Pointer to the ST_MEDICO struct. 
  * @param doctors      Total number of doctors.
  *
  * @return GtkWidget   GtkGrid widget which represents the table.
  *
  */
GtkWidget *createDoctorTable(ST_MEDICO *doctors, int n_doctors) {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

  const char *headers[] = {"ID", "Name", "Email", "License Number", "Specialty", "Status" };
  for (int i = 0; i < 6; i++) {
    GtkWidget *label = gtk_label_new(headers[i]);
    gtk_widget_add_css_class(label, "header-label");
    gtk_grid_attach(GTK_GRID(grid), label, i, 0, 1, 1);
  }

  for (int i = 0; i < n_doctors; i++) {
    ST_MEDICO j = doctors[i];
    
    char id[5];
    snprintf(id, sizeof(id), "%u", j.ID);

    char license_number[7];
    snprintf(license_number, sizeof(license_number), "%u", j.cedula);

    char status[10]; 
    strcpy(status, j.estado ? "🟢" : "🔴");
    GtkWidget *labels[] = {
      gtk_label_new(id),
      gtk_label_new(j.nome),
      gtk_label_new(j.email),
      gtk_label_new(license_number),
      gtk_label_new(j.especialidade),
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
  ST_MEDICO *doctors = (ST_MEDICO *)data;
  
  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) {
    return;
  }

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "AddDoctors");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "AddDoctors");

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
  snprintf(id, sizeof(id), "%d", numeroMedicos(doctors) + 1);

  GtkEntryBuffer *buffer = gtk_entry_buffer_new(id, -1);
  gtk_entry_set_buffer(GTK_ENTRY(entry), buffer);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
  
  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_NAME);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "Name", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 8, 1);
  
  label = gtk_label_new("Email");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Email");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_EMAIL);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "Email", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 10, 1);

  label = gtk_label_new("License Number");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 11, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 6);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "LicenseNumber", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 12, 2, 1, 1);

  label = gtk_label_new("Specialty");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
  
  GtkStringList *list = loadSpecialty();
  
  GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(list), NULL);
  gtk_drop_down_set_show_arrow(GTK_DROP_DOWN(dropdown), true);
  gtk_widget_set_hexpand(dropdown, true);
  gtk_widget_add_css_class(dropdown, "form-dropdown");
  g_object_set_data(G_OBJECT(rigth_box), "Specialty", dropdown);
  gtk_grid_attach(GTK_GRID(grid), dropdown, 1, 3, 1, 1);

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
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitAdd), doctors);
}

static void clickedButtonEdit(GtkButton *button, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data;

  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) {
    return;
  }
  
  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "EditDoctors");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "EditDoctors");
 
  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search by ID, Email or License Number");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);
  g_signal_connect(search_entry, "activate", G_CALLBACK(activateSearchEditDoctor), doctors);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 30);
  gtk_box_append(GTK_BOX(rigth_box), spacer);

  GtkWidget *label = gtk_label_new("");
  gtk_widget_add_css_class(label, "label-error");
  gtk_widget_set_visible(label, false);
  g_object_set_data(G_OBJECT(rigth_box), "label-error", label);
  gtk_box_append(GTK_BOX(spacer), label);

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
  
  label = gtk_label_new("ID");
  gtk_widget_set_hexpand(label, true);
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  GtkWidget *entry = gtk_entry_new();
  gtk_widget_set_hexpand(entry, true);
  gtk_widget_set_sensitive(entry, false);
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  g_object_set_data(G_OBJECT(rigth_box), "ID", entry);
  gtk_widget_add_css_class(entry, "form-entry-disabled");

  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Name");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_NAME);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "Name", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 8, 1);  

  label = gtk_label_new("Email");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Email");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_EMAIL);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "Email", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 10, 1);

  label = gtk_label_new("License Number");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 11, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 6);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "LicenseNumber", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 12, 2, 1, 1);

  label = gtk_label_new("Specialty");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
  
  GtkStringList *list = loadSpecialty();
  
  GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(list), NULL);
  gtk_drop_down_set_show_arrow(GTK_DROP_DOWN(dropdown), true);
  gtk_widget_set_hexpand(dropdown, true);
  gtk_widget_add_css_class(dropdown, "form-dropdown");
  g_object_set_data(G_OBJECT(rigth_box), "Specialty", dropdown);
  gtk_grid_attach(GTK_GRID(grid), dropdown, 1, 3, 1, 1);

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
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitEdit), doctors);
}

static void clickedButtonToggle(GtkButton *button, gpointer data) {

}

static void clickedButtonView(GtkButton *button, gpointer data) {

}

static void clickedButtonBack(GtkButton *button, gpointer data) {
  (void)button; // unused 

  GtkWidget *stack = (GtkWidget *)data;
  
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddDoctors");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
   
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "EditDoctors");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "ToggleDoctors");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
 
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "ViewDoctors");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "doctors");
}

static void clickedButtonSubmitAdd(GtkButton *button, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data;

  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(button));

  GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char name[STRING_MAX];
  strncpy(name, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  name[STRING_MAX - 1] = '\0';

  entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char email[STRING_MAX];
  strncpy(email, convertToUppercase(gtk_entry_buffer_get_text(buffer)), STRING_MAX - 1);
  email[STRING_MAX - 1] = '\0';

  if(!validarEmail(email, doctors, TYPE_DOCTORS)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *license_number = gtk_entry_buffer_get_text(buffer);
  // TODO: Validate license_number
 
  GtkStringList *list = loadSpecialty();

  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "Specialty");
  int position = gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown));
  const char *specialty = gtk_string_list_get_string(list, position);

  ST_MEDICO new_doctor = {
    .ID = numberOf(doctors, TYPE_DOCTORS) + 1,
    .cedula = atoi(license_number),
    .estado = true,
  };

  strncpy(new_doctor.nome, name, STRING_MAX - 1);
  new_doctor.nome[STRING_MAX - 1] = '\0';

  strncpy(new_doctor.email, email, STRING_MAX - 1);
  new_doctor.email[STRING_MAX - 1] = '\0';

  strncpy(new_doctor.especialidade, specialty, STRING_MAX - 1);
  new_doctor.especialidade[STRING_MAX - 1] = '\0';

  GtkWidget *stack = gtk_widget_get_parent(rigth_box);
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddDoctors");
  if(child) {
    // Confirm the new doctor by adding it to the doctors list.
    confirmarMedicos(doctors, new_doctor);

    // Save the new doctor to the file.
    inserirFicheiroMedico(new_doctor);
    
    // Remove the "AddDoctor" page from the stack.
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  // Remove the "doctor" page from the stack to update the table with new information.
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "doctors");
  gtk_stack_remove(GTK_STACK(stack), child);
  
  // Reinitialize with the updated doctors list.
  initializeUIDoctors(stack, doctors);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "doctors");
}

static void activateSearchEditDoctor(GtkSearchEntry *search_entry, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data;
  ST_MEDICO *edit_doctor = NULL;
  
  GtkWidget *rigth_top_box = gtk_widget_get_parent(GTK_WIDGET(search_entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(rigth_top_box));
  
  GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
  gtk_label_set_text(GTK_LABEL(label), "");
  gtk_widget_set_visible(label, false);
  
  const char *input = gtk_editable_get_text(GTK_EDITABLE(search_entry));

  SEARCH_TYPE type = detectSearchType(input);
  
  switch(type) {
    case SEARCH_BY_ID:
      edit_doctor = procurarMedicosID(doctors, atoi(input));
      if(!edit_doctor) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No doctor found with the provided ID. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_EMAIL:
      edit_doctor = procurarMedicosEmail(doctors, input);
      if(!edit_doctor) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No doctor found with the provided Email. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_LICENSE_NUMBER:
      edit_doctor = procurarMedicosLicenseNumber(doctors, atoi(input));
      if(!edit_doctor) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No doctor found with the provided license number. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    default:
      label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
      gtk_label_set_text(GTK_LABEL(label), "Invalid identifier. Please enter a valid ID, Email or license number.");
      gtk_widget_set_visible(label, true);
      return;
  }

  if(edit_doctor) {
    GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "ID");
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char id[10];
    snprintf(id, sizeof(id), "%u", edit_doctor->ID);
    gtk_entry_buffer_set_text(buffer, id, -1);
        
    entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, edit_doctor->nome, -1);

    entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, edit_doctor->email, -1);  

    entry = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char license_number[7];
    snprintf(license_number, sizeof(license_number), "%u", edit_doctor->cedula);
    gtk_entry_buffer_set_text(buffer, license_number, -1);

    GtkStringList *list = loadSpecialty();

    GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "Specialty");
    for (unsigned int i = 0; i < g_list_model_get_n_items(G_LIST_MODEL(list)); i++) {
      const char *cmp = gtk_string_list_get_string(list, i);
      if(strcmp(cmp, edit_doctor->especialidade) == 0) {
        gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown), i);
        break;
      }
    }
  }
}

static void clickedButtonSubmitEdit(GtkButton *button, gpointer data) {
  ST_MEDICO *doctors = (ST_MEDICO *)data;

  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(button));

  GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "ID");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));

  ST_MEDICO *edit_doctor = procurarMedicosID(doctors, atoi(gtk_entry_buffer_get_text(buffer)));
  if(!edit_doctor) {
    return;
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char name[STRING_MAX];
  strncpy(name, convertToUppercase(gtk_entry_buffer_get_text(buffer)), STRING_MAX - 1);
  name[STRING_MAX - 1] = '\0';

  entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char email[STRING_MAX];
  strncpy(email, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  email[STRING_MAX - 1] = '\0';

  if(!validarEmail(email, doctors, TYPE_DOCTORS) && strcmp(email, edit_doctor->email) != 0) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "LicenseNumber");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *license_number = gtk_entry_buffer_get_text(buffer);
  // TODO: validate license_number

  GtkStringList *list = loadSpecialty();

  GtkWidget *dropdown = g_object_get_data(G_OBJECT(rigth_box), "Specialty");
  int position = gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown));
  const char *specialty = gtk_string_list_get_string(list, position);

  strncpy(edit_doctor->nome, name, STRING_MAX - 1);
  edit_doctor->nome[STRING_MAX - 1] = '\0';

  strncpy(edit_doctor->email, email, STRING_MAX - 1);
  edit_doctor->email[STRING_MAX - 1] = '\0';

  sscanf(license_number, "%u", &edit_doctor->cedula);

  strncpy(edit_doctor->especialidade, specialty, STRING_MAX - 1);
  edit_doctor->especialidade[STRING_MAX - 1] = '\0';

  GtkWidget *stack = gtk_widget_get_parent(rigth_box);
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "EditDoctors");
  if(child) {
    // Update the doctor file.
    atualizarFicheiroMedico(doctors);

    gtk_stack_remove(GTK_STACK(stack), child);
  }  

  // Remove the "doctors" page from the stack to update the table with new information.
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "doctors");
  gtk_stack_remove(GTK_STACK(stack), child);
  
  // Reinitialize with the updated doctors list.
  initializeUIDoctors(stack, doctors);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "doctors");
}
