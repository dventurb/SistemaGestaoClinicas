#include "mainWindow.h"
  
void createMainWindow(GtkApplication *app, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;

  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hospital Management");
  gtk_window_set_default_size(GTK_WINDOW(window), 1100, 700);
  gtk_widget_add_css_class(window, "window");
  
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), main_box);

  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(main_box), left_box);
 
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT);
  gtk_box_append(GTK_BOX(main_box), stack);
  
  initializeLeftBar(left_box, stack);
  
  initializeDashboard(stack, application);
  initializeUIClients(stack, application);
  initializeUIDoctors(stack, application);
  initializeUIAppointments(stack, application);

  GtkCssProvider *provider = gtk_css_provider_new();
  GFile *css_file = g_file_new_for_path(STYLE_CSS_PATH);
  gtk_css_provider_load_from_file(provider, css_file);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_window_present(GTK_WINDOW(window));

  g_object_unref(css_file);
}
