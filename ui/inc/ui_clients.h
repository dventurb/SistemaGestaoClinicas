#ifndef UI_CLIENTS_H
#define UI_CLIENTS_H

#include <gtk/gtk.h>
#include <strings.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "cliente.h"

void initializeUIClients(GtkWidget *stack, ST_CLIENTE *clients);
GtkWidget *createClientTable(ST_CLIENTE *client, int n_clients);

#endif
