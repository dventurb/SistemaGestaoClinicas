#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <gtk/gtk.h>
#include "utils.h"
#include "paths.h"

void initializeLeftBar(GtkWidget *left_box, GtkWidget *stack, ST_APPLICATION *application);
void clickedButtonDashboard(GtkButton *button, gpointer user_data);
void clickedButtonClients(GtkButton *button, gpointer user_data);
void clickedButtonDoctors(GtkButton *button, gpointer user_data);
void clickedButtonAppointments(GtkButton *button, gpointer user_data);
void clickedButtonSettings(GtkButton *button, gpointer user_data);

#endif
