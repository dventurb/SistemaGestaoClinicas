#include "leftbar.h"

void initializeLeftBar(GtkWidget *left_box) {
  GtkWidget *image = gtk_image_new_from_file(LOGOTIPO_PATH);
  gtk_widget_set_size_request(image, 48, 48);
  gtk_widget_set_margin_start(image, 10);
  gtk_box_append(GTK_BOX(left_box), image);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(left_box), spacer);

  ST_BUTTON button;
  createButtonWithImageLabel(&button, DASHBOARD_ICON_PATH, "DASHBOARD");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  createButtonWithImageLabel(&button, CLIENT_ICON_PATH, "CLIENTS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  createButtonWithImageLabel(&button, DOCTOR_ICON_PATH, "DOCTORS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  createButtonWithImageLabel(&button, APPOINTMENT_ICON_PATH, "APPOINTMENTS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);
  
  createButtonWithImageLabel(&button, SETTINGS_ICON_PATH, "SETTINGS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
}
