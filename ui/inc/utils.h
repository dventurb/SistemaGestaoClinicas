#ifndef UTILS_H 
#define UTILS_H 

#include <gtk/gtk.h>

typedef struct {
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *image;
  GtkWidget *label;
} ST_BUTTON;

typedef enum {
  BUTTON_ORIENTATION_HORIZONTAL,
  BUTTON_ORIENTATION_VERTICAL,
} BUTTON_ORIENTATION;

typedef enum {
  BUTTON_POSITION_FIRST_LABEL,
  BUTTON_POSITION_FIRST_IMAGE,
} BUTTON_POSITION;

void createButtonWithImageLabel(ST_BUTTON *button, const char *pathToImage, const char *text, BUTTON_ORIENTATION orientation, BUTTON_POSITION position);

#endif
