#include "ui_clients.h"

// CALLBACKS 
static void clickedButtonAdd(GtkButton *button, gpointer data);
static void clickedButtonEdit(GtkButton *button, gpointer data);
static void clickedButtonToggle(GtkButton *button, gpointer data);
static void clickedButtonView(GtkButton *button, gpointer data);
static void clickedButtonBack(GtkButton *button, gpointer data);
static void changedEntryPostalCode(GtkEntry *entry, gpointer data);
static void clickedButtonSubmitAdd(GtkButton *button, gpointer data);
static void activateSearchEditClient(GtkSearchEntry *search_entry, gpointer data);
static void clickedButtonSubmitEdit(GtkButton *button, gpointer data);

/** 
 *  @brief Initializes the interface for the clients. 
 *
 *  @param stack      A pointer to the stack widget used to manage different UI pages.
 *  @param clients    Pointer to the ST_CLIENTE struct.
 *
 */
void initializeUIClients(GtkWidget *stack, ST_CLIENTE *clients) {
  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "clients");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search for clients");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);

  GtkWidget *rigth_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 25);
  gtk_box_append(GTK_BOX(rigth_box), rigth_main_box);
  
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_main_box), grid);

  addClientButtonsToGrid(grid, clients);

  GtkWidget *scrolled = gtk_scrolled_window_new();
  gtk_widget_set_vexpand(scrolled, true);
  gtk_box_append(GTK_BOX(rigth_main_box), scrolled);

  grid = createClientTable(clients, numeroClientes(clients));
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), grid);
}

/** 
 * @brief Creates and attaches the buttons to a specific position within a GtkGrid.
 *
 * This function helps reduce code duplication and encapsulates the creation and configuration of buttons.
 *
 * @param GtkWidget    GtkGrid widget where the buttons will be placed.
 * @param clients      Pointer to the ST_CLIENTE struct. 
 *
 */
void addClientButtonsToGrid(GtkWidget *grid, ST_CLIENTE *clients) {
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
    gtk_widget_add_css_class(button.button, "clients-button");
    gtk_widget_add_css_class(button.label, "clients-button-label");
    gtk_grid_attach(GTK_GRID(grid), button.button, i, 0, 1, 1);

    switch(i) {
      case 0:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonAdd), clients);
        break;
      case 1:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonEdit), clients);
        break;
      case 2:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonToggle), clients);
        break;
      case 3:
        g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonView), clients);
        break;
    }
  }
}

/** 
  * @brief Creates a table to display information about the clients.
  *
  * @param clients      Pointer to the ST_CLIENTE struct. 
  * @param n_clients    Total number of clients.
  *
  * @return GtkWidget   GtkGrid widget which represents the table.
  *
  */
GtkWidget *createClientTable(ST_CLIENTE *clients, int n_clients) {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

  const char *headers[] = {"ID", "Name", "Email", "City", "Birth Date ", "NIF", "SNS", "Status" };
  for (int i = 0; i < 8; i++) {
    GtkWidget *label = gtk_label_new(headers[i]);
    gtk_widget_add_css_class(label, "header-label");
    gtk_grid_attach(GTK_GRID(grid), label, i, 0, 1, 1);
  }

  for (int i = 0; i < n_clients; i++) {
    ST_CLIENTE j = clients[i];
    
    char id[5];
    snprintf(id, sizeof(id), "%u", j.ID);

    char date[15];
    snprintf(date, sizeof(date), "%u-%u-%u", j.data_nascimento.dia, j.data_nascimento.mes, j.data_nascimento.ano);
    
    char nif[10];
    snprintf(nif, sizeof(nif), "%lu", j.NIF);

    char sns[10];
    snprintf(sns, sizeof(sns), "%lu", j.SNS);

    char status[10]; 
    strcpy(status, j.estado ? "🟢" : "🔴");

    GtkWidget *labels[] = {
      gtk_label_new(id),
      gtk_label_new(j.nome),
      gtk_label_new(j.email),
      gtk_label_new(j.morada.cidade),
      gtk_label_new(date),
      gtk_label_new(nif),
      gtk_label_new(sns),
      gtk_label_new(status)
    };

    for (int z = 0; z < 8; z++) {
      gtk_grid_attach(GTK_GRID(grid), labels[z], z, i + 1, 1, 1);
      if(z < 7) gtk_label_set_selectable(GTK_LABEL(labels[z]), true);
    }
  }

  return grid;
}

static void clickedButtonAdd(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;
  
  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) {
    return;
  }

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "AddClients");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "AddClients");

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
 
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(rigth_box), spacer);

  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, "icon/back.png","BACK", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
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
  snprintf(id, sizeof(id), "%d", numeroClientes(clients) + 1);

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

  label = gtk_label_new("Birth Date");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 11, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "01-01-1999");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "BirthDate", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 12, 2, 1, 1);

  label = gtk_label_new("NIF");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  g_object_set_data(G_OBJECT(rigth_box), "NIF", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 3, 1, 1);

  label = gtk_label_new("SNS");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 3, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  g_object_set_data(G_OBJECT(rigth_box), "SNS", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 4, 3, 1, 1);

  label = gtk_label_new("Postal Code");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "4990130");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 7);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "PostalCode", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 4, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryPostalCode), NULL);

  label = gtk_label_new("City");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 2, 4, 1, 1);
 
  entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "PONTE DE LIMA");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_set_sensitive(entry, false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "City", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 3, 4, 4, 1);

  label = gtk_label_new("Street");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
 
  entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Rua Reinaldo Varela");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_set_sensitive(entry, false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "Street", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 5, 4, 1);

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
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitAdd), clients);
}

static void clickedButtonEdit(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;

  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) {
    return;
  }

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "EditClients");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "EditClients");
 
  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *search_entry = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search by ID, Email, NIF or SNS");
  gtk_widget_add_css_class(search_entry, "search-entry");
  gtk_widget_set_hexpand(search_entry, true);
  gtk_box_append(GTK_BOX(rigth_top_box), search_entry);
  g_signal_connect(search_entry, "activate", G_CALLBACK(activateSearchEditClient), clients);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(rigth_box), spacer);

  GtkWidget *label = gtk_label_new("");
  gtk_widget_add_css_class(label, "label-error");
  gtk_widget_set_visible(label, false);
  g_object_set_data(G_OBJECT(rigth_box), "label-error", label);
  gtk_box_append(GTK_BOX(spacer), label);
 
  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, "icon/back.png","BACK", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
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

  label = gtk_label_new("Birth Date");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 11, 2, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "01-01-1999");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "BirthDate", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 12, 2, 1, 1);

  label = gtk_label_new("NIF");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  g_object_set_data(G_OBJECT(rigth_box), "NIF", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 3, 1, 1);

  label = gtk_label_new("SNS");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 3, 3, 1, 1);
 
  entry = gtk_entry_new();
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 9);
  g_object_set_data(G_OBJECT(rigth_box), "SNS", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 4, 3, 1, 1);

  label = gtk_label_new("Postal Code");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
 
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "4990130");
  gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_DIGITS);
  gtk_entry_set_max_length(GTK_ENTRY(entry), 7);
  gtk_widget_add_css_class(entry, "form-entry");
  g_object_set_data(G_OBJECT(rigth_box), "PostalCode", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 4, 1, 1);
  g_signal_connect(entry, "changed", G_CALLBACK(changedEntryPostalCode), NULL);

  label = gtk_label_new("City");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 2, 4, 1, 1);
 
  entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "PONTE DE LIMA");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_set_sensitive(entry, false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "City", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 3, 4, 4, 1);

  label = gtk_label_new("Street");
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
 
  entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(entry), false);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Rua Reinaldo Varela");
  gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
  gtk_widget_set_sensitive(entry, false);
  gtk_widget_add_css_class(entry, "form-entry-disabled");
  g_object_set_data(G_OBJECT(rigth_box), "Street", entry);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 5, 4, 1);

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
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitEdit), clients);
}

static void clickedButtonToggle(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;


}

static void clickedButtonView(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;


}

static void clickedButtonBack(GtkButton *button, gpointer data) {
  (void)button; // unused 

  GtkWidget *stack = (GtkWidget *)data;
  
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddClients");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
   
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "EditClients");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "clients");
}

/**
  * @brief Callback function when the postal code entry is changed.
  *
  * This function updates the city and street entry based on 
  * the postal code entered by the user. 
  *
  * @param entry    A pointer to GtkEntry widget.
  * @param data     User data passed to the callback (unused, NULL). 
  *
*/
static void changedEntryPostalCode(GtkEntry *entry, gpointer data) {
  (void)data; // unused

  GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(grid));
  
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  int length = gtk_entry_buffer_get_length(buffer);

  if(length == 7) {
    bool is_digit = true;
    for(int i = 0; i < 7; i++) {
      if(!g_ascii_isdigit(gtk_entry_buffer_get_text(buffer)[i])) {
        is_digit = false;
        break;
      }
    }
    if(is_digit) {
      int postal_code = atoi(gtk_entry_buffer_get_text(buffer));

      ST_CLIENTE client;
      if(obterMorada(&client, postal_code)) {
    
        if(g_utf8_validate(client.morada.rua, -1, NULL)) {
          GtkWidget *entry_street = g_object_get_data(G_OBJECT(rigth_box), "Street");
          buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_street));
          gtk_entry_buffer_set_text(buffer, client.morada.rua, -1);
        }

        if(g_utf8_validate(client.morada.cidade, -1, NULL)) {
          GtkWidget *entry_city = g_object_get_data(G_OBJECT(rigth_box), "City");
          buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_city));
          gtk_entry_buffer_set_text(buffer, client.morada.cidade, -1);
        }
      }else {
        GtkWidget *entry_street = g_object_get_data(G_OBJECT(rigth_box), "Street");  
        gtk_editable_set_editable(GTK_EDITABLE(entry_street), true);
        gtk_widget_set_sensitive(entry_street, true);
        gtk_widget_add_css_class(entry_street, "form-entry");

        GtkWidget *entry_city = g_object_get_data(G_OBJECT(rigth_box), "City");
        gtk_editable_set_editable(GTK_EDITABLE(entry_city), true);
        gtk_widget_set_sensitive(entry_city, true);
        gtk_widget_add_css_class(entry_city, "form-entry");
      }
    }
  }else {
    GtkWidget *entry_street = g_object_get_data(G_OBJECT(rigth_box), "Street");  
    gtk_editable_set_editable(GTK_EDITABLE(entry_street), false);
    gtk_widget_set_sensitive(entry_street, false);
    gtk_widget_remove_css_class(entry_street, "form-entry");

    GtkWidget *entry_city = g_object_get_data(G_OBJECT(rigth_box), "City");
    gtk_editable_set_editable(GTK_EDITABLE(entry_city), false);
    gtk_widget_set_sensitive(entry_city, false);
    gtk_widget_remove_css_class(entry_city, "form-entry");
  }
}

static void clickedButtonSubmitAdd(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;

  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(button));
  
  GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char name[STRING_MAX];
  strncpy(name, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  name[STRING_MAX - 1] = '\0';

  entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char email[STRING_MAX];
  strncpy(email, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  email[STRING_MAX - 1] = '\0';

  if(!validarEmail(email, clients)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "BirthDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *birth_date = gtk_entry_buffer_get_text(buffer);
  if(!validarFormatoData(birth_date)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }

  entry = g_object_get_data(G_OBJECT(rigth_box), "NIF");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *nif = gtk_entry_buffer_get_text(buffer);
  if(!validarNIF(nif, clients)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }

  entry = g_object_get_data(G_OBJECT(rigth_box), "SNS");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *sns = gtk_entry_buffer_get_text(buffer);
  if(!validarSNS(sns, clients)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "PostalCode");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *postal_code = gtk_entry_buffer_get_text(buffer);
  if(!validarCodigoPostal(postal_code)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
 
  ST_CLIENTE new_client = {
    .ID = numeroClientes(clients) + 1,
    .NIF = atoi(nif),
    .SNS = atoi(sns),
    .estado = true,
  };

  strncpy(new_client.nome, name, STRING_MAX - 1);
  new_client.nome[STRING_MAX - 1] = '\0';

  strncpy(new_client.email, email, STRING_MAX - 1);
  new_client.email[STRING_MAX - 1] = '\0';
  
  sscanf(birth_date,"%2u-%2u-%4u", &new_client.data_nascimento.dia, &new_client.data_nascimento.mes, &new_client.data_nascimento.ano);

  if(!obterMorada(&new_client, atoi(postal_code))) {
    entry = g_object_get_data(G_OBJECT(rigth_box), "City");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    strncpy(new_client.morada.cidade, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
    new_client.morada.cidade[STRING_MAX - 1] = '\0';

    entry = g_object_get_data(G_OBJECT(rigth_box), "Street");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    strncpy(new_client.morada.rua, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
    new_client.morada.rua[STRING_MAX - 1] = '\0';
  }
  
  GtkWidget *stack = gtk_widget_get_parent(rigth_box);
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "AddClients");
  if(child) {
    // Confirm the new client by adding it to the clients list.
    confirmarClientes(clients, new_client);

    // Save the new client to the file.
    inserirFicheiroCliente(new_client);
    
    // Remove the "AddClients" page from the stack.
    gtk_stack_remove(GTK_STACK(stack), child);
  }

  // Remove the "clients" page from the stack to update the table with new information.
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "clients");
  gtk_stack_remove(GTK_STACK(stack), child);
  
  // Reinitialize with the updated clients list.
  initializeUIClients(stack, clients);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "clients");
}

static void activateSearchEditClient(GtkSearchEntry *search_entry, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;
  ST_CLIENTE *edit_client = NULL;
  
  GtkWidget *rigth_top_box = gtk_widget_get_parent(GTK_WIDGET(search_entry));
  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(rigth_top_box));
  
  GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
  gtk_label_set_text(GTK_LABEL(label), "");
  gtk_widget_set_visible(label, false);
  
  const char *input = gtk_editable_get_text(GTK_EDITABLE(search_entry));

  SEARCH_TYPE type = detectSearchType(input);
  
  switch(type) {
    case SEARCH_BY_ID:
      edit_client = procurarClientesID(clients, atoi(input));
      if(!edit_client) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No client found with the provided ID. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_EMAIL:
      edit_client = procurarClientesEmail(clients, input);
      if(!edit_client) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No client found with the provided Email. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_NIF:
      edit_client = procurarClientesNIF(clients, atoi(input));
      if(!edit_client) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No client found with the provided NIF. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_SNS:
      edit_client = procurarClientesSNS(clients, atoi(input));
      if(!edit_client) {
        label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
        gtk_label_set_text(GTK_LABEL(label), "No client found with the provided SNS. Please check and try again.");
        gtk_widget_set_visible(label, true);
      }
      break;
    case SEARCH_BY_INVALID:
      label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
      gtk_label_set_text(GTK_LABEL(label), "Invalid identifier. Please enter a valid ID, NIF, SNS, or Email.");
      gtk_widget_set_visible(label, true);
      return;
  }

  if(edit_client) {
    GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "ID");
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char id[10];
    snprintf(id, sizeof(id), "%u", edit_client->ID);
    gtk_entry_buffer_set_text(buffer, id, -1);
        
    entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, edit_client->nome, -1);

    entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, edit_client->email, -1);
        
    entry = g_object_get_data(G_OBJECT(rigth_box), "BirthDate");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char birth_date[11];
    snprintf(birth_date, sizeof(birth_date), "%02u-%02u-%04u", edit_client->data_nascimento.dia, edit_client->data_nascimento.mes, edit_client->data_nascimento.ano);
    gtk_entry_buffer_set_text(buffer, birth_date, -1);
    
    entry = g_object_get_data(G_OBJECT(rigth_box), "NIF");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char nif[10];
    snprintf(nif, sizeof(nif), "%lu", edit_client->NIF);
    gtk_entry_buffer_set_text(buffer, nif, -1);

    entry = g_object_get_data(G_OBJECT(rigth_box), "SNS");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char sns[10];
    snprintf(sns, sizeof(sns), "%lu", edit_client->SNS);
    gtk_entry_buffer_set_text(buffer, sns, -1);

    entry = g_object_get_data(G_OBJECT(rigth_box), "PostalCode");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char postal_code[8];
    snprintf(postal_code, sizeof(postal_code), "%lu", edit_client->morada.codigo_postal);
    gtk_entry_buffer_set_text(buffer, postal_code, -1);
  }
}


static void clickedButtonSubmitEdit(GtkButton *button, gpointer data) {
  ST_CLIENTE *clients = (ST_CLIENTE *)data;

  GtkWidget *rigth_box = gtk_widget_get_parent(GTK_WIDGET(button));

  GtkWidget *entry = g_object_get_data(G_OBJECT(rigth_box), "ID");
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  ST_CLIENTE *edit_client = procurarClientesID(clients, atoi(gtk_entry_buffer_get_text(buffer)));
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "Name");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char name[STRING_MAX];
  strncpy(name, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  name[STRING_MAX - 1] = '\0';

  entry = g_object_get_data(G_OBJECT(rigth_box), "Email");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char email[STRING_MAX];
  strncpy(email, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
  email[STRING_MAX - 1] = '\0';

  if(!validarEmail(email, clients) && strcmp(email, edit_client->email) != 0) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "BirthDate");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *birth_date = gtk_entry_buffer_get_text(buffer);
  char date[11];
  snprintf(date, sizeof(date), "%02u-%02u-%04u", edit_client->data_nascimento.dia, edit_client->data_nascimento.mes, edit_client->data_nascimento.ano); 
  if(!validarFormatoData(birth_date) && strcmp(birth_date, date) != 0) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }

  entry = g_object_get_data(G_OBJECT(rigth_box), "NIF");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *nif = gtk_entry_buffer_get_text(buffer);
  char NIF[10];
  snprintf(NIF, sizeof(NIF), "%lu", edit_client->NIF);
  if(!validarNIF(nif, clients) && strcmp(nif, NIF) != 0) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }

  entry = g_object_get_data(G_OBJECT(rigth_box), "SNS");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *sns = gtk_entry_buffer_get_text(buffer);
  char SNS[10];
  snprintf(SNS, sizeof(SNS), "%lu", edit_client->SNS);
  if(!validarSNS(sns, clients) && strcmp(sns, SNS) != 0) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
  
  entry = g_object_get_data(G_OBJECT(rigth_box), "PostalCode");
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *postal_code = gtk_entry_buffer_get_text(buffer);
  if(!validarCodigoPostal(postal_code)) {
    gtk_widget_add_css_class(entry, "entry-error");
    return;
  }else {
    gtk_widget_remove_css_class(entry, "entry-error");
    gtk_widget_add_css_class(entry, "form-entry");
  }
 
  strncpy(edit_client->nome, name, STRING_MAX - 1);
  edit_client->nome[STRING_MAX - 1] = '\0';

  strncpy(edit_client->email, email, STRING_MAX - 1);
  edit_client->email[STRING_MAX - 1] = '\0';
  
  sscanf(birth_date,"%02u-%02u-%04u", &edit_client->data_nascimento.dia, &edit_client->data_nascimento.mes, &edit_client->data_nascimento.ano);
  
  sscanf(nif, "%lu", &edit_client->NIF);

  sscanf(sns, "%lu", &edit_client->SNS);

  if(!obterMorada(edit_client, atoi(postal_code))) {
    entry = g_object_get_data(G_OBJECT(rigth_box), "City");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    strncpy(edit_client->morada.cidade, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
    edit_client->morada.cidade[STRING_MAX - 1] = '\0';

    entry = g_object_get_data(G_OBJECT(rigth_box), "Street");
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    strncpy(edit_client->morada.rua, gtk_entry_buffer_get_text(buffer), STRING_MAX - 1);
    edit_client->morada.rua[STRING_MAX - 1] = '\0';
  }
  
  GtkWidget *stack = gtk_widget_get_parent(rigth_box);
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "EditClients");
  if(child) {
    // Update the clients file.
    atualizarFicheiroCliente(clients);

    gtk_stack_remove(GTK_STACK(stack), child);
  }
  
  // Remove the "clients" page from the stack to update the table with new information.
  child = gtk_stack_get_child_by_name(GTK_STACK(stack), "clients");
  gtk_stack_remove(GTK_STACK(stack), child);
  
  // Reinitialize with the updated clients list.
  initializeUIClients(stack, clients);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "clients");
}
