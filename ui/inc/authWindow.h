#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

// BIBLIOTECAS
#include <gtk/gtk.h>
#include "utils.h" 
#include "paths.h"
#include "dashboard.h"
#include "ui_clients.h"
#include "ui_doctors.h"
#include "ui_appointments.h"
#include "structs.h"
#include "funcionario.h"
#include "mainWindow.h"

// PROTÓTIPOS DAS FUNÇÕES MENUS
void createAuthWindow(GtkApplication *app, gpointer data);
void createRightBox(GtkWidget *main_box);
void createLoginForm(ST_APPLICATION *application, GtkWidget *stack);
void createRegisterForm(ST_APPLICATION *application, GtkWidget *stack);

#endif
