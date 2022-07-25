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



void WCO_GUI_Start()
{
    gtk_init(NULL, NULL);

    MyGUI.MyBuilder = gtk_builder_new_from_file("MyApp.glade");

    MyGUI.MyWindow1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyWindow"));
    MyGUI.MyFixed1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed1"));
    MyGUI.MyLabel1 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel1"));
    MyGUI.MyLabel2 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel2"));
    MyGUI.MyLabel3 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel3"));
    MyGUI.MyLabel4 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel4"));
    MyGUI.MyLabel5 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel5"));
    MyGUI.MyButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton1"));
    MyGUI.MyButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton2"));
    MyGUI.MyButton3 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton3"));
    MyGUI.MyButton4 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton4"));
    MyGUI.MyCheckButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton1"));
    MyGUI.MyCheckButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton2"));
    MyGUI.MyCheckButton3 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton3"));
    MyGUI.MyCheckButton4 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton4"));
    MyGUI.MyCheckButton5 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton5"));
    MyGUI.MyCheckButton6 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton6"));
    MyGUI.MyRadioButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton1"));
    MyGUI.MyRadioButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton2"));
    MyGUI.MySpinButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton1"));
    MyGUI.MySpinButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton2"));
    MyGUI.MySpinButton3 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton3"));
    MyGUI.MySpinButton4 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton4"));
    MyGUI.MySpinButton5 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton5"));
    MyGUI.MySpinButton6 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton6"));
    MyGUI.MySpinButton7 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton7"));
    MyGUI.MySpinButton8 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton8"));
    MyGUI.MySpinButton9 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton9"));
    MyGUI.MySpinButton10 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton10"));
    MyGUI.MySpinButton11 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton11"));
    MyGUI.MySpinButton12 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton12"));
    MyGUI.MySpinButton13 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton13"));
    MyGUI.MyFileChosserButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFileChosserButton1"));
    MyGUI.MyEntry1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyEntry1"));
    
    gtk_builder_connect_signals(MyGUI.MyBuilder, NULL);

    gtk_widget_show(MyGUI.MyWindow1);

    //WCO_GUI_Init();

    gtk_main();
}


void WCO_GUI_Init()
{
    MyGUI.showPDF = _OFF;
    MyGUI.savePDF = _OFF;
    MyGUI.saveFolder = _OFF;

    
    WCO_GUI_Update_Addition();
    WCO_GUI_Update_Division();
    WCO_GUI_Update_Multiplication();
    WCO_GUI_Update_Division();
    WCO_GUI_Update_PermissionButton1();
    
}
    

/**********************************************************************************************************************/

/*
*   Called by press the X-Button in the right uppor corner
*   Closes the PDF-Viewer and the GTK Window
*/
void exitApp()
{
    WCO_GUI_Close_PDFViewer();
    gtk_main_quit();
    exit(0);
}


/*
*   Starts the PDF-Viewer
*/
void WCO_GUI_Start_PDFViewer()
{
    MyGUI.showPDF = _ON;
}

/*
*   Closes the PDF-Viewer
*/
void WCO_GUI_Close_PDFViewer()
{
    MyGUI.showPDF = _OFF;
    system("killall okular");
}

/*
*   Return the status of the viewer
*   Is it on or off
*/
int WCO_GUI_Status_PDFViewer()
{
    return MyGUI.showPDF;
}

/**********************************************************************************************************************/

/*
*   Shows the final task-pdf
*/
static void *WCO_GUI_PDFViewer_Thread1()
{
    //Calling via a System call the okular pdf-viewer
    system(MyPDF.systemOpenFile[_Tasks]);

    return NULL;
}

/*
*   Shows the final solution-pdf
*/
static void *WCO_GUI_PDFViewer_Thread2()
{
    //Calling via a System call the ocular pdf-viewer
    system(MyPDF.systemOpenFile[_Solutions]);

    return NULL;
}

/*
*   This is a Thread which handles the PDF_Viewer Thread
*/
void *WCO_GUI_PDFViewer()
{
    while(1)
    {
        while(MyGUI.showPDF)
        {
            //initialising tow instanzes of Threads
            pthread_t thread_id3;
            pthread_t thread_id4;

            //Creat the Thread and teeling the function the function which have to be execute
            pthread_create(&thread_id3, NULL, WCO_GUI_PDFViewer_Thread1, NULL);
            pthread_create(&thread_id4, NULL, WCO_GUI_PDFViewer_Thread2, NULL);

            //Joining the Threads
            pthread_join(thread_id3, NULL);
            pthread_join(thread_id4, NULL);
        }
    }
}





