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
#include "GUI_Status.h"
#include "GUI_Update.h"
#include "GUI.h"
#include "PDF.h"
#include "PNG.h"
#include "Worksheet_Baseboard.h"
#include "Worksheet_Creat_Fraction.h"
#include "Worksheet_Creat_Task.h"

/*
*   Function updates all the GUI settings if a specific button is pressed
*/
void WCO_GUI_Update(int i)
{
    WCO_GUI_Update_Label(i);

    WCO_GUI_Update_Visibility(i);

    WCO_GUI_Update_DigitRange(i);

    WCO_GUI_Update_CreateButton();
}

/*
*   Function updates the GUI-Label which represents the num-Space of the functions 
*/
void WCO_GUI_Update_Label(int i)
{
    int spinValue = WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + i));
    int checkButton = WCO_BUTTON(WCO_GUI_Get(task_addition + i));
    char numSpace[5] = {'Z', '\0', 'R', '\0', ' '};


    if((spinValue == 0) && checkButton) WCO_GUI_Set(&numSpace[0], (label_addition + i));
    if((spinValue >= 1) && checkButton) WCO_GUI_Set(&numSpace[2], (label_addition + i));
    if(!checkButton) WCO_GUI_Set(&numSpace[4], (label_addition + i));
    
}

/*
*   Function updates the GUI-Widget-Visibility if the Opperand-Check-Buttons are pressed
*/
void WCO_GUI_Update_Visibility(int i)
{
    int jmpVal = (i == 0) ? 0 : (i == 1) ? 4 : (i == 2) ? 8 : (i == 3) ? 12 : 0;
    if(WCO_BUTTON(WCO_GUI_Get(task_addition + i)))
    {
        for (int k = 0; k <= 2; k++)
        {
            gtk_widget_show(WCO_WDG(WCO_GUI_Get(task_addition_digit_1_ref + jmpVal + k)));
        } 
    }else{
        for (int k = 0; k <= 2; k++)
        {
            gtk_widget_hide(WCO_WDG(WCO_GUI_Get(task_addition_digit_1_ref + jmpVal + k)));
        } 
    }
}

/*
*   This function updates the visibility of the settings for the baseboard
*/
void WCO_GUI_Update_Baseboard()
{
    if(WCO_BUTTON(WCO_GUI_Get(base_baseboard)))
    {
        for (int i = 0; i <= 2; i++)
        {
            gtk_widget_show(WCO_WDG(WCO_GUI_Get(base_date_ref + i)));
        }
    }else{
        for (int i = 0; i <= 2; i++)
        {
            gtk_widget_hide(WCO_WDG(WCO_GUI_Get(base_date_ref + i)));
        }
    }
}

/*
*   This function updates the range of the digitRange of the opperands
*/
void WCO_GUI_Update_DigitRange(int i)
{
    int leftRange = WCO_BUTTON(WCO_GUI_Get(task_addition_digit_1 + i));
    int rightRange = WCO_BUTTON(WCO_GUI_Get(task_addition_digit_2 + i));
    int jmpVal = (i == 0) ? 0 : (i == 1) ? 4 : (i == 2) ? 8 : (i == 3) ? 12 : 0;
    int minRange = 0;
    int maxRange = (leftRange < rightRange) ? leftRange : rightRange;
    gtk_spin_button_set_range(GTK_SPIN_BUTTON(WCO_WDG(WCO_GUI_Get(task_addition_dezcount_ref + jmpVal))), (double)minRange, (double)maxRange);
}

/*
*   Checks the conditions under the creatButton is able to displayed for a better userbility
*/
void WCO_GUI_Update_CreateButton()
{
    int checkSum = 0;
    int fileNameLeangh = strlen(WCO_ENTRY(WCO_GUI_Get(entry_1)));
    if (WCO_WDG(WCO_GUI_Get(gtk_stack)) == WCO_WDG(WCO_GUI_Get(gtk_fixed_1)))
    {
        for (int i = 0; i <= 3; i++)
        {
            checkSum += (WCO_BUTTON(WCO_GUI_Get(task_addition + i))) ? 1 : 0;
        }
    }
    if (WCO_WDG(WCO_GUI_Get(gtk_stack)) == WCO_WDG(WCO_GUI_Get(gtk_fixed_2)))
    {
        for (int i = 0; i <= 3; i++)
        {
            checkSum += (WCO_BUTTON(WCO_GUI_Get(frac_addition + i))) ? 1 : 0;
        }
    }
    
    if (checkSum == 0 || fileNameLeangh == 0 || !WCO_BUTTON(WCO_GUI_Get(savePDFButton)) || !WCO_BUTTON(WCO_GUI_Get(saveFolderButton)))
    {
        gtk_widget_hide(WCO_WDG(WCO_GUI_Get(creatButton_ref)));
    }else{
        gtk_widget_show(WCO_WDG(WCO_GUI_Get(creatButton_ref)));
    }
}

/*
*   sets the filename and the folder name
*/
void WCO_GUI_Update_FileName()
{
    int fileNameLeangh = strlen(WCO_ENTRY(WCO_GUI_Get(entry_1)));
    WCO_PDF_SetFoldername(WCO_ENTRY(WCO_GUI_Get(folder_name)));


    if (fileNameLeangh >= 1)
    {
    WCO_PDF_SetFilename(WCO_ENTRY(WCO_GUI_Get(entry_1)), _Tasks);
    WCO_PDF_SetFilename(WCO_ENTRY(WCO_GUI_Get(entry_1)), _Solutions);
    }
}
