#include <gtk/gtk.h>

void start_clicked(GtkWidget *widget, gpointer data) {
    
  g_print("start clicked\n");
}

void reset_clicked(GtkWidget *widget, gpointer data) {
    
  g_print("reset clicked\n");
}

int main(int argc, char *argv[])
{
    static GtkWidget *window = NULL;

    GtkWidget *main_grid, *tasks_grid;
    GtkWidget *tasks_vbox, *algo_hbox;

    GtkWidget *t1_label, *t2_label, *t3_label,
    *t4_label, *t5_label, *t6_label;

    GtkWidget *start_button, *reset_button;

    GtkWidget *t1_einput, *t2_einput, *t3_einput,
    *t4_einput, *t5_einput, *t6_einput, *t1_pinput, 
    *t2_pinput, *t3_pinput, *t4_pinput, *t5_pinput,
    *t6_pinput, *cb_schedulable, *cb_rm,  *cb_edf, *cb_llf,
    *cb_combine_all;

    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *frame_horz;
    GtkWidget *frame_vert;

    /* Initialize GTK */
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 430, 400);
    gtk_window_set_title(GTK_WINDOW(window), "SOA - Project 3: Real Time Scheduling");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    main_grid = gtk_grid_new();

    tasks_grid = gtk_grid_new();
    gtk_grid_set_column_spacing (tasks_grid, 10);
    gtk_grid_set_row_spacing (tasks_grid, 10);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit),
                     NULL);

    start_button = gtk_button_new_with_label("Start");
    reset_button = gtk_button_new_with_label("Reset");

    g_signal_connect(G_OBJECT(start_button), "clicked", 
      G_CALLBACK(start_clicked), NULL);

    g_signal_connect(G_OBJECT(reset_button), "clicked", 
      G_CALLBACK(reset_clicked), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    tasks_vbox = gtk_vbox_new(FALSE, 0);
    algo_hbox = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_grid);

    frame_horz = gtk_frame_new("Tasks Setup");
    frame_vert = gtk_frame_new ("Algorithms");
    gtk_box_pack_start(GTK_BOX(tasks_vbox), frame_horz, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(algo_hbox), frame_vert, TRUE, TRUE, 10);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_set_spacing (GTK_BOX (vbox), 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(frame_horz), vbox);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_set_spacing (GTK_BOX (hbox), 10);
    gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
    gtk_container_add (GTK_CONTAINER (frame_vert), hbox);

    t1_label = gtk_label_new("Task 1");
    t2_label = gtk_label_new("Task 2");
    t3_label = gtk_label_new("Task 3");
    t4_label = gtk_label_new("Task 4");
    t5_label = gtk_label_new("Task 5");
    t6_label = gtk_label_new("Task 6");

    t1_einput = gtk_entry_new();
    t2_einput = gtk_entry_new();
    t3_einput = gtk_entry_new();
    t4_einput = gtk_entry_new();
    t5_einput = gtk_entry_new();
    t6_einput = gtk_entry_new();

    t1_pinput = gtk_entry_new();
    t2_pinput = gtk_entry_new();
    t3_pinput = gtk_entry_new();
    t4_pinput = gtk_entry_new();
    t5_pinput = gtk_entry_new();
    t6_pinput = gtk_entry_new();

    cb_schedulable = gtk_check_button_new_with_label("Schedulable");
    cb_combine_all = gtk_check_button_new_with_label("Combine All");

    cb_rm = gtk_check_button_new_with_label("RM");
    cb_edf = gtk_check_button_new_with_label("EDF");
    cb_llf = gtk_check_button_new_with_label("LLF");

    gtk_grid_attach(GTK_GRID(tasks_grid), t1_label,  0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t1_einput, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t1_pinput, 2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t2_label,  0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t2_einput, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t2_pinput, 2, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t3_label,  0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t3_einput, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t3_pinput, 2, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t4_label,  0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t4_einput, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t4_pinput, 2, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t5_label,  0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t5_einput, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t5_pinput, 2, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t6_label,  0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t6_einput, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), t6_pinput, 2, 5, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), cb_schedulable, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), cb_combine_all, 2, 6, 1, 1);

    gtk_container_add(GTK_CONTAINER(vbox), tasks_grid);

    gtk_box_pack_start (GTK_BOX (hbox), cb_rm, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cb_edf, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), cb_llf, TRUE, TRUE, 0);

    gtk_grid_attach(GTK_GRID(main_grid), tasks_vbox, 0, 0, 4, 1);
    gtk_grid_attach(GTK_GRID(main_grid), algo_hbox, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), start_button, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), reset_button, 3, 2, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}