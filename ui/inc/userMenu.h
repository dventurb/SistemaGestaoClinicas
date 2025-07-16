#ifndef USER_MENU_H 
#define USER_MENU_H 

#include <gtk/gtk.h>
#include "structs.h"
#include "utils.h"
#include "authWindow.h"

void initializeUserMenu(GtkWidget *box, ST_APPLICATION *application, const char *current);
void initializeUserInterface(GtkWidget *stack, ST_APPLICATION *application, const char *current);

#endif
