//#include <stdlib.h>
#include <gtk/gtk.h>
#include "data_structures/form_data.h"
#include "data_structures/settings.h"
#include "utils/beamerGenerator.h"
#include <string.h>

int MCD = 1;

void show_error(char *s)
{
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    s);
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void start_clicked(GtkWidget *widget, form_data *data)
{

    simulation_settings *settings = malloc(sizeof(settings) + 14 * sizeof(int));

    settings->combineAll = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(data->cb_combine_all));

    settings->rm = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(data->cb_rm));
    settings->edf = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(data->cb_edf));
    settings->llf = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(data->cb_llf));

    gchar *e1_text, *e2_text, *e3_text, *e4_text, *e5_text, *e6_text;
    gchar *p1_text, *p2_text, *p3_text, *p4_text, *p5_text, *p6_text;

    e1_text = gtk_entry_get_text(GTK_ENTRY(data->e1));
    e2_text = gtk_entry_get_text(GTK_ENTRY(data->e2));
    e3_text = gtk_entry_get_text(GTK_ENTRY(data->e3));
    e4_text = gtk_entry_get_text(GTK_ENTRY(data->e4));
    e5_text = gtk_entry_get_text(GTK_ENTRY(data->e5));
    e6_text = gtk_entry_get_text(GTK_ENTRY(data->e6));

    p1_text = gtk_entry_get_text(GTK_ENTRY(data->p1));
    p2_text = gtk_entry_get_text(GTK_ENTRY(data->p2));
    p3_text = gtk_entry_get_text(GTK_ENTRY(data->p3));
    p4_text = gtk_entry_get_text(GTK_ENTRY(data->p4));
    p5_text = gtk_entry_get_text(GTK_ENTRY(data->p5));
    p6_text = gtk_entry_get_text(GTK_ENTRY(data->p6));

    if ((settings->rm + settings->edf + settings->llf) == 0)
    {
        show_error("\n You must select at least one algorithm");
        return;
    }

    if (no_number(e1_text) || no_number(e2_text) || no_number(e3_text) || no_number(e4_text) || no_number(e5_text) || no_number(e6_text) || no_number(p1_text) || no_number(p2_text) || no_number(p3_text) || no_number(p4_text) || no_number(p5_text) || no_number(p6_text))
    {
        show_error("\n All fields used must be numeric");
        return;
    }

    if (strlen(e1_text) == 0)
    {
        show_error("\n The execution time #1 can not be empty");
        return;
    }

    if (strlen(e1_text) > 0 && strlen(p1_text) == 0)
    {
        show_error("\n The period can not be empty if the execution time is full");
        return;
    }

    settings->executionTimes[0] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e1)));
    settings->executionTimes[1] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e2)));
    settings->executionTimes[2] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e3)));
    settings->executionTimes[3] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e4)));
    settings->executionTimes[4] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e5)));
    settings->executionTimes[5] = atoi(gtk_entry_get_text(GTK_ENTRY(data->e6)));

    settings->periods[0] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p1)));
    settings->periods[1] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p2)));
    settings->periods[2] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p3)));
    settings->periods[3] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p4)));
    settings->periods[4] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p5)));
    settings->periods[5] = atoi(gtk_entry_get_text(GTK_ENTRY(data->p6)));

    for (int i = 0; i < 6; i++)
    {
        if (settings->executionTimes[i] > settings->periods[i])
        {
            show_error("\n The period can not be less than the execution time");
            return;
        }

        if (settings->periods[i] > 0 && settings->executionTimes[i] == 0)
        {
            show_error("\n The execution time can not be empty if the period field is full");
            return;
        }
    }

    //compute least common multiple
    for (int i = 0; i < 6; i++)
    {
        if (settings->periods[i] > 0)
        {
            MCD = mcm(MCD, settings->periods[i]);
        }
    }
    settings->MCD = MCD;

    //Verificacion de datos, esto se quita
    for (int i = 0; i < 6; i++)
    {
        printf("pos: %d executionTimes: %d periods %d\n", i, settings->executionTimes[i], settings->periods[i]);
    }

    printf("MCD %d \n", settings->MCD);

    //La comente pq se cae, pero con las lineas de arriba se ve que estoy pasando los datos
    //bien, o sea en el arreglo
    generateBeamer(settings);
}

void reset_clicked(GtkWidget *widget, gpointer data)
{

    g_print("reset clicked\n");
}

int no_number(char num[])
{
    if (strlen(num) == 0)
    {
        return FALSE;
    }

    for (int i = 0; i < strlen(num); i++)
    {
        if (!isdigit(num[i]))
        {
            return TRUE;
        }
    }
    return FALSE;
}

int mcd(int n1, int n2)
{
    int mcd = 0;
    int a = max(n1, n2);
    int b = min(n1, n2);

    do
    {
        mcd = b;
        b = a % b;
        a = mcd;
    } while (b != 0);
    return mcd;
}

int mcm(int n1, int n2)
{

    int mcm = 0;
    int a = max(n1, n2);
    int b = min(n1, n2);
    mcm = round((a / mcd(a, b)) * b);
    return mcm;
}

int min(int n1, int n2)
{
    if (n1 < n2)
    {
        return n1;
    }
    return n2;
}

int max(int n1, int n2)
{
    if (n1 > n2)
    {
        return n1;
    }
    return n2;
}

int main(int argc, char *argv[])
{

    form_data f_data;

    static GtkWidget *window = NULL;

    GtkWidget *main_grid, *tasks_grid,
        *tasks_vbox, *algo_hbox;

    GtkWidget *header_exec_label, *header_period_label, *t1_label, *t2_label, *t3_label,
        *t4_label, *t5_label, *t6_label;

    GtkWidget *start_button, *reset_button;

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
    gtk_grid_set_column_spacing(tasks_grid, 10);
    gtk_grid_set_row_spacing(tasks_grid, 10);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit),
                     NULL);

    start_button = gtk_button_new_with_label("Start");
    reset_button = gtk_button_new_with_label("Reset");

    g_signal_connect(G_OBJECT(start_button), "clicked",
                     G_CALLBACK(start_clicked), &f_data);

    g_signal_connect(G_OBJECT(reset_button), "clicked",
                     G_CALLBACK(reset_clicked), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    tasks_vbox = gtk_vbox_new(FALSE, 0);
    algo_hbox = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_grid);

    frame_horz = gtk_frame_new("Tasks Setup");
    frame_vert = gtk_frame_new("Algorithms");
    gtk_box_pack_start(GTK_BOX(tasks_vbox), frame_horz, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(algo_hbox), frame_vert, TRUE, TRUE, 10);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_set_spacing(GTK_BOX(vbox), 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(frame_horz), vbox);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_set_spacing(GTK_BOX(hbox), 10);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_container_add(GTK_CONTAINER(frame_vert), hbox);

    header_exec_label = gtk_label_new("Execution time");
    header_period_label = gtk_label_new("Period");

    t1_label = gtk_label_new("Task 1");
    t2_label = gtk_label_new("Task 2");
    t3_label = gtk_label_new("Task 3");
    t4_label = gtk_label_new("Task 4");
    t5_label = gtk_label_new("Task 5");
    t6_label = gtk_label_new("Task 6");

    f_data.e1 = gtk_entry_new();
    f_data.e2 = gtk_entry_new();
    f_data.e3 = gtk_entry_new();
    f_data.e4 = gtk_entry_new();
    f_data.e5 = gtk_entry_new();
    f_data.e6 = gtk_entry_new();

    f_data.p1 = gtk_entry_new();
    f_data.p2 = gtk_entry_new();
    f_data.p3 = gtk_entry_new();
    f_data.p4 = gtk_entry_new();
    f_data.p5 = gtk_entry_new();
    f_data.p6 = gtk_entry_new();

    f_data.cb_combine_all = gtk_check_button_new_with_label("Show all in slides");
    f_data.cb_rm = gtk_check_button_new_with_label("RM");
    f_data.cb_edf = gtk_check_button_new_with_label("EDF");
    f_data.cb_llf = gtk_check_button_new_with_label("LLF");

    gtk_grid_attach(GTK_GRID(tasks_grid), header_exec_label, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), header_period_label, 2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t1_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e1, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p1, 2, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t2_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e2, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p2, 2, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t3_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e3, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p3, 2, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t4_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e4, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p4, 2, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t5_label, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e5, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p5, 2, 5, 1, 1);

    gtk_grid_attach(GTK_GRID(tasks_grid), t6_label, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.e6, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(tasks_grid), f_data.p6, 2, 6, 1, 1);

    gtk_container_add(GTK_CONTAINER(vbox), tasks_grid);

    gtk_box_pack_start(GTK_BOX(hbox), f_data.cb_rm, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), f_data.cb_edf, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), f_data.cb_llf, TRUE, TRUE, 0);

    gtk_grid_attach(GTK_GRID(main_grid), tasks_vbox, 0, 0, 4, 1);
    gtk_grid_attach(GTK_GRID(main_grid), algo_hbox, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), start_button, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), reset_button, 3, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), f_data.cb_combine_all, 2, 2, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}