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


/*
*   This function is responsible for initializing the gtk widgets and for starting the gtk main loop
*/
void WCO_GUI_Start()
{
    //Init the gtk. It is posible to give the arguments from the main function into this init function
    gtk_init(NULL, NULL);

    //Set up the gtk builder from the glade xml file
    MyGUI.MyBuilder = gtk_builder_new_from_file("MyApp.glade");

    //Set up the gtk widgets with the gtk builder
    MyGUI.MyWindow1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyWindow"));
    MyGUI.MyFixed1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed1"));
    MyGUI.MyWorksheetFixed[0] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed2"));
    MyGUI.MyWorksheetFixed[1] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed3"));
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


    
    
    //connecting the signalls which were initilized by glade with the programm
    gtk_builder_connect_signals(MyGUI.MyBuilder, NULL);

    //show the widgets in the window
    gtk_widget_show(MyGUI.MyWindow1);

    //init the gui
    WCO_GUI_Init();

    //starts the main loop. 
    //to interrupt this main loop to carry out other functions is not possible. This functions have to be set up in a seperate thread
    //but be carefull. GTK is not really thread save.
    gtk_main();
}

/*
*   This function is used to initialize the GUI struct 
*/
void WCO_GUI_Init()
{
    //diffrent flags are set;
    MyGUI.showPDF = _OFF;
    MyGUI.savePDF = _OFF;
    MyGUI.saveFolder = _OFF;
    MyGUI.showPNG = _OFF;

    //the label pointer is now set to the adress of the heap 
    MyGUI.label = malloc(3 * sizeof(char));
    
    //Every adress of the first "Spallte" gets now a additional adress in the heap for the two dimensional array
    for (int i = 0; i <= 2; i++)
    {
        MyGUI.label[i] = malloc(2 * sizeof(char));
    }

    //filling the two dimensional array with values which were used to display different label outputs
    sprintf(MyGUI.label[0], "Z");
    sprintf(MyGUI.label[1], "R");
    sprintf(MyGUI.label[2], " ");
    //Update the gui conditions
    WCO_GUI_Update_Addition();
    WCO_GUI_Update_Division();
    WCO_GUI_Update_Multiplication();
    WCO_GUI_Update_Division();
    WCO_GUI_Update_PermissionButton1();
}
    

/**********************************************************************************************************************/

/*
*   Called by pressing the X-Button or the close button
*   Closes the PDF-Viewer and the GTK Window
*/
void exitApp()
{
    //Closes the PDFViewer
    WCO_GUI_Close_PDFViewer();
    
    //quites from the gtk main loop
    gtk_main_quit();

    //stops the programm
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
    // disables the pdf show flag which stopps the loop in which a threads whait to display the pdf-viewer
    MyGUI.showPDF = _OFF;

    //closes okular via a system command
    system("killall okular");
}

/*
*   Return the status of the viewer
*   Is it on or off
*/
int WCO_GUI_Status_Get_PDFViewer()
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

/**********************************************************************************************************************/
/*
*   function is responsible to display the created pdf in the gtk window as an png
*/
void WCO_GUI_Show_Worksheet(int page)
{
    //this case is true if this generated pdf was the first one since starting the programm
    //this is necesserly because at the beginning the gtk-image is not initiliced
    if (WCO_GUI_Status_Get_ShowPNG())
    {
        //this removes the container in which the image is conatained
        //if this is not done the displayed pages lie on top of each other
        gtk_container_remove(GTK_CONTAINER(MyGUI.MyWorksheetFixed[page]), MyGUI.MyWorksheetImage[page]);
    }

    //Initializing a new gtk image from a given file
    MyGUI.MyWorksheetImage[page] = gtk_image_new_from_file(WCO_PNG_Get_FileName(page));

    //add the image to a new container
    gtk_container_add(GTK_CONTAINER(MyGUI.MyWorksheetFixed[page]), MyGUI.MyWorksheetImage[page]);

    //display the image
    gtk_widget_show(MyGUI.MyWorksheetImage[page]);

    //move the image to the left upor corner of the container
    gtk_fixed_move(GTK_FIXED(MyGUI.MyWorksheetFixed[page]), MyGUI.MyWorksheetImage[page], 0, 0);
}





