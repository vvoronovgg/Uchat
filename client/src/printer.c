#include "client.h"

static void params(GtkWidget *sender, GtkWidget *align, const char *key) {
    gtk_widget_set_name(sender, key);
    gtk_widget_set_halign(sender,GTK_ALIGN_END );
    gtk_widget_set_valign(sender, GTK_ALIGN_START);
    gtk_widget_set_hexpand(align, TRUE);
}

void printer(GtkWidget *list, const char *login) {
    GtkWidget *sender = gtk_label_new(login);
	GtkWidget *align = gtk_label_new("");
	GtkWidget *grid_box = gtk_grid_new();
	GtkWidget *grid = gtk_grid_new();
    
	params(sender, align, login);
    gtk_grid_insert_row(GTK_GRID(grid_box), 0);
    gtk_widget_set_hexpand(grid_box, FALSE);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    gtk_grid_attach(GTK_GRID(grid_box), sender, 0, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), align, 1, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), grid_box, 1, 0, 1, 1);
    gtk_list_box_insert(GTK_LIST_BOX(list), grid, -1);
    gtk_widget_show_all(list);
}
