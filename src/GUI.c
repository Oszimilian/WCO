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
#include <cairo.h>

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

#include "main.h"



/*
*   This function is responsible for initializing the gtk widgets and for starting the gtk main loop
*/
void WCO_GUI_Start()
{
    //Init the gtk. It is posible to give the arguments from the main function into this init function
    gtk_init(NULL, NULL);

    
    //Set up the gtk builder from the glade xml file
    WCO_GUI_Ref()->MyBuilder = gtk_builder_new_from_file("glade/MyApp.glade");
    

    //Set up the gtk widgets with the gtk builder
    WCO_GUI_Ref()->MyWindow1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyWindow"));

    WCO_GUI_Ref()->MyFixed1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFixed1"));
    WCO_GUI_Ref()->MyWorksheetFixed[0] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFixed2"));
    WCO_GUI_Ref()->MyWorksheetFixed[1] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFixed3"));

    //MyGUI.MyLabel1 = GTK_LABEL(gtk_builder_get_object(MyGUI.MyBuilder, "MyLabel1"));
    WCO_GUI_Ref()->MyLabel2 = GTK_LABEL(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyLabel2"));
    WCO_GUI_Ref()->MyLabel3 = GTK_LABEL(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyLabel3"));
    WCO_GUI_Ref()->MyLabel4 = GTK_LABEL(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyLabel4"));
    WCO_GUI_Ref()->MyLabel5 = GTK_LABEL(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyLabel5"));

    WCO_GUI_Ref()->MyButton1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyButton1"));
    //MyGUI.MyButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton2"));
    WCO_GUI_Ref()->MyButton3 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyButton3"));
    WCO_GUI_Ref()->MyButton4 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyButton4"));
    //MyGUI.MyButton5 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyButton5"));

    WCO_GUI_Ref()->MyCheckButton1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton1"));
    WCO_GUI_Ref()->MyCheckButton2 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton2"));
    WCO_GUI_Ref()->MyCheckButton3 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton3"));
    WCO_GUI_Ref()->MyCheckButton4 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton4"));
    WCO_GUI_Ref()->MyCheckButton5 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton5"));
    WCO_GUI_Ref()->MyCheckButton6 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton6"));
    WCO_GUI_Ref()->MyCheckButton7 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton7"));
    WCO_GUI_Ref()->MyCheckButton8 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton8"));
    WCO_GUI_Ref()->MyCheckButton9 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton9"));
    WCO_GUI_Ref()->MyCheckButton10 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton10"));
    WCO_GUI_Ref()->MyCheckButton11 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton11"));
    WCO_GUI_Ref()->MyCheckButton12 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton12"));
    WCO_GUI_Ref()->MyCheckButton13 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyCheckButton13"));

    //MyGUI.MyRadioButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton1"));
    //MyGUI.MyRadioButton2 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MyRadioButton2"));

    //MyGUI.MySpinButton1 = GTK_WIDGET(gtk_builder_get_object(MyGUI.MyBuilder, "MySpinButton1"));
    WCO_GUI_Ref()->MySpinButton2 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton2"));
    WCO_GUI_Ref()->MySpinButton3 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton3"));
    WCO_GUI_Ref()->MySpinButton4 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton4"));
    WCO_GUI_Ref()->MySpinButton5 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton5"));
    WCO_GUI_Ref()->MySpinButton6 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton6"));
    WCO_GUI_Ref()->MySpinButton7 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton7"));
    WCO_GUI_Ref()->MySpinButton8 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton8"));
    WCO_GUI_Ref()->MySpinButton9 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton9"));
    WCO_GUI_Ref()->MySpinButton10 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton10"));
    WCO_GUI_Ref()->MySpinButton11 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton11"));
    WCO_GUI_Ref()->MySpinButton12 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton12"));
    WCO_GUI_Ref()->MySpinButton13 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton13"));
    WCO_GUI_Ref()->MySpinButton14 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton14"));
    WCO_GUI_Ref()->MySpinButton15 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton15"));
    WCO_GUI_Ref()->MySpinButton16 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton16"));
    WCO_GUI_Ref()->MySpinButton17 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MySpinButton17"));
    
    WCO_GUI_Ref()->MyFileChooserButton1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFileChosserButton1"));

    

    WCO_GUI_Ref()->MyEntry1 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyEntry1"));
    WCO_GUI_Ref()->MyEntry2 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyEntry2"));

    WCO_GUI_Ref()->MyStackSwitcher2 = GTK_STACK_SWITCHER(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyStackSwitcher2"));
    WCO_GUI_Ref()->MyStack2 = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyStack2"));
    WCO_GUI_Ref()->MySettingsFixed[0] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFixed4"));
    WCO_GUI_Ref()->MySettingsFixed[1] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyFixed5"));

    WCO_GUI_Ref()->MyDrawArea[0] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyDrawArea1"));
    WCO_GUI_Ref()->MyDrawArea[1] = GTK_WIDGET(gtk_builder_get_object(WCO_GUI_Ref()->MyBuilder, "MyDrawArea2"));


    
    
    //connecting the signalls which were initilized by glade with the programm
    gtk_builder_connect_signals(WCO_GUI_Ref()->MyBuilder, NULL);

    //show the widgets in the window
    gtk_widget_show(WCO_GUI_Ref()->MyWindow1);

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
    WCO_GUI_Ref()->savePDF = _OFF;
    WCO_GUI_Ref()->saveFolder = _OFF;
    WCO_GUI_Ref()->showPNG = _OFF;

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
    if(WCO_GUI_Ref()->MySettingsFixed[0] == gtk_stack_get_visible_child(GTK_STACK(WCO_GUI_Ref()->MyStack2)))
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
/*
void WCO_GUI_Show_Worksheet(int page)
{
    //this case is true if this generated pdf was the first one since starting the programm
    //this is necesserly because at the beginning the gtk-image is not initiliced

    if (*(int*)WCO_PNG_Get(get_showPNG))
    {
        //this removes the container in which the image is conatained
        //if this is not done the displayed pages lie on top of each other
        gtk_container_remove(GTK_CONTAINER(WCO_GUI_Ref()->MyWorksheetFixed[page]), WCO_GUI_Ref()->MyWorksheetImage[page]);
        
    }

    //Initializing a new gtk image from a given file
    WCO_GUI_Ref()->MyWorksheetImage[page] = gtk_image_new_from_file(WCO_PNG_Get_FileName(page));

    //add the image to a new container
    gtk_container_add(GTK_CONTAINER(WCO_GUI_Ref()->MyWorksheetFixed[page]), WCO_GUI_Ref()->MyWorksheetImage[page]);

    //display the image
    gtk_widget_show(WCO_GUI_Ref()->MyWorksheetImage[page]);

    //move the image to the left upor corner of the container
    gtk_fixed_move(GTK_FIXED(WCO_GUI_Ref()->MyWorksheetFixed[page]), WCO_GUI_Ref()->MyWorksheetImage[page], 0, 0);
}
*/

void WCO_GUI_Show_Worksheet(int page)
{
    cairo_pdf_surface_create(WCO_ENTRY(WCO_GUI_Get(folder_name)), HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]), HPDF_Page_GetHeight(WCO_PDF_Ref()->page[page]));
}



