#ifndef UTILS_H 
#define UTILS_H 

#include <gtk/gtk.h>
#include "regex.h"
#include "auxiliares.h"
#include "cliente.h"

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

typedef enum {
  SEARCH_BY_INVALID,
  SEARCH_BY_ID,
  SEARCH_BY_EMAIL,
  SEARCH_BY_NIF,
  SEARCH_BY_SNS,
  SEARCH_BY_DATE,
  SEARCH_BY_POSTAL_CODE,
  SEARCH_BY_LICENSE_NUMBER
} SEARCH_TYPE;

void createButtonWithImageLabel(ST_BUTTON *button, const char *pathToImage, const char *text, BUTTON_ORIENTATION orientation, BUTTON_POSITION position);
SEARCH_TYPE detectSearchType(const char *input);
GtkStringList *loadSpecialty();

#endif
