#ifndef UI_APPOINTMENTS_H
#define UI_APPOINTMENTS_H

#include <gtk/gtk.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "consulta.h"

void initializeUIAppointments(GtkWidget *stack, ST_CONSULTA *appointments);
void addAppointmentButtonsToGrid(GtkWidget *grid, ST_CONSULTA *appointments);
GtkWidget *createAppointmentTable(ST_CONSULTA *appointments, int n_appointments);

#endif
