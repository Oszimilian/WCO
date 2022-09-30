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
#include "main.h"


/*
*   called when the creat worksheet-button is pressed
*/
void MyButton1_Clicked(GtkButton *b)
{
    printf("\nButton One is clicked!\n");

    //starts creating the worksheet and if a error appears a message will be printet to the terminal
    if(WCO_GUI_Get_Stack() == task_setting)
    {
        WCO_Worksheet_Task_Start();
    }
    if(WCO_GUI_Get_Stack() == fraction_setting)
    {
        WCO_Worksheet_Fraction_Start();
    }
}

void MyButton2_Clicked(GtkButton *b){}


/**********************************************************************************************************************/

void MyCheckButton1_Toggled(GtkCheckButton *b){WCO_GUI_Update(_ADDITION);}

void MyCheckButton2_Toggled(GtkCheckButton *b){WCO_GUI_Update(_SUBTRACTION);}

void MyCheckButton3_Toggled(GtkCheckButton *b){WCO_GUI_Update(_MULTIPLICATION);}

void MyCheckButton4_Toggled(GtkCheckButton *b){WCO_GUI_Update(_DIVISION);}

/**********************************************************************************************************************/
    
void MyCheckButton5_Toggled(GtkCheckButton *b){WCO_GUI_Update_Baseboard();}
void MyCheckButton6_Toggled(GtkCheckButton *b){WCO_GUI_Update_Baseboard();}
void MyCheckButton11_Changed(GtkCheckButton *b){WCO_GUI_Update_Baseboard();}
void MyEntry2_Changed(GtkCheckButton *b){WCO_GUI_Update_Baseboard();}

/**********************************************************************************************************************************************************************************/

void MyRadioButton1_Toggled(GtkRadioButton *b){}

void MyRadioButton2_Toggled(GtkRadioButton *b){}

void MySpinButton1_Changed(GtkSpinButton *s){}

/**********************************************************************************************************************************************************************************/


void MySpinButton2_Changed(GtkSpinButton *s){WCO_GUI_Update(_ADDITION);} 
void MySpinButton8_Changed(GtkSpinButton *s){WCO_GUI_Update(_ADDITION);} 

void MySpinButton5_Changed(GtkSpinButton *s){WCO_GUI_Update(_SUBTRACTION);} 
void MySpinButton9_Changed(GtkSpinButton *s){WCO_GUI_Update(_SUBTRACTION);} 

void MySpinButton3_Changed(GtkSpinButton *s){WCO_GUI_Update(_MULTIPLICATION);} 
void MySpinButton4_Changed(GtkSpinButton *s){WCO_GUI_Update(_MULTIPLICATION);} 

void MySpinButton6_Changed(GtkSpinButton *s){WCO_GUI_Update(_DIVISION);} 
void MySpinButton7_Changed(GtkSpinButton *s){WCO_GUI_Update(_DIVISION);} 


/**********************************************************************************************************************/

void MySpinButton10_Changed(GtkSpinButton *s){WCO_GUI_Update(_ADDITION);} 

void MySpinButton11_Changed(GtkSpinButton *s){WCO_GUI_Update(_SUBTRACTION);} 

void MySpinButton12_Changed(GtkSpinButton *s){WCO_GUI_Update(_MULTIPLICATION);} 

void MySpinButton13_Changed(GtkSpinButton *s){WCO_GUI_Update(_DIVISION);} 

/**********************************************************************************************************************/

void MyFileChosserButton1_FileSet(GtkFileChooserButton *f)
{

}

void MyEntry1_Changed(GtkEntry *e)
{
    int i = _FALSE;
    WCO_GUI_Set(&i, savePDF);
    WCO_GUI_Update_CreateButton();
}

void MyButton4_Clicked(GtkButton *b)
{
    int i = _TRUE;
    WCO_GUI_Set(&i, savePDF);
    //WCO_GUI_Update_FileName();
    WCO_GUI_Update_CreateButton();
}

void MyButtonTest_Clicked()
{


    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Chosse a folder", GTK_WINDOW(WCO_GUI_Ref()->MyWindow1), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());

    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    else
        g_print("You pressed Cancel\n");
    

    int i = _TRUE;
    WCO_GUI_Set(&i, saveFolder);
    WCO_GUI_Update_CreateButton();

    int fileNameLeangh = strlen(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    WCO_PDF_SetFoldername(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));


    if (fileNameLeangh >= 1)
    {
        WCO_PDF_SetFilename(WCO_ENTRY(WCO_GUI_Get(entry_1)), _Tasks);
        WCO_PDF_SetFilename(WCO_ENTRY(WCO_GUI_Get(entry_1)), _Solutions);
    }

    
    gtk_widget_destroy(dialog);
}

/**********************************************************************************************************************/

void MyButton5_Clicked(GtkButton *b){WCO_Worksheet_Fraction_Start(); }

/**********************************************************************************************************************/

void MySpinButton14_Changed(GtkSpinButton *b){}

void MySpinButton15_Changed(GtkSpinButton *b){}

void MySpinButton16_Changed(GtkSpinButton *b){}

void MySpinButton17_Changed(GtkSpinButton *b){}

/**********************************************************************************************************************/

void MyCheckButton7_Changed(GtkCheckButton *b){WCO_GUI_Update(_ADDITION);}

void MyCheckButton8_Changed(GtkCheckButton *b){WCO_GUI_Update(_SUBTRACTION);}

void MyCheckButton9_Changed(GtkCheckButton *b){WCO_GUI_Update(_MULTIPLICATION);}

void MyCheckButton10_Changed(GtkCheckButton *b){WCO_GUI_Update(_DIVISION);}

/**********************************************************************************************************************/

void MyStackSwitcher2_Changed(){}

/**********************************************************************************************************************/

void MyCheckButton12_Changed(GtkCheckButton *b){}

void MyCheckButton13_Changed(GtkCheckButton *b){} 



