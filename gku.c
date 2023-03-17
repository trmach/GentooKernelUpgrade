#include <stdio.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

static void print_bitchass (GtkWidget *widget, gpointer data) {
  g_print ("bitchass\n");
}

//static void update_button_label (GtkWidget *widget, gpointer data) {}

static void activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  int n = 0;
  char * button_text;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "bitchass");
  gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
  
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label (("bitchass\n%c"));
  g_signal_connect (button, "clicked", G_CALLBACK (print_bitchass), n);
  //g_signal_connect_swapped (button, "clicked", G_CALLBACK (NULL), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all (window);
  
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
