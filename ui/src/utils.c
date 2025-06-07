#include "utils.h"

void createButtonWithImageLabel(ST_BUTTON *button, const char *pathToImage, const char *text) {
  button->button = gtk_button_new();
  
  button->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_widget_set_margin_start(button->box, 5);
  gtk_widget_set_margin_end(button->box, 5);
  gtk_button_set_child(GTK_BUTTON(button->button), button->box);
  
  button->image = gtk_image_new_from_file(pathToImage);
  gtk_widget_set_size_request(button->image, 30, 30);
  gtk_box_append(GTK_BOX(button->box), button->image);

  button->label = gtk_label_new(text);
  gtk_box_append(GTK_BOX(button->box), button->label);
}
