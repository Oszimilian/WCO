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


/*
*   called when the creat worksheet-button is pressed
*/
void MyButton1_Clicked(GtkButton *b)
{
    printf("Button One is clicked! \n\n\n");

    //if the PDFViewerFlag is enabled the tread starts two okular pdf-viewer
    if (WCO_GUI_Status_Get_PDFViewer()) WCO_GUI_Start_PDFViewer();

    //starts creating the worksheet and if a error appears a message will be printet to the terminal
    if(!WCO_Worksheet_Create_Start()) printf("Es konnte keine neue PDF erzeugt werden! \n");

    //print success if evreything was carried out successfully
    else printf("Success \n");
}

/*
*   calle when the close PDF-Button is pressed
*/
void MyButton2_Clicked(GtkButton *b)
{
    //disables the PDFViewer Flag
    WCO_GUI_Close_PDFViewer();
}

/**********************************************************************************************************************/

/*
*   called when addition tasks are disabled or enabled
*/
void MyCheckButton1_Toggled(GtkCheckButton *b)
{
    //updates all the conditions arround the addition button
    WCO_GUI_Update_Addition();
}

/*
*   called when subtraction tasks are disabled or enabled
*/
void MyCheckButton2_Toggled(GtkCheckButton *b)
{
    //updates all the conidtions arround the subtraction button
    WCO_GUI_Update_Subtraction();
}

/*
*   called when multiplication tasks are disabled or enabled
*/
void MyCheckButton3_Toggled(GtkCheckButton *b)
{
    //updates all the conditions arround the multiplication button
    WCO_GUI_Update_Multiplication();
}

/*
*   called when division tasks are disabled or enabled
*/
void MyCheckButton4_Toggled(GtkCheckButton *b)
{
    //updates all the conditions arround the multiplication button
    WCO_GUI_Update_Division();
}

/*
*   called when the baseboard is enabled or disabled
*/
void MyCheckButton5_Toggled(GtkCheckButton *b)
{
    //sets the baseboardflag to the state of the return value of the checkbutton 
    WCO_Worksheet_Status_Config_Baseboard(WCO_GUI_Status_Baseboard_CheckButton5());
}

void MycheckButton6_Toggled(GtkCheckButton *b)
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
*   called when the left digit range for additions is changed
*/
void MySpinButton2_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the addition buttons
    WCO_GUI_Update_Addition();
}

/*
*   called when the right digit range for additions is changed
*/
void MySpinButton8_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the addition buttons
    WCO_GUI_Update_Addition();
}

/*
*   called when the left digit range for subtraction is changed
*/
void MySpinButton5_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the subtraction buttons
    WCO_GUI_Update_Subtraction();
}

/*
*   called when the right digit range for subtraction is changed
*/
void MySpinButton9_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the subtraction buttons 
    WCO_GUI_Update_Subtraction();
}

/*
*   called when the left digit range for multiplication is changed
*/
void MySpinButton3_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the multiplication buttons
    WCO_GUI_Update_Multiplication();
}

/*
*   called when the right digit range for multiplication is changed
*/
void MySpinButton4_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the multiplication buttons
    WCO_GUI_Update_Multiplication();
}


/*
*   called when the left digit range for division is changed
*/
void MySpinButton6_Changed(GtkSpinButton *s)
{
    //updates all the conidtions arround the division buttons
    void WCO_GUI_Update_Division();
}

/*
*   called when the right digit range for division is changed
*/
void MySpinButton7_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the divison buttons
    WCO_GUI_Update_Division();
}

/**********************************************************************************************************************/

/*
*   is called when the range for the decimal places of the addition task is changed
*/
void MySpinButton10_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the addition buttons
    WCO_GUI_Update_Addition();
}

/*
*   is called when the range for the decimal places of the subtraction task is changed
*/
void MySpinButton11_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the subtraction buttons
    WCO_GUI_Update_Subtraction();
}

/*
*   is called when the range for the decimal places of the multiplication task is changed
*/
void MySpinButton12_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the multiplication buttons
    WCO_GUI_Update_Multiplication();
}

/*
*   is called when the range for the decimal places of the division task is changed
*/
void MySpinButton13_Changed(GtkSpinButton *s)
{
    //updates all the conditions arround the division buttons
    void WCO_GUI_Update_Division();
}

/**********************************************************************************************************************/

/*
*   is called when the user choosed a folder directory 
*/
void MyFileChosserButton1_FileSet(GtkFileChooserButton *f)
{
    //Sets the saveFolderFlag and stores the folder. Finaly the CreatButton conditions are checked
    WCO_GUI_Update_Set_SaveFolder();
}

/*
*   called when the user changed something in the filename entry
*/
void MyEntry1_Changed(GtkEntry *e)
{
    //resets the savePDFFlag to make sure that the user has to save the file again
    WCO_GUI_Update_Reset_SavePDF();
    
    //Check the conditions to show the CreatButton
    WCO_GUI_Update_PermissionButton1();
}

/*
*   called when the user clicks on the save button
*/
void MyButton4_Clicked(GtkButton *b)
{
    //sets the savePDFFlag 
    WCO_GUI_Update_Set_SavePDF();
}