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
#include "Worksheet_Creat_Task.h"

void WCO_GUI_Update(int i)
{
    WCO_GUI_Update_Label(i);

    WCO_GUI_Update_Visibility(i);

    WCO_GUI_Update_DigitRange(i);

    WCO_GUI_Update_CreateButton();
}

void WCO_GUI_Update_Label(int i)
{
    int spinValue = WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + i));
    int checkButton = WCO_BUTTON(WCO_GUI_Get(task_addition + i));
    char numSpace[5] = {'Z', '\0', 'R', '\0', ' '};


    if((spinValue == 0) && checkButton) WCO_GUI_Set(&numSpace[0], (label_addition + i));
    if((spinValue >= 1) && checkButton) WCO_GUI_Set(&numSpace[2], (label_addition + i));
    if(!checkButton) WCO_GUI_Set(&numSpace[4], (label_addition + i));
    
}

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

void WCO_GUI_Update_DigitRange(int i)
{
    int leftRange = WCO_BUTTON(WCO_GUI_Get(task_addition_digit_1 + i));
    int rightRange = WCO_BUTTON(WCO_GUI_Get(task_addition_digit_2 + i));
    int jmpVal = (i == 0) ? 0 : (i == 1) ? 4 : (i == 2) ? 8 : (i == 3) ? 12 : 0;
    int minRange = 0;
    int maxRange = (leftRange < rightRange) ? leftRange : rightRange;
    gtk_spin_button_set_range(GTK_SPIN_BUTTON(WCO_WDG(WCO_GUI_Get(task_addition_dezcount_ref + jmpVal))), (double)minRange, (double)maxRange);
}

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
        printf("Fix 1 \n");
    }
    if (WCO_WDG(WCO_GUI_Get(gtk_stack)) == WCO_WDG(WCO_GUI_Get(gtk_fixed_2)))
    {
        for (int i = 0; i <= 3; i++)
        {
            checkSum += (WCO_BUTTON(WCO_GUI_Get(frac_addition + i))) ? 1 : 0;
        }
        printf("Fix 2 \n");
    }
    
    if (checkSum == 0 || fileNameLeangh == 0 || !WCO_BUTTON(WCO_GUI_Get(savePDFButton)) || !WCO_BUTTON(WCO_GUI_Get(saveFolderButton)))
    {
        gtk_widget_hide(WCO_WDG(WCO_GUI_Get(creatButton_ref)));
    }else{
        gtk_widget_show(WCO_WDG(WCO_GUI_Get(creatButton_ref)));
    }
}

void WCO_GUI_Update_FileName()
{
    int fileNameLeangh = strlen(WCO_ENTRY(WCO_GUI_Get(entry_1)));

    if (fileNameLeangh >= 1)
    {
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Tasks);
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Solutions);

        int i = _TRUE;
        WCO_GUI_Set(&i, savePDF);
    }
}

/*
*   this function updates all the conditions arround the visibility of buttons and labels depending on the addition enable button
*/
void WCO_GUI_Update_Addition()
{
    //Init a pointer
    char *ptr;

    //Set the local var which is responsible for the min range of the spinButton
    double minRange = 0;

    if (!WCO_GUI_Status_Get_AdditionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Addition_CheckButton())
    {
        //if the value of the spin-button is zero and the addition checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[0];
    }
    else if(WCO_GUI_Status_Get_AdditionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Addition_CheckButton())
    {
        //if the value of the spin-button is greather than zero and the addition checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[1];
    }
    else if (!WCO_GUI_Status_Get_Addition_CheckButton())
    {
        //if the addition checkbutton is False the lokal pointer gets the address to a pointer which points to a empty string
        ptr = MyGUI.label[2];
    }

    //if the addition check button is enabled the specific buttons are displayed otherwise they were hide by gtk
    if (WCO_GUI_Status_Get_Addition_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton2);
        gtk_widget_show(MyGUI.MySpinButton8);
        gtk_widget_show(MyGUI.MySpinButton10);
        gtk_label_set_text(MyGUI.MyLabel2, ptr);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton2);
        gtk_widget_hide(MyGUI.MySpinButton8);
        gtk_widget_hide(MyGUI.MySpinButton10);
        gtk_label_set_text(MyGUI.MyLabel2, ptr);
    }

    //this is responsible to make sure that the highest count of decimal places is never higher than the lowest digit count
    if (WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(0) < WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton10), minRange, (double) WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton10), minRange, (double) WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(1));
    }

    //Update the permissions under the "Creatbutton" is allowed to be displayed
    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Subtraction()
{
    //Init a pointer
    char *ptr;

    //Set the local var which is responsible for the min range of the spinButton
    double minRange = 0;

    if (!WCO_GUI_Status_Get_SubtractionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Subtraction_CheckButton())
    {
        //if the value of the spin-button is zero and the subtraction checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[0];
    }
    else if (WCO_GUI_Status_Get_SubtractionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Subtraction_CheckButton())
    {
        //if the value of the spin-button is greather than zero and the subtraction checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[1];
    }
    else if (!WCO_GUI_Status_Get_Subtraction_CheckButton())
    {
        //if the subtraction checkbutton is False the lokal pointer gets the address to a pointer which points to a empty string
        ptr = MyGUI.label[2];
    }

    //if the subtraction check button is enabled the specific buttons are displayed otherwise they were hide by gtk
    if (WCO_GUI_Status_Get_Subtraction_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton5);
        gtk_widget_show(MyGUI.MySpinButton9);
        gtk_widget_show(MyGUI.MySpinButton11);
        gtk_label_set_text(MyGUI.MyLabel3, ptr);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton5);
        gtk_widget_hide(MyGUI.MySpinButton9);
        gtk_widget_hide(MyGUI.MySpinButton11);
        gtk_label_set_text(MyGUI.MyLabel3, ptr);
    }

    //this is responsible to make sure that the highest count of decimal places is never higher than the lowest digit count
    if (WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(0) < WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton11), minRange, (double) WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton11), minRange, (double) WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(1));
        
    }

    //Update the permissions under the "Creatbutton" is allowed to be displayed
    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Multiplication()
{
    //Init a pointer
    char *ptr;

    //Set the local var which is responsible for the min range of the spinButton
    double minRange = 0;

    if (!WCO_GUI_Status_Get_MultiplicationDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Multiplication_CheckButton())
    {
        //if the value of the spin-button is zero and the multiplication checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[0];
    }
    else if(WCO_GUI_Status_Get_MultiplicationDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Multiplication_CheckButton())
    {
        //if the value of the spin-button is greather than zero and the multiplication checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[1];
    }
    else if (!WCO_GUI_Status_Get_Multiplication_CheckButton())
    {
        //if the multiplication checkbutton is False the lokal pointer gets the address to a pointer which points to a empty string
        ptr = MyGUI.label[2];
    }

    //if the multiplication check button is enabled the specific buttons are displayed otherwise they were hide by gtk
    if (WCO_GUI_Status_Get_Multiplication_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton3);
        gtk_widget_show(MyGUI.MySpinButton4);
        gtk_widget_show(MyGUI.MySpinButton12);
        gtk_label_set_text(MyGUI.MyLabel4, ptr);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton3);
        gtk_widget_hide(MyGUI.MySpinButton4);
        gtk_widget_hide(MyGUI.MySpinButton12);
        gtk_label_set_text(MyGUI.MyLabel4, ptr);
    }

    //this is responsible to make sure that the highest count of decimal places is never higher than the lowest digit count
    if (WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(0) < WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton12), minRange, (double) WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton12), minRange, (double) WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(1));
    }

    //Update the permissions under the "Creatbutton" is allowed to be displayed
    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Division()
{
    //Init a pointer
    char *ptr;

    //Set the local var which is responsible for the min range of the spinButton
    double minRange = 0;

    if (!WCO_GUI_Status_Get_DevisionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Division_CheckButton())
    {
        //if the value of the spin-button is zero and the division checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[0];
    }
    else if(WCO_GUI_Status_Get_DevisionDecimalPlaces_SpinButton() && WCO_GUI_Status_Get_Division_CheckButton())
    {
        //if the value of the spin-button is greather than zero and the division checkbutton is True, the lokal pointer gets the adress of anthour pointer
        ptr = MyGUI.label[1];
    }
    else if(!WCO_GUI_Status_Get_Division_CheckButton())
    {
        //if the division checkbutton is False the lokal pointer gets the address to a pointer which points to a empty string
        ptr = MyGUI.label[2];
    }

    //if the division check button is enabled the specific buttons are displayed otherwise they were hide by gtk
    if (WCO_GUI_Status_Get_Division_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton6);
        gtk_widget_show(MyGUI.MySpinButton7);
        gtk_widget_show(MyGUI.MySpinButton13);
        gtk_label_set_text(MyGUI.MyLabel5, ptr);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton6);
        gtk_widget_hide(MyGUI.MySpinButton7);
        gtk_widget_hide(MyGUI.MySpinButton13);
        gtk_label_set_text(MyGUI.MyLabel5, ptr);
    }

    //this is responsible to make sure that the highest count of decimal places is never higher than the lowest digit count
    if (WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(0) < WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton13), minRange, (double) WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton13), minRange, (double) WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(1));
    }

    //Update the permissions under the "Creatbutton" is allowed to be displayed
    WCO_GUI_Update_PermissionButton1();
}


/*
*   This function is used to check the conditions under the "Creatbutton" is allowed to be displayed
*   To avoid that the programm trys to save the generated file without a filename or to generate a worksheet where all operands are disabled this is necesserly
*/
void WCO_GUI_Update_PermissionButton1()
{
    //store the leangh of the filename in a local var
    int fileNameLeangh = strlen(WCO_GUI_Status_FileName());

    //The conditions are:
    //-At least one operand has to be enabled
    //-the filename has to be more places than one
    //-The user pressed after every change of the filename in the filename entry field the save button
    //-The user searched after a directory to store the worksheets
    //-> As a result of the evaluation the "CreatButton" is displayed or hide
    if(!WCO_GUI_Status_Get_AllOperand_CheckButtons() || fileNameLeangh == 0 || !WCO_GUI_Status_SaveButton4() || !WCO_GUI_Status_FolderButton())
    {
        gtk_widget_hide(MyGUI.MyButton1);
    }else{
        gtk_widget_show(MyGUI.MyButton1);
    }
}

/*
*   This function is called when the user pressed the save button
*/
void WCO_GUI_Update_Set_SavePDF()
{

    int fileNameLeangh = strlen(WCO_ENTRY(WCO_GUI_Get(entry_1)));


    if (fileNameLeangh >= 1)
    {
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Tasks);
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Solutions);

        int i = _TRUE;
        WCO_GUI_Set(&i, savePDF);
    }
}



/*
*   This function is used to reset the global saveEnabledFlag
*   This happens every time when the user changes the contant of the entry field
*/
void WCO_GUI_Update_Reset_SavePDF()
{
    MyGUI.savePDF = _FALSE;
}

/*
*   function is called when the user already searched after a directory
*/
void WCO_GUI_Update_Set_SaveFolder()
{
    //store the leangh of the foldername in a local var
    //if the fileleangh is zero that whould mean that the pdf is saved in the programmdirectory and this should not allowed
    int folderLeangh = strlen(WCO_GUI_Status_FolderName());

    //if the foldername is longer than one
    if (folderLeangh >= 1)
    {
        //Set the foldername 
        WCO_PDF_SetFoldername(WCO_GUI_Status_FolderName());

        //Set a global flag to true to visualice that a folder is already choosed
        MyGUI.saveFolder = _TRUE;
    }

    //Called to check the conditions for the "CreatButton"
    WCO_GUI_Update_PermissionButton1();
}

/*
*   function is used to reset the saveFolder Flag
*/
void WCO_GUI_Update_Reset_SaveFolder()
{
    MyGUI.saveFolder = _FALSE;
}