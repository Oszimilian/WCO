#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "hpdf.h"
#include "GUI_Call.h"
#include "GUI.h"
#include "PDF.h"
#include "Worksheet.h"







int main(void)
{

    


    pthread_t thread_id1;




    pthread_create(&thread_id1, NULL, WCO_GUI_PDFViewer, NULL);


    WCO_GUI_Start();

    //pthread_join(thread_id1, NULL);
    //pthread_join(thread_id2, NULL);
    //pthread_join(thread_id5, NULL);


    //pthread_exit(NULL);
    return EXIT_SUCCESS;
    //exit(0);
}




