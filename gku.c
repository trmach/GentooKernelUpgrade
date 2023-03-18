#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk-3.0/gtk/gtk.h>

#define ENTRY_BUFFER 100

static int insert_entries(GtkWidget * list_box) {       //* Accept the list box where we insert our list of targets

  FILE * fp;                                            //* Read command output to file
  char entry_buf[ENTRY_BUFFER];                         //* buffer for our entries
  int num_targets = 0;

  fp = popen("/usr/bin/eselect kernel list", "r");      //* Execute command and read
  if (fp == NULL) {                                     //* Check that execution was successful
    fprintf(stderr, "Failed to run command.\n");        //* If not, error and exit.
    exit(1);
  }

  fgets(entry_buf, sizeof(entry_buf), fp); //* AvAiLaBlE kErNeL sYmLiNk TaRgEtS:

  while(fgets(entry_buf, sizeof(entry_buf), fp) != NULL) {           //* I can't believe this actually works
    GtkWidget * symlinkTarget = gtk_label_new(entry_buf);
    gtk_list_box_insert(list_box, symlinkTarget, num_targets);
    num_targets++;
  }
  
  fclose(fp);

  return 0;

}

static void update_button(GtkButton *button, gpointer data) {

  char * buf = malloc(100 * sizeof(char));
  static int n = 0;
  n++;
  sprintf(buf, "%d", n);
  gtk_button_set_label(button, buf);
  free(buf);

}

static int activate(GtkApplication* app, gpointer user_data) {

  GtkWidget *window, 
    *box,
    *list_box,
    *number_button, *cancel_button;
    //*radio1, *radio2, *radio3
  
  //* Open Window and set properties
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "bitchass");
  gtk_window_set_default_size(GTK_WINDOW (window), 640, 480);
  
  //* Make a box, not a button_box!
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_set_homogeneous(GTK_BOX (box), TRUE);

  gtk_container_add(GTK_CONTAINER (window), box);

  //* Button that does something fun
  number_button = gtk_button_new_with_label("0");
  g_signal_connect(number_button, "clicked", (G_CALLBACK (update_button)), NULL);

  //* Button that closes the window
  cancel_button = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  //* Radio buttons
  // radio1 = gtk_radio_button_new(NULL);
  // GtkWidget * entry = gtk_entry_new();
  // gtk_container_add(GTK_CONTAINER (radio1), entry);

  // radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1), "Second button");
  // radio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1), "Third Button");

  //* Here we want to create a list box with gtk_list_box_new()
  //* We want to add the list of kernel symlink targets as they are read in another function with gtk_list_box_insert()
  //* Finally determine the target number with gtk_list_box_get_selected_row(), perhaps triggered by a button press.
  list_box = gtk_list_box_new();
  insert_entries(list_box);

  //* Add buttons to container. It looks like hell.
    // gtk_box_pack_start(GTK_BOX (box), radio1, true, true, 2);
  // gtk_box_pack_start(GTK_BOX (box), radio2, true, true, 2);
  // gtk_box_pack_start(GTK_BOX (box), radio3, true, true, 2);
  gtk_box_pack_start(GTK_BOX (box), list_box, true, true, 2);
  gtk_box_pack_start(GTK_BOX (box), number_button, true, true, 9);
  gtk_box_pack_start(GTK_BOX (box), cancel_button, true, true, 9);

  //gtk_container_add(GTK_CONTAINER (window), box);

  gtk_widget_show_all(window);

  return 0;
  
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
