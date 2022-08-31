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
#include <MagickWand/MagickWand.h>

#include "hpdf.h"
#include "GUI_Call.h"
#include "GUI_Status.h"
#include "GUI_Update.h"
#include "GUI.h"
#include "PDF.h"
#include "PNG.h"
#include "Worksheet_Baseboard.h"
#include "Worksheet_Creat_Fraction.h"
#include "Worksheet_Creat_Task.h"



/*
*   This function is responsible for initializing the gtk widgets and for starting the gtk main loop
*/
void WCO_GUI_Start()
{
    //Init the gtk. It is posible to give the arguments from the main function into this init function
    gtk_init(NULL, NULL);

    
    //Set up the gtk builder from the glade xml file
    MyGUI.MyBuilder = gtk_builder_new_from_file("glade/MyApp.glade");
    

    //Set up the gtk widgets with the gtk builder
    MyGUI.MyWindow1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyWindow"));

    MyGUI.MyFixed1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed1"));
    MyGUI.MyWorksheetFixed[0] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed2"));
    MyGUI.MyWorksheetFixed[1] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed3"));

    //MyGUI.MyLabel1 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel1"));
    MyGUI.MyLabel2 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel2"));
    MyGUI.MyLabel3 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel3"));
    MyGUI.MyLabel4 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel4"));
    MyGUI.MyLabel5 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel5"));

    MyGUI.MyButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton1"));
    //MyGUI.MyButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton2"));
    MyGUI.MyButton3 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton3"));
    MyGUI.MyButton4 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton4"));
    //MyGUI.MyButton5 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton5"));

    MyGUI.MyCheckButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton1"));
    MyGUI.MyCheckButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton2"));
    MyGUI.MyCheckButton3 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton3"));
    MyGUI.MyCheckButton4 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton4"));
    MyGUI.MyCheckButton5 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton5"));
    MyGUI.MyCheckButton6 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton6"));
    MyGUI.MyCheckButton7 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton7"));
    MyGUI.MyCheckButton8 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton8"));
    MyGUI.MyCheckButton9 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton9"));
    MyGUI.MyCheckButton10 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton10"));
    MyGUI.MyCheckButton11 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyCheckButton11"));

    //MyGUI.MyRadioButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton1"));
    //MyGUI.MyRadioButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton2"));

    //MyGUI.MySpinButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton1"));
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
    MyGUI.MySpinButton14 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton14"));
    MyGUI.MySpinButton15 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton15"));
    MyGUI.MySpinButton16 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton16"));
    MyGUI.MySpinButton17 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton17"));
    
    MyGUI.MyFileChosserButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFileChosserButton1"));

    MyGUI.MyEntry1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyEntry1"));
    MyGUI.MyEntry2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyEntry2"));

    MyGUI.MyStackSwitcher2 = GTK_STACK_SWITCHER(gtk_builder_get_object(MyGUI.MyBuilder, "MyStackSwitcher2"));
    MyGUI.MyStack2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyStack2"));
    MyGUI.MySettingsFixed[0] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed4"));
    MyGUI.MySettingsFixed[1] = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyFixed5"));
    
    
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
    MyGUI.savePDF = _OFF;
    MyGUI.saveFolder = _OFF;
    MyGUI.showPNG = _OFF;

}
    

/**********************************************************************************************************************/

/*
*   Called by pressing the X-Button or the close button
*   Closes the PDF-Viewer and the GTK Window
*/
void exitApp()
{
    //quites from the gtk main loop
    gtk_main_quit();

    //stops the programm
    exit(0);
}

/**********************************************************************************************************************/

int WCO_GUI_Get_Stack()
{
    if(MyGUI.MySettingsFixed[0] == gtk_stack_get_visible_child(GTK_STACK(MyGUI.MyStack2)))
    {
        return task_setting;
    }else{
        return fraction_setting;
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

    if (*(int*)WCO_PNG_Get(get_showPNG))
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





