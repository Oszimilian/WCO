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
    //store the leangh of the filename in a local var
    int fileNameLeangh = strlen(WCO_GUI_Status_FileName());

    //if the filename is greater than ten
    if (fileNameLeangh >= 1)
    {
        //The filenames for the solution and the task sheets are set
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Tasks);
        WCO_PDF_SetFilename(WCO_GUI_Status_FileName(), _Solutions);

        //a global saveButtonFlag is set to true which is necesserly for the function above to show the "CreatButton"
        MyGUI.savePDF = _TRUE;
    }

    //Called to check the conditions for the "CreatButton"
    WCO_GUI_Update_PermissionButton1();
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