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
*   called when the creat worksheet-button is pressed
*/
void MyButton1_Clicked(GtkButton *b)
{
    printf("Button One is clicked! \n\n\n");

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
    int i = _TRUE;
    WCO_GUI_Set(&i, saveFolder);
    WCO_GUI_Update_CreateButton();
}

void MyEntry1_Changed(GtkEntry *e)
{
    int i = _FALSE;
    WCO_GUI_Set(&i, savePDF);
    WCO_GUI_Update_FileName();
    WCO_GUI_Update_CreateButton();
}

void MyButton4_Clicked(GtkButton *b)
{
    int i = _TRUE;
    WCO_GUI_Set(&i, savePDF);
    WCO_GUI_Update_CreateButton();
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
