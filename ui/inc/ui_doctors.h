#ifndef UI_DOCTORS_H
#define UI_DOCTORS_H

#include <gtk/gtk.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "medico.h"

void initializeUIDoctors(GtkWidget *stack, ST_MEDICO *doctors);
void addDoctorButtonsToGrid(GtkWidget *grid, ST_MEDICO *doctors);
GtkWidget *createDoctorTable(ST_MEDICO *doctors, int n_doctors);

#endif
