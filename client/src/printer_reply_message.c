#include "client.h"

static void params(GtkWidget *text, GtkWidget *sender, GtkWidget *align, GtkWidget *time) {
    gtk_label_set_line_wrap(GTK_LABEL(text), TRUE);
    gtk_label_set_selectable(GTK_LABEL(text), TRUE);
    gtk_widget_set_name(sender, "user_name_label");
    gtk_widget_set_name(time, "current_time");
    gtk_widget_set_halign(sender, GTK_ALIGN_START);
    gtk_widget_set_valign(sender, GTK_ALIGN_END);
    gtk_widget_set_halign(time, GTK_ALIGN_END);
    gtk_widget_set_valign(time, GTK_ALIGN_START);
    gtk_widget_set_halign(text, GTK_ALIGN_START);
    gtk_widget_set_hexpand(align, TRUE);
}

void printer_reply_message(GtkWidget *list, const char *message, const char *name) {
	GtkWidget *text = gtk_label_new(message);
	GtkWidget *align = gtk_label_new("");
	GtkWidget *sender = gtk_label_new(name);
	const char *time = time_doing();
    GtkWidget *time_label = gtk_label_new(time);
	GtkWidget *grid_box = gtk_grid_new();
	GtkWidget *grid = gtk_grid_new();

	params(text, sender, align, time_label);
    gtk_grid_insert_row(GTK_GRID(grid_box), 0);
    gtk_grid_insert_row(GTK_GRID(grid_box), 1);
    gtk_widget_set_hexpand(grid_box, FALSE);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    gtk_grid_attach(GTK_GRID(grid_box), sender, 0, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid_box), text, 0, 1, 1, 2);
    //gtk_grid_attach(GTK_GRID(grid_box), time_label, 0, 1, 2, 3);
    gtk_grid_attach(GTK_GRID(grid), align, 100, 0, 1, 99);
    gtk_grid_attach(GTK_GRID(grid), grid_box, 100, 0, 1, 1);
    gtk_list_box_insert(GTK_LIST_BOX(list), grid, -1);
    gtk_widget_show_all(list);
}
