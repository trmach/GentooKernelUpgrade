#include <stdio.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

#define ENTRY_BUFFER 100

void read_entries() {

  FILE * fp; //* Read command output to file
  char * entry_buf[ENTRY_BUFFER];    //* buffer for our entries

  fp = popen("/usr/bin/eselect kernel list", "r"); //* Execute command and read
  if (fp == NULL) {                                //* Check that execution was successful
    fprintf(stderr, "Failed to run command.\n");   //* If not, error and exit.
    exit(1);
  }

  while(fgets(entry_buf, sizeof(entry_buf), fp) != NULL) {           //* AvAiLaBlE kErNeL sYmLiNk TaRgEtS:
    printf("%s", entry_buf);
  }
  
  if (entry_buf == NULL) {
    fclose(fp);
  }

}

static void update_button(GtkWidget *button, gpointer data) {

  char * buf = malloc(100 * sizeof(char));
  static int n = 0;
  n++;
  sprintf(buf, "%d", n);
  gtk_button_set_label(button, buf);
  read_entries();
  free(buf);

}

static int activate(GtkApplication* app, gpointer user_data) {

  GtkWidget *window, *number_button, *cancel_button, *button_box;
  
  //* Open Window and set properties
  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW (window), "bitchass");
  gtk_window_set_default_size(GTK_WINDOW (window), 640, 480);
  
  //* Thing that contains buttons
  button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER (window), button_box);

  //* Button that does something fun
  number_button = gtk_button_new_with_label("0");
  g_signal_connect(number_button, "clicked", (G_CALLBACK (update_button)), NULL);

  //* Button that closes the window
  cancel_button = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  //* Add buttons to container. It looks like hell.
  gtk_container_add(GTK_CONTAINER (button_box), number_button);
  gtk_container_add(GTK_CONTAINER (button_box), cancel_button);
  

  gtk_widget_show_all(window);
  
}

int main (int argc, char **argv) {

  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;

}
