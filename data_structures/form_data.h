#ifndef FORM_DATA_H
#define FORM_DATA_H

#include <gtk/gtk.h>

typedef struct
{
    GtkWidget *e1, *e2, *e3, *e4, *e5, *e6,
        *p1, *p2, *p3, *p4, *p5, *p6,
        *cb_schedulable, *cb_combine_all,
        *cb_rm, *cb_edf, *cb_llf;

} form_data;

#endif