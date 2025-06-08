#include "ui_clients.h"

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

  ST_BUTTON button;
  
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_main_box), grid);
  
  createButtonWithImageLabel(&button, ADD_CLIENT_PATH, "Add", BUTTON_ORIENTATION_VERTICAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_set_size_request(button.button, 96, 96);
  gtk_widget_set_size_request(button.image, 48, 48);
  gtk_widget_add_css_class(button.button, "clients-button");
  gtk_widget_add_css_class(button.label, "clients-button-label");
  gtk_grid_attach(GTK_GRID(grid), button.button, 0, 0, 1, 1);

  createButtonWithImageLabel(&button, EDIT_CLIENT_PATH, "Edit", BUTTON_ORIENTATION_VERTICAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_set_size_request(button.button, 96, 96);
  gtk_widget_set_size_request(button.image, 48, 48);
  gtk_widget_add_css_class(button.button, "clients-button");
  gtk_widget_add_css_class(button.label, "clients-button-label");
  gtk_grid_attach(GTK_GRID(grid), button.button, 1, 0, 1, 1);
  
  createButtonWithImageLabel(&button, TOGGLE_CLIENT_PATH, "Toggle", BUTTON_ORIENTATION_VERTICAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_set_size_request(button.button, 96, 96);
  gtk_widget_set_size_request(button.image, 48, 48);
  gtk_widget_add_css_class(button.button, "clients-button");
  gtk_widget_add_css_class(button.label, "clients-button-label");
  gtk_grid_attach(GTK_GRID(grid), button.button, 2, 0, 1, 1); 
  
  createButtonWithImageLabel(&button, VIEW_CLIENT_PATH, "View", BUTTON_ORIENTATION_VERTICAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_set_size_request(button.button, 96, 96);
  gtk_widget_set_size_request(button.image, 48, 48);
  gtk_widget_add_css_class(button.button, "clients-button");
  gtk_widget_add_css_class(button.label, "clients-button-label");
  gtk_grid_attach(GTK_GRID(grid), button.button, 3, 0, 1, 1);

  grid = createClientTable(clients, numeroClientes(clients));
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_main_box), grid);
}

GtkWidget *createClientTable(ST_CLIENTE *client, int n_clients) {
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
    ST_CLIENTE j = client[i];
    
    char id[5];
    snprintf(id, sizeof(id), "%u", j.ID);

    char date[15];
    snprintf(date, sizeof(date), "%u-%u-%u", j.data_nascimento.dia, j.data_nascimento.mes, j.data_nascimento.ano);
    
    char nif[10];
    snprintf(nif, sizeof(nif), "%lu", j.NIF);

    char sns[10];
    snprintf(sns, sizeof(sns), "%lu", j.SNS);

    char status[10]; 
    strcpy(status, j.estado ? "Active" : "Inactive");

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
    }
  }

  return grid;
}
