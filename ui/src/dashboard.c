#include "dashboard.h"

void initializeDashboard(GtkWidget *stack, ST_APPLICATION *application) {
  ST_CLIENTE *clients = application->clients;

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "dashboard");
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

  initializeUserMenu(rigth_top_box, application);

  GtkWidget *rigth_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(rigth_box), rigth_main_box);

  GtkChart *chart;
  chart = GTK_CHART(gtk_chart_new());
  gtk_chart_set_type(chart, GTK_CHART_TYPE_GAUGE_ANGULAR);
  gtk_chart_set_title(chart, "Clients");
  gtk_chart_set_value(chart, numberOf(clients, TYPE_CLIENTS));
  gtk_chart_set_value_min(chart, numberOf(clients, TYPE_CLIENTS));
  gtk_chart_set_value_max(chart, MAX_CLIENTES);
  gtk_chart_set_color(chart, "line_color", "green");
  gtk_widget_set_hexpand(GTK_WIDGET(chart), TRUE);
  gtk_widget_set_vexpand(GTK_WIDGET(chart), TRUE);
  gtk_box_append(GTK_BOX(rigth_main_box), GTK_WIDGET(chart));
}
