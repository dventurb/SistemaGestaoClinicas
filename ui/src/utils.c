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

/**
  * @brief Detects the type of input used for search the client.
  *
  * This function detect the SearchEntry input and determines whether it 
  * corresponds to an email, NIF, SNS, ID or invalid input. 
  *
  * @param input    String representing the user input. 
  * @return A value from the SEARCH_TYPE enum. 
  *
  */
SEARCH_TYPE detectSearchType(const char *input) {

  // Checking if the input is a valid email format.
  const char *email_regex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
  
  regex_t regex;
  int reti = regcomp(&regex, email_regex, REG_EXTENDED);

  reti = regexec(&regex, input, 0, NULL, 0);

  if(reti == REG_NOMATCH) {
    regfree(&regex);
  }else if(reti) {
    regfree(&regex);
  }else {
    regfree(&regex);
    return SEARCH_BY_EMAIL;
  }
  
  // Check if the input is composed of digits.
  int length = strlen(input);
  
  if(validarFormatoData(input)) {
    return SEARCH_BY_DATE;
  }else if(validarCodigoPostal(input)) {
    return SEARCH_BY_POSTAL_CODE;
  }

  for(int i = 0; i < length; i++) {
    if(!isdigit((unsigned char)input[i])) {
      return SEARCH_BY_INVALID;
    }
  }
  
  // If is 9 digits long, perfome a checksum validation to check if is between NIF or SNS.
  if(length == 9) {
    int digit[8] = { 9, 8, 7, 6, 5, 4, 3, 2 };
    int sum = 0;
    for(int i = 0; i < 8; i++) {
      sum += (input[i] - '0') * digit[i];
    }

    int remainer = sum % 11;
    int checksum = (remainer == 0 || remainer == 1) ? 0 : 11 - remainer;

    if((11 - remainer) == (input[8] - '0')) {
      return SEARCH_BY_NIF;
    }else {
      return SEARCH_BY_SNS;
    }
  }else if(length == 6) {
    return SEARCH_BY_LICENSE_NUMBER;  // Doctor license numbers typically have 6 digits.
  }else { 
    return SEARCH_BY_ID;  // Assume the input is an ID. 
  }
}

GtkStringList *loadSpecialty() {
  GtkStringList *list = gtk_string_list_new(NULL);

  FILE *file = fopen("data/especialidade.txt", "r");
  if(!file) {
    return list;
  }

  char row[64];
  while(fgets(row, sizeof(row), file)) {
    row[strcspn(row, "\n")] = '\0';
    gtk_string_list_append(list, row);
  }

  fclose(file);
  return list;
}
