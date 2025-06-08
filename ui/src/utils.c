#include "utils.h"

/** 
  * @brief Creates a button with an image and label.
  * 
  * @param button         Pointer to the ST_BUTTON struct. 
  * @param pathToImage    Path to the image file. Can be NULL if no image is used.
  * @param text           Label to display on the button. Can be NULL if no text is used. 
  * @param orientation    Orientation of the image and label (horizontal or vertical).
  * @param position       Order in which image and label apper (label first or image first).
  *
  */
void createButtonWithImageLabel(ST_BUTTON *button, const char *pathToImage, const char *text, BUTTON_ORIENTATION orientation, BUTTON_POSITION position) {
  button->button = gtk_button_new();
  
  if (orientation == BUTTON_ORIENTATION_HORIZONTAL) {
    button->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(button->box, 5);
    gtk_widget_set_margin_end(button->box, 5);
    gtk_button_set_child(GTK_BUTTON(button->button), button->box);
  }else if(orientation == BUTTON_ORIENTATION_VERTICAL) {
    button->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(button->box, 5);
    gtk_widget_set_margin_end(button->box, 5);
    gtk_button_set_child(GTK_BUTTON(button->button), button->box);
  }
  
  if(position == BUTTON_POSITION_FIRST_IMAGE) {
    if(pathToImage != NULL) {
      button->image = gtk_image_new_from_file(pathToImage);
      gtk_widget_set_size_request(button->image, 30, 30);
      gtk_box_append(GTK_BOX(button->box), button->image);
    }

    if(text != NULL) {
      button->label = gtk_label_new(text);
      gtk_box_append(GTK_BOX(button->box), button->label);
    }
  }else if(position == BUTTON_POSITION_FIRST_LABEL) {
    if(text != NULL) {
      button->label = gtk_label_new(text);
      gtk_box_append(GTK_BOX(button->box), button->label);
    }

    if(pathToImage != NULL) {
      button->image = gtk_image_new_from_file(pathToImage);
      gtk_widget_set_size_request(button->image, 30, 30);
      gtk_box_append(GTK_BOX(button->box), button->image);
    }
  }
}
