#ifndef UI_CLIENTS_H
#define UI_CLIENTS_H

#include <gtk/gtk.h>
#include <strings.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "cliente.h"
#include "userMenu.h"

void initializeUIClients(GtkWidget *stack, ST_APPLICATION *application);
void addClientButtonsToGrid(GtkWidget *grid, ST_APPLICATION *application);
GtkWidget *createClientTable(ST_CLIENTE *clients, int n_clients);

#endif
