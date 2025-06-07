#ifndef UTILS_H 
#define UTILS_H 

#include <gtk/gtk.h>

typedef struct {
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *image;
  GtkWidget *label;
} ST_BUTTON;

void createButtonWithImageLabel(ST_BUTTON *button, const char *pathToImage, const char *text);

#endif
