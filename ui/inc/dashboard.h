#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtk/gtk.h>
#include "gtkchart.h"
#include "cliente.h"
#include "userMenu.h"

void initializeDashboard(GtkWidget *stack, ST_APPLICATION *application);
void addCardsToGrid(GtkWidget *grid, ST_APPLICATION *application);

#endif
