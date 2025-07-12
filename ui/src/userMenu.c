#include "userMenu.h"

// CALLBACKS
static void clickedButtonUserInterface(GtkButton *button, gpointer data);
static void clickedButtonLogout(GtkButton *button, gpointer data);
static void clickedButtonBack(GtkButton *button, gpointer data);
static void clickedButtonUploudImage(GtkButton *button, gpointer data);
static void clickedButtonDeleteImage(GtkButton *button, gpointer data);

static void choosePathImage(GObject *source, GAsyncResult *res, gpointer data);

/** 
 *  @brief Initializes the userMenu in the topbox. 
 *
 *  @param box          A box which represent the topbox.
 *  @param application  A pointer for the ST_APPLICATION struct.
 *
 */
void initializeUserMenu(GtkWidget *box, ST_APPLICATION *application, const char *current) {
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
  g_signal_connect(button.button, "clicked", G_CALLBACK(clickedButtonUserInterface), application);

  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(box), GTK_TYPE_STACK);
  if(!stack) return;
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), current);
  if(!child) return;

  g_object_set_data(G_OBJECT(child), "Image", button.image);
}

static void clickedButtonUserInterface(GtkButton *button, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;

  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) return;

  const char *current = gtk_stack_get_visible_child_name(GTK_STACK(stack));

  initializeUserInterface(stack, application, current);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "userInterface");
}

void initializeUserInterface(GtkWidget *stack, ST_APPLICATION *application, const char *current) {
  ST_FUNCIONARIO *user = application->staff;

  GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
  gtk_stack_add_named(GTK_STACK(stack), rigth_box, "userInterface");

  g_object_set_data(G_OBJECT(rigth_box), "application", application);
  
  GtkWidget *rigth_top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_add_css_class(rigth_top_box, "rigth_top_box");
  gtk_widget_set_size_request(rigth_top_box, -1, 60);
  gtk_box_append(GTK_BOX(rigth_box), rigth_top_box);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_hexpand(spacer, true);
  gtk_box_append(GTK_BOX(rigth_top_box), spacer);
  
  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, LOGOUT_PATH,"LOGOUT", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_LABEL);  
  gtk_widget_add_css_class(btn.button, "logout-button");
  gtk_widget_add_css_class(btn.label, "logout-button-label");
  gtk_widget_set_size_request(btn.image, 20, 20);
  gtk_widget_set_margin_start(btn.button, 10);
  gtk_widget_set_margin_end(btn.button, 25);
  gtk_widget_set_margin_top(btn.button, 15);
  gtk_widget_set_margin_bottom(btn.button, 15);
  gtk_box_append(GTK_BOX(rigth_top_box), btn.button);
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonLogout), application);
  
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 10);
  gtk_box_append(GTK_BOX(rigth_box), spacer);
  
  createButtonWithImageLabel(&btn, BACK_ICON_PATH,"BACK", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "back-button");
  gtk_widget_add_css_class(btn.label, "back-button-label");
  gtk_widget_set_size_request(btn.button, 25, 25);
  gtk_widget_set_halign(btn.button, GTK_ALIGN_START);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(rigth_box), btn.button);
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonBack), (gpointer)current);
  
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_box), grid);
  
  GtkWidget *image = gtk_image_new_from_file(user->pathToImage);
  gtk_widget_set_size_request(image, 64, 64);
  g_object_set_data(G_OBJECT(rigth_box), "Image", image);
  gtk_grid_attach(GTK_GRID(grid), image, 0, 0, 2, 4);

  createButtonWithImageLabel(&btn, NULL, "Uploud Image", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "uploud-photo-button");
  gtk_widget_add_css_class(btn.label, "uploud-photo-label");
  gtk_widget_set_hexpand(btn.label, true);
  gtk_widget_set_size_request(btn.button, 15, 30);
  gtk_widget_set_size_request(btn.box, 15, 30);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_grid_attach(GTK_GRID(grid), btn.button, 4, 1, 2, 1); 
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonUploudImage), application->staff);
 
  createButtonWithImageLabel(&btn, DELETE_PATH, NULL, BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "delete-photo-button");
  gtk_widget_set_size_request(btn.image, 15, 15);
  gtk_widget_set_size_request(btn.button, 15, 15);
  gtk_grid_attach(GTK_GRID(grid), btn.button, 6, 1, 1, 1); 
  g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonDeleteImage), application->staff);
  
  GtkWidget *label = gtk_label_new("Max 1MB (128x128px)");
  gtk_widget_add_css_class(label, "info-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 4, 2, 3, 1);
  
  grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(rigth_box), grid);
  
  label = gtk_label_new("Name");
  gtk_widget_set_hexpand(label, true);
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  GtkWidget *entry = gtk_entry_new();
  gtk_widget_set_hexpand(entry, true);
  g_object_set_data(G_OBJECT(rigth_box), "Name", entry);
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 2, 1);

  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  gtk_entry_buffer_set_text(buffer, user->nome, -1);
  
  label = gtk_label_new("Username");
  gtk_widget_set_hexpand(label, true);
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

  entry = gtk_entry_new();
  gtk_widget_set_hexpand(entry, true);
  g_object_set_data(G_OBJECT(rigth_box), "Username", entry);
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 2, 1);

  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  gtk_entry_buffer_set_text(buffer, user->username, -1);

  label = gtk_label_new("Password");
  gtk_widget_set_hexpand(label, true);
  gtk_widget_add_css_class(label, "form-label");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
 
  entry = gtk_password_entry_new();
  gtk_widget_set_hexpand(entry, true);
  g_object_set_data(G_OBJECT(rigth_box), "Password", entry);
  gtk_widget_add_css_class(entry, "form-entry");
  gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(entry), true);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 2, 1);
  
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 40);
  gtk_box_append(GTK_BOX(rigth_box), spacer);
 
  label = gtk_label_new("");
  gtk_widget_add_css_class(label, "label-error");
  g_object_set_data(G_OBJECT(rigth_box), "label-error", label);
  gtk_widget_set_visible(label, false);
  gtk_box_append(GTK_BOX(rigth_box), label);
  
  createButtonWithImageLabel(&btn, SUBMIT_PATH,"SUBMIT", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_LABEL);  
  gtk_widget_add_css_class(btn.button, "submit-button");
  gtk_widget_add_css_class(btn.label, "submit-button-label");
  gtk_widget_set_size_request(btn.button, 40, 40);
  gtk_widget_set_halign(btn.button, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(rigth_box), btn.button);
  //g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonSubmitAdd), application);
}

static void clickedButtonLogout(GtkButton *button, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;
 
  GtkNative *native = gtk_widget_get_native(GTK_WIDGET(button));
  if(GTK_IS_WINDOW(native)) {
    GtkWindow *window = GTK_WINDOW(native);

    GtkApplication *app = g_object_get_data(G_OBJECT(window), "app");

    createAuthWindow(app, application);

    gtk_window_destroy(window);
  }
}

static void clickedButtonBack(GtkButton *button, gpointer data) {
  const char *current = (const char *)data;

  GtkWidget *stack = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_STACK);
  if(!stack) return;

  GtkWidget *rigth_box = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_BOX);
  if(!rigth_box) return;

  ST_APPLICATION *application = g_object_get_data(G_OBJECT(rigth_box), "application");

  const char *strings[] = { 
    "dashboard", 
    "clients", 
    "doctors", 
    "appointments"
  };
  
  // Update the Image of UserMenu in every Stack page.
  for (int i = 0; i < 4; i++) {
    GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), strings[i]);
  
    GtkWidget *image = g_object_get_data(G_OBJECT(child), "Image");
    gtk_image_set_from_file(GTK_IMAGE(image), application->staff->pathToImage);
  }
  
  GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(stack), "userInterface");
  if(child) {
    gtk_stack_remove(GTK_STACK(stack), child);
  }
  
  gtk_stack_set_visible_child_name(GTK_STACK(stack), current);
}

static void clickedButtonUploudImage(GtkButton *button, gpointer data) {
  ST_FUNCIONARIO *user = (ST_FUNCIONARIO *)data;

  GtkWidget *rigth_box = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_BOX);
  if(!rigth_box) return;

  g_object_set_data(G_OBJECT(rigth_box), "user", user);

  GtkFileDialog *dialog = gtk_file_dialog_new();

  GtkNative *native = gtk_widget_get_native(GTK_WIDGET(button));
  if(GTK_IS_WINDOW(native)) {
    GtkWindow *window = GTK_WINDOW(native);

    gtk_file_dialog_open(dialog, window, NULL, choosePathImage, rigth_box);
  }
}

static void clickedButtonDeleteImage(GtkButton *button, gpointer data) {
  ST_FUNCIONARIO *user = (ST_FUNCIONARIO *)data;

  GtkWidget *rigth_box = gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_BOX);
  if(!rigth_box) return;

  ST_FUNCIONARIO temp[MAX_FUNCIONARIOS] = {0};
  loadUserFile(temp);

  int number = (user->ID % 4) + 1;
  switch (number) {
    case 1:
      strncpy(temp[user->ID - 1].pathToImage, USER_IMAGE_1_PATH, STRING_MAX - 1);
      temp[user->ID - 1].pathToImage[STRING_MAX - 1] = '\0';
      strncpy(user->pathToImage, USER_IMAGE_1_PATH, STRING_MAX - 1);
      user->pathToImage[STRING_MAX - 1] = '\0';
      break;
    case 2:
      strncpy(temp[user->ID - 1].pathToImage, USER_IMAGE_2_PATH, STRING_MAX - 1);
      temp[user->ID - 1].pathToImage[STRING_MAX - 1] = '\0';
      strncpy(user->pathToImage, USER_IMAGE_2_PATH, STRING_MAX - 1);
      user->pathToImage[STRING_MAX - 1] = '\0';
      break;
    case 3:
      strncpy(temp[user->ID - 1].pathToImage, USER_IMAGE_3_PATH, STRING_MAX - 1);
      temp[user->ID - 1].pathToImage[STRING_MAX - 1] = '\0';
      strncpy(user->pathToImage, USER_IMAGE_3_PATH, STRING_MAX - 1);
      user->pathToImage[STRING_MAX - 1] = '\0';
      break;
    case 4:
      strncpy(temp[user->ID - 1].pathToImage, USER_IMAGE_4_PATH, STRING_MAX - 1);
      temp[user->ID - 1].pathToImage[STRING_MAX - 1] = '\0';
      strncpy(user->pathToImage, USER_IMAGE_4_PATH, STRING_MAX - 1);
      user->pathToImage[STRING_MAX - 1] = '\0';
      break;
    default:
      break;
  }
  
  updateUserFile(temp);

  GtkWidget *image = g_object_get_data(G_OBJECT(rigth_box), "Image");
  gtk_image_set_from_file(GTK_IMAGE(image), user->pathToImage);
}

static void choosePathImage(GObject *source, GAsyncResult *res, gpointer data) {
  GtkWidget *rigth_box = (GtkWidget *)data;

  ST_FUNCIONARIO *user = g_object_get_data(G_OBJECT(rigth_box), "user");

  GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
  
  GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
  if(!file) return;

  if(!validationTypeSizeDimensions(file)) {
    GtkWidget *label = g_object_get_data(G_OBJECT(rigth_box), "label-error");
    gtk_label_set_text(GTK_LABEL(label), "Please select a valid image (PNG or JPEG), under 1MB and no larger than 128x128 pixels.");
    gtk_widget_set_visible(label, true);
    return;
  }

  const char *path = g_file_get_path(file);

  ST_FUNCIONARIO temp[MAX_FUNCIONARIOS] = {0};
  loadUserFile(temp);

  strcpy(temp[user->ID - 1].pathToImage, path);
  
  updateUserFile(temp);

  strcpy(user->pathToImage, path);
  
  GtkWidget *image = g_object_get_data(G_OBJECT(rigth_box), "Image");
  gtk_image_set_from_file(GTK_IMAGE(image), path);
}
