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
#include "PNG.h"
#include <MagickWand/MagickWand.h>







//Test
int main(void)
{
    //calls the init function to preset the baseboardflag and the threashold value
    WCO_Worksheet_Init();

    //calls the init function to set the folder and file name for the convertet png
    WCO_PNG_Init();
    
    //initialises a thread instance and creats a thread which calls the function WCO_GUI_PDFViewer 
    //pthread_t thread_id1;
    //pthread_create(&thread_id1, NULL, WCO_GUI_PDFViewer, NULL);

    //Starts the GTK GUI Window
    WCO_GUI_Start();

    //Whaits till the thread is closed before the programm disapears
    //pthread_exit(NULL);

    return EXIT_SUCCESS;
}




