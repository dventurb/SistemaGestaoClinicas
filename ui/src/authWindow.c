#include "authWindow.h"

// CALLBACKS
static void pressedGestureLogin(GtkGestureClick *gesture, int n_press, double x, double y, gpointer data);
static void pressedGestureRegister(GtkGestureClick *gesture, int n_press, double x, double y, gpointer data);

/** 
 *  @brief Create the window for the authentication. 
 *
 *  @param app    Pointer to the GtkApplication.
 *  @param data   Pointer to the application data which contains clients, doctors, 
 *                  appointments and staff. 
 *
 */
void createAuthWindow(GtkApplication *app, gpointer data) {
  ST_APPLICATION *application = (ST_APPLICATION *)data;
  
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hospital Management");
  gtk_window_set_default_size(GTK_WINDOW(window), 1100, 700);
  gtk_widget_add_css_class(window, "window");

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), main_box);

  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT);
  gtk_box_append(GTK_BOX(main_box), stack);

  createRightBox(main_box);
  createLoginForm(stack);
  createRegisterForm(stack);

  GtkCssProvider *provider = gtk_css_provider_new();
  GFile *css_file = g_file_new_for_path(STYLE_CSS_PATH);
  gtk_css_provider_load_from_file(provider, css_file);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_window_present(GTK_WINDOW(window));

  g_object_unref(css_file);
}

void createRightBox(GtkWidget *main_box) {
  GtkWidget *right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(right_box, "right-box");
  gtk_widget_set_size_request(right_box, 320, -1);
  gtk_box_append(GTK_BOX(main_box), right_box);
  
  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(right_box), spacer);
  
  GtkWidget *image = gtk_image_new_from_file(LOGOTIPO_PATH);
  gtk_widget_set_size_request(image, 64, 64);
  gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(right_box), image);
 
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 30);
  gtk_widget_set_valign(spacer, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(right_box), spacer);
  
  GtkWidget *label = gtk_label_new("Hospital Management");
  gtk_widget_add_css_class(label, "title");
  gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(right_box), label);

  label = gtk_label_new("A simple CRUD, carefully built for hospitals.");
  gtk_widget_add_css_class(label, "subtitle");
  gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(right_box), label); 

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(right_box), spacer);
}

/** 
 *  @brief Creates and adds the login interface. 
 *
 *  @param stack    Pointer to the GtkStack.
 *
 */
void createLoginForm(GtkWidget *stack) {
  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(left_box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(left_box, true);
  gtk_stack_add_named(GTK_STACK(stack), left_box, "login");

  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);
  
  GtkWidget *label = gtk_label_new("Log in");
  gtk_widget_add_css_class(label, "login-title");
  gtk_box_append(GTK_BOX(left_box), label);

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 30);
  gtk_box_append(GTK_BOX(left_box), spacer);

  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(left_box), grid);

  label = gtk_label_new("Username");
  gtk_widget_add_css_class(label, "login-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  GtkWidget *entry = gtk_entry_new();
  g_object_set_data(G_OBJECT(left_box), "Username", entry);
  gtk_widget_add_css_class(entry, "login-entry");
  gtk_widget_set_halign(entry, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 1, 1, 1);
  
  label = gtk_label_new("Password");
  gtk_widget_add_css_class(label, "login-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

  entry = gtk_entry_new();
  g_object_set_data(G_OBJECT(left_box), "Password", entry);
  gtk_widget_add_css_class(entry, "login-entry");
  gtk_widget_set_halign(entry, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 3, 1, 1);
 
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 15);
  gtk_box_append(GTK_BOX(left_box), spacer);

  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, NULL,"Login", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "login-button");
  gtk_widget_add_css_class(btn.label, "login-button-label");
  gtk_widget_set_size_request(btn.button, 80, 40);
  gtk_widget_set_halign(btn.box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(left_box), btn.button);
  //TODO: g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonBack), stack);
  
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_append(GTK_BOX(left_box), box);

  label = gtk_label_new("Don't have an account?");
  gtk_widget_add_css_class(label, "login-label");
  gtk_box_append(GTK_BOX(box), label);
  
  label = gtk_label_new("Sign up");
  gtk_widget_set_focusable(label, true);
  gtk_widget_add_css_class(label, "login-label-signup");
  gtk_box_append(GTK_BOX(box), label);

  GtkGesture *gesture = gtk_gesture_click_new();
  gtk_widget_add_controller(label, GTK_EVENT_CONTROLLER(gesture));
  g_signal_connect(gesture, "pressed", G_CALLBACK(pressedGestureLogin), stack);  

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");
}

/** 
 *  @brief Creates the register interface. 
 *
 *  @param stack    Pointer to the GtkStack.
 *
 */
void createRegisterForm(GtkWidget *stack) {
  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(left_box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(left_box, true);
  gtk_stack_add_named(GTK_STACK(stack), left_box, "register");

  GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);
  
  GtkWidget *label = gtk_label_new("Sign up");
  gtk_widget_add_css_class(label, "login-title");
  gtk_box_append(GTK_BOX(left_box), label);

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 30);
  gtk_box_append(GTK_BOX(left_box), spacer);

  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(left_box), grid);
  
  label = gtk_label_new("Name");
  gtk_widget_add_css_class(label, "login-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  GtkWidget *entry = gtk_entry_new();
  g_object_set_data(G_OBJECT(left_box), "Name", entry);
  gtk_widget_add_css_class(entry, "login-entry");
  gtk_widget_set_halign(entry, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 1, 1, 1);
  
  label = gtk_label_new("Username");
  gtk_widget_add_css_class(label, "login-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

  entry = gtk_entry_new();
  g_object_set_data(G_OBJECT(left_box), "Username", entry);
  gtk_widget_add_css_class(entry, "login-entry");
  gtk_widget_set_halign(entry, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 3, 1, 1);
  
  label = gtk_label_new("Password");
  gtk_widget_add_css_class(label, "login-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);

  entry = gtk_entry_new();
  g_object_set_data(G_OBJECT(left_box), "Password", entry);
  gtk_widget_add_css_class(entry, "login-entry");
  gtk_widget_set_halign(entry, GTK_ALIGN_CENTER);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 5, 1, 1);
 
  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(spacer, -1, 15);
  gtk_box_append(GTK_BOX(left_box), spacer);

  ST_BUTTON btn; 
  createButtonWithImageLabel(&btn, NULL,"Sign up", BUTTON_ORIENTATION_HORIZONTAL, BUTTON_POSITION_FIRST_IMAGE);  
  gtk_widget_add_css_class(btn.button, "login-button");
  gtk_widget_add_css_class(btn.label, "login-button-label");
  gtk_widget_set_size_request(btn.button, 80, 40);
  gtk_widget_set_halign(btn.box, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(btn.button, false);
  gtk_box_append(GTK_BOX(left_box), btn.button);
  //TODO:g_signal_connect(btn.button, "clicked", G_CALLBACK(clickedButtonBack), stack);
  
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_append(GTK_BOX(left_box), box);

  label = gtk_label_new("Already have an account?");
  gtk_widget_add_css_class(label, "login-label");
  gtk_box_append(GTK_BOX(box), label);
  
  label = gtk_label_new("Log in");
  gtk_widget_set_focusable(label, true);
  gtk_widget_add_css_class(label, "login-label-signup");
  gtk_box_append(GTK_BOX(box), label);

  GtkGesture *gesture = gtk_gesture_click_new();
  gtk_widget_add_controller(label, GTK_EVENT_CONTROLLER(gesture));
  g_signal_connect(gesture, "pressed", G_CALLBACK(pressedGestureRegister), stack);  

  spacer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(spacer, true);
  gtk_box_append(GTK_BOX(left_box), spacer);
}

static void pressedGestureLogin(GtkGestureClick *gesture, int n_press, double x, double y, gpointer data) {
  (void)gesture; // unused parameter
  (void)n_press; // unused parameter
  (void)x;       // unused parameter
  (void)y;       // unused parameter

  GtkWidget *stack = (GtkWidget *)data;
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "register");
}

static void pressedGestureRegister(GtkGestureClick *gesture, int n_press, double x, double y, gpointer data) {
  (void)gesture;  // unused parameter
  (void)n_press;  // unused parameter
  (void)x;        // unused parameter
  (void)y;        // unused parameter

  GtkWidget *stack = (GtkWidget *)data;
  gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");
}
