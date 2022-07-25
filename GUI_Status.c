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
*   function is used to show when all opperands are disabled
*   this is a condition for hiding the CreatButton because a worksheet with no opperands can not exist
*/
int WCO_GUI_Status_Get_AllOperand_CheckButtons()
{
    // store the states of the opperand in local vars
    gboolean a = WCO_GUI_Status_Get_Addition_CheckButton();
    gboolean b = WCO_GUI_Status_Get_Division_CheckButton();
    gboolean c = WCO_GUI_Status_Get_Multiplication_CheckButton();
    gboolean d = WCO_GUI_Status_Get_Division_CheckButton();

    //if all opperand-buttons are disabled the return value is false else the return value is true
    if (!a && !b && !c && !d)
    {
        return _FALSE;
    }else{
        return _TRUE;
    }
}

/**********************************************************************************************************************/

/*
*   function is used to search for the state of a specific opperand button
*/
int WCO_GUI_Status_Get_SpecificOperand_CheckButton(int i)
{
    //initialse a return value
    int ret;

    //serach after the specific operand and store the return value of the called functions in the local var
    switch (i)
    {
        case 0: ret = WCO_GUI_Status_Get_Addition_CheckButton(); break;
        case 1: ret = WCO_GUI_Status_Get_Subtraction_CheckButton(); break;
        case 2: ret = WCO_GUI_Status_Get_Multiplication_CheckButton(); break;
        case 3: ret = WCO_GUI_Status_Get_Division_CheckButton(); break;
        default: break;
    }

    //return the local var
    return ret;
}

/*
*   function returns the state of the addition check-button 
*/
int WCO_GUI_Status_Get_Addition_CheckButton()
{
    //the function returns the state of the button and requires a casted form of the check-button
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton1));
}

/*
*   function returns the state of the subtraction check-button 
*/
int WCO_GUI_Status_Get_Subtraction_CheckButton()
{
    //the function returns the state of the button and requires a casted form of the check-button
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton2));   
}

/*
*   function returns the state of the multiplication check-button 
*/
int WCO_GUI_Status_Get_Multiplication_CheckButton()
{
    //the function returns the state of the button and requires a casted form of the check-button
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton3));   
}

/*
*   function returns the state of the division check-button 
*/
int WCO_GUI_Status_Get_Division_CheckButton()
{
    //the function returns the state of the button and requires a casted form of the check-button
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton4));   
}

/**********************************************************************************************************************/

/*
*   function is used to search after a specific value of operand-digit-spin-button 
*   you can specify after the operand and after the left and right spin button (int i)
*/
int WCO_GUI_Status_Get_SpecificOperandDigitRange_spinButton(int operand, int i)
{
    //initialice a lokal return var
    int ret;

    //search after the operand and store the return value of the called function. The called function gets a input to distinguish between left and right
    switch (operand)
    {
        case 0: ret = WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(i); break;
        case 1: ret = WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(i); break;
        case 2: ret = WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(i); break;
        case 3: ret = WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(i); break;
        default: break;
    }

    //return the local var
    return ret;
}

/*
*   function returns the value of the right or left digit range addition spin button 
*/
int WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(int i)
{
    //init a local return val
    gdouble ret;

    //serach after the right or left spin button end store the returned value 
    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton2)); break;
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton8)); break;
        default: break;
    }

    //cast the return value from gdouble to int and return it
    return (int)ret;
}

/*
*   function returns the value of the right or left digit range subtraction spin button 
*/
int WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(int i)
{
    //init a local return val
    gdouble ret;

    //serach after the right or left spin button end store the returned value 
    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton5)); break;
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton9)); break;
        default: break;
    }

    //cast the return value from gdouble to int and return it
    return (int)ret;
}

/*
*   function returns the value of the right or left digit range Multiplication spin button 
*/
int WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(int i)
{
    //init a local return val
    gdouble ret;

    //serach after the right or left spin button end store the returned value
    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton3)); break;
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton4)); break;
        default: break;
    }

    //cast the return value from gdouble to int and return it
    return (int)ret;
}

/*
*   function returns the value of the right or left digit range Division spin button 
*/
int WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(int i)
{
    //init a local return val
    gdouble ret;

    //serach after the right or left spin button end store the returned value
    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton6)); break;
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton7)); break;
        default: break;
    }

    //cast the return value from gdouble to int and return it
    return (int)ret;
}

/**********************************************************************************************************************/

/*
*   funcition is used to search after a specific value of decimal-places-spin-button
*/
int WCO_GUI_Status_Get_SpecificOperandDecimalPlaces_SpinButton(int operand)
{
    //init a local return var
    int ret;

    //search after the right operand and store the return value of the fuction in the local return var
    switch (operand)
    {
        case 0: ret = WCO_GUI_Status_Get_AdditionDecimalPlaces_SpinButton(); break;
        case 1: ret = WCO_GUI_Status_Get_SubtractionDecimalPlaces_SpinButton(); break;
        case 2: ret = WCO_GUI_Status_Get_MultiplicationDecimalPlaces_SpinButton(); break;
        case 3: ret = WCO_GUI_Status_Get_DevisionDecimalPlaces_SpinButton(); break;
    }

    //return the local var
    return ret;
}

/*
*   returns the value of the addition-decimal-places spinbutton
*/
int WCO_GUI_Status_Get_AdditionDecimalPlaces_SpinButton()
{
    //calls the function and cast the return value from gdouble to int 
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton10));
}

/*
*   returns the value of the division-decimal-places spinbutton
*/
int WCO_GUI_Status_Get_SubtractionDecimalPlaces_SpinButton()
{
    //calls the function and cast the return value from gdouble to int 
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton11));
}

/*
*   returns the value of the multiplication-decimal-places spinbutton
*/
int WCO_GUI_Status_Get_MultiplicationDecimalPlaces_SpinButton()
{
    //calls the function and cast the return value from gdouble to int 
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton12));
}

/*
*   returns the value of the division-decimal-places spinbutton
*/
int WCO_GUI_Status_Get_DevisionDecimalPlaces_SpinButton()
{   
    //calls the function and cast the return value from gdouble to int 
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton13));
}

/**********************************************************************************************************************/
/*
*   function return a pointer to a string where the filename is stored
*/
char *WCO_GUI_Status_FileName()
{
    //generating space for a 100 chars
    char *tmp = malloc(100 * sizeof(char));

    //stores the entry text from the gtk widget in the tmp
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(MyGUI.MyEntry1)));

    //return the pointer 
    return tmp;
}

/*
*   function returns the savePDFFlag
*/
int WCO_GUI_Status_SaveButton4()
{
    return MyGUI.savePDF;
}

/*
*   function returns a pointer to a string where the foldername is stored
*/
char *WCO_GUI_Status_FolderName()
{
    //generates space for a array of 100 chars
    char *tmp = malloc(100 * sizeof(char));

    //stores the string returned by the gtk function which prints the foldertree into tmp 
    sprintf(tmp, "%s", gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(MyGUI.MyFileChosserButton1)));

    //returns the pointer
    return tmp;
}

/*
*   returns the saveFolder flag which point out if the user added a folder
*/
int WCO_GUI_Status_FolderButton()
{
    return MyGUI.saveFolder;
}

/*
*   returns if the checkbutton for the Baseboard is enabled or disabled
*/
int WCO_GUI_Status_Baseboard_CheckButton5()
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton5));   
}

