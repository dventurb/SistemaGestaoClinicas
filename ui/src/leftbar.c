#include "leftbar.h"

void initializeLeftBar(GtkWidget *left_box, GtkWidget *stack) {
  GtkWidget *image = gtk_image_new_from_file(LOGOTIPO_PATH);
  gtk_widget_set_size_request(image, 64, 64);
  gtk_widget_set_margin_start(image, 10);
  gtk_box_append(GTK_BOX(left_box), image);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(left_box), spacer);

  ST_BUTTON button;
  
  createButtonWithImageLabel(&button, DASHBOARD_ICON_PATH, "DASHBOARD", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.label, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonDashboard), stack);

  createButtonWithImageLabel(&button, CLIENT_ICON_PATH, "CLIENTS", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.label, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonClients), stack);

  createButtonWithImageLabel(&button, DOCTOR_ICON_PATH, "DOCTORS", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.label, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonDoctors), stack);
  
  createButtonWithImageLabel(&button, APPOINTMENT_ICON_PATH, "APPOINTMENTS", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.label, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonAppointments), stack);

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);
  
  createButtonWithImageLabel(&button, SETTINGS_ICON_PATH, "SETTINGS", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.label, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonSettings), stack);
}

void clickedButtonDashboard(GtkButton *button, gpointer data) {
  (void)button; // unused parameter 
  GtkWidget *stack = (GtkWidget *)data;

  clearStackPages(stack);

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "dashboard");
}

void clickedButtonClients(GtkButton *button, gpointer data) {
  (void)button; // unused parameter 
  GtkWidget *stack = (GtkWidget *)data;

  clearStackPages(stack);
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "clients");
}

void clickedButtonDoctors(GtkButton *button, gpointer data) {
  (void)button; // unused parameter 
  GtkWidget *stack = (GtkWidget *)data;

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "doctors");
}

void clickedButtonAppointments(GtkButton *button, gpointer data) {
  (void)button; // unused parameter 
  GtkWidget *stack = (GtkWidget *)data;

  clearStackPages(stack);
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "appointments");
}

void clickedButtonSettings(GtkButton *button, gpointer data) {
  (void)button; // unused parameter 
  GtkWidget *stack = (GtkWidget *)data;

  clearStackPages(stack);
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "settings");
}
