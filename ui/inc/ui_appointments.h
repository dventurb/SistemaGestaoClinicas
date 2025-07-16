#ifndef UI_APPOINTMENTS_H
#define UI_APPOINTMENTS_H

#include <gtk/gtk.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "consulta.h"
#include "userMenu.h"

void initializeUIAppointments(GtkWidget *stack, ST_APPLICATION *application);
void addAppointmentButtonsToGrid(GtkWidget *grid, ST_APPLICATION *application);
GtkWidget *createAppointmentTable(ST_CONSULTA *appointments, int n_appointments);

#endif
