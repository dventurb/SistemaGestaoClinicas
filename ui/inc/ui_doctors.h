#ifndef UI_DOCTORS_H
#define UI_DOCTORS_H

#include <gtk/gtk.h>
#include "paths.h"
#include "utils.h"
#include "structs.h"
#include "medico.h"
#include "userMenu.h"

void initializeUIDoctors(GtkWidget *stack, ST_APPLICATION *application);
void addDoctorButtonsToGrid(GtkWidget *grid, ST_APPLICATION *application);
GtkWidget *createDoctorTable(ST_MEDICO *doctors, int n_doctors);

#endif
