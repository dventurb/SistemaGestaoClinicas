#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtk/gtk.h>
#include "gtkchart.h"
#include "cliente.h"

void initializeDashboard(GtkWidget *stack, ST_CLIENTE *clients);

#endif
