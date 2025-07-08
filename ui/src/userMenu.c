#include "userMenu.h"

void initializeUserMenu(GtkWidget *box, ST_APPLICATION *application) {
  ST_FUNCIONARIO *user = application->staff; // Current user 
 
  GtkWidget *user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_append(GTK_BOX(box), user_box);

  ST_BUTTON button;
  
  createButtonWithImageLabel(&button, user->pathToImage, user->nome, BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);
  gtk_widget_add_css_class(button.button, "user-button");
  gtk_widget_add_css_class(button.label, "user-button-label");
  gtk_widget_set_size_request(button.image, 20, 20);
  gtk_widget_set_margin_start(button.button, 5);
  gtk_widget_set_margin_end(button.button, 20);
  gtk_widget_set_margin_top(button.button, 10);
  gtk_widget_set_margin_bottom(button.button, 10);
  gtk_box_append(GTK_BOX(user_box), button.button);
  //TODO:g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButton), stack);
}
