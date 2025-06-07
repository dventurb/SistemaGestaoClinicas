#include "mainWindow.h"
#include "ui_utils.h"
#include <gtk/gtk.h>
  
void createMainWindow(GtkApplication *app, gpointer data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Sistema de Gestão de Clínicas");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
  gtk_widget_add_css_class(window, "window");
  
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), main_box);

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_append(GTK_BOX(main_box), rigth_box);

  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(main_box), left_box);

  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_append(GTK_BOX(left_box), rigth_top_box);

  GtkWidget *image = gtk_image_new_from_file("icon/icon.png");
  gtk_widget_set_size_request(image, 48, 48);
  gtk_widget_set_margin_start(image, 12);
  gtk_box_append(GTK_BOX(left_box), image);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(left_box), spacer);

  ST_BUTTON button;
  createButtonWithImageLabel(&button, "icon/client.png", "CLIENTS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  createButtonWithImageLabel(&button, "icon/doctor.png", "DOCTORS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);

  createButtonWithImageLabel(&button, "icon/appointment.png", "APPOINTMENTS");
  gtk_widget_add_css_class(button.button, "leftbar-button");
  gtk_widget_add_css_class(button.button, "leftbar-button-label");
  gtk_box_append(GTK_BOX(left_box), button.button);
  
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT);
  gtk_box_append(GTK_BOX(rigth_box), stack);

  GtkWidget *rigth_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_stack_add_named(GTK_STACK(stack), rigth_main_box, "homepage");
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage");
  
  GtkCssProvider *provider = gtk_css_provider_new();
  GFile *css_file = g_file_new_for_path("styles/styles.css");
  gtk_css_provider_load_from_file(provider, css_file);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_window_present(GTK_WINDOW(window));

  g_object_unref(css_file);
}
