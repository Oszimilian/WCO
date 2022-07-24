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



void MyButton1_Clicked(GtkButton *b)
{
    printf("Button One is clicked! \n");


    WCO_PDF_SetFilename("Aufgaben", _Tasks);
    WCO_PDF_SetFilename("Solution", _Solutions);

    if (!WCO_GUI_Status_PDFViewer()) WCO_GUI_Start_PDFViewer();

    WCO_Worksheet_Create_Start();
}

void MyButton2_Clicked(GtkButton *b)
{
    WCO_GUI_Close_PDFViewer();
}

void MyCheckButton1_Toggled(GtkCheckButton *b)
{

}

void MyCheckButton2_Toggled(GtkCheckButton *b)
{

}

void MyCheckButton3_Toggled(GtkCheckButton *b)
{

}

void MyCheckButton4_Toggled(GtkCheckButton *b)
{

}

void MyCheckButton5_Toggled(GtkCheckButton *b)
{

}

/**********************************************************************************************************************************************************************************/
void MyRadioButton1_Toggled(GtkRadioButton *b)
{

}

void MyRadioButton2_Toggled(GtkRadioButton *b)
{

}

void MySpinButton1_Changed(GtkSpinButton *s)
{

}
/**********************************************************************************************************************************************************************************/



/*
*   function changes the min count of digits for the first part of the addition
*/
void MySpinButton2_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the max count of digits for the second part of the addition
*/
void MySpinButton8_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the min count of digits for the first part of the subtraction
*/
void MySpinButton5_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the max count of digits for the second part of the subtraction
*/
void MySpinButton9_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the mix count of digits for the first part of the multiplication
*/
void MySpinButton3_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the max count of digits for the second part of the multiplication
*/
void MySpinButton4_Changed(GtkSpinButton *s)
{

}


/*
*   function changes the mix count of digits for the first part of the division
*/
void MySpinButton6_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the max count of digit for the second part of the division
*/
void MySpinButton7_Changed(GtkSpinButton *s)
{

}

/**********************************************************************************************************************/
/*
*   function changes the decimalplaces for addition
*/
void MySpinButton10_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the decimalplaces for subtraction
*/
void MySpinButton11_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the decimalplaces for multiplication
*/
void MySpinButton12_Changed(GtkSpinButton *s)
{

}

/*
*   function changes the decimalplaces for division
*/
void MySpinButton13_Changed(GtkSpinButton *s)
{

}

/**********************************************************************************************************************/

void MyFileChosserButton1_FileSet(GtkFileChooserButton *f)
{

}

void MyEntry1_Changed(GtkEntry *e)
{

}

void MyButton4_Clicked(GtkButton *b)
{

}