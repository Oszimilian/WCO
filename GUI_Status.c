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
const char *WCO_GUI_Status_FileName()
{
    return gtk_entry_get_text(GTK_ENTRY(MyGUI.MyEntry1));
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
    return gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(MyGUI.MyFileChosserButton1));
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

/*
*   returns if the PNG is enabled to be displayed or not
*/
int WCO_GUI_Status_Get_ShowPNG()
{
    return MyGUI.showPNG;
}

/*
*   Set the ShowPNG Flag 
*/
void WCO_GUI_Status_Set_ShowPNG()
{
    MyGUI.showPNG = _TRUE;
}

/*
*   Reset the ShowPNG Flag
*/
void WCO_GUI_Status_Reset_ShowPNG()
{
    MyGUI.showPNG = _FALSE;
}



void *WCO_GUI_Get(int i)
{
    void *ret;
    int intRes;
    char charRes;
    GtkWidget *wdgRes;
    GtkLabel *labRes;

    switch(i)
    {   
        //SpinButtons for the fraction digits
        case frac_zahler_1: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton14)); ret = &intRes; break;
        case frac_nenner_1: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton15)); ret = &intRes; break;
        case frac_zahler_2: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton16)); ret = &intRes; break;
        case frac_nenner_2: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton17)); ret = &intRes; break;

        //CheckButtons for the fractionmode
        case frac_addition:       intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton7));  ret = &intRes; break;
        case frac_subtraction:    intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton8));  ret = &intRes; break;
        case frac_multiplication: intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton9));  ret = &intRes; break;
        case frac_division:       intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton10)); ret = &intRes; break;

        //CheckButtons for the baseboard
        case base_baseboard:    intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton5)); ret = &intRes; break;
        case base_date:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton6)); ret = &intRes; break;
        case base_name:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton11)); ret = &intRes; break;
        case base_text:         ret = gtk_entry_get_text(GTK_ENTRY(MyGUI.MyEntry2)); break;

        //CheckButtons for the taskmode
        case task_addition:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton1)); ret = &intRes; break;
        case task_subtraction:      intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton2)); ret = &intRes; break;
        case task_multiplication:   intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton3)); ret = &intRes; break; 
        case task_division:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton4)); ret = &intRes; break;

        //SpinButtons for the decimal places in the taskmode
        case task_addition_dezcount:           intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton10)); ret = &intRes; break;
        case task_subtraction_dezcount:        intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton11)); ret = &intRes; break;
        case task_multiplication_dezcount:     intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton12)); ret = &intRes; break;
        case task_division_dezcount:           intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton13)); ret = &intRes; break;

        //SpinButtons for the left digits in the taskmode
        case task_addition_digit_1:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton2)); ret = &intRes; break;
        case task_subtraction_digit_1:      intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton5)); ret = &intRes; break;
        case task_multiplication_digit_1:   intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton3)); ret = &intRes; break;
        case task_division_digit_1:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton6)); ret = &intRes; break;

        //SpinButton for the right digits in the taskmode
        case task_addition_digit_2:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton8)); ret = &intRes; break;
        case task_subtraction_digit_2:      intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton9)); ret = &intRes; break;
        case task_multiplication_digit_2:   intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton4)); ret = &intRes; break;
        case task_division_digit_2:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton7)); ret = &intRes; break;

        //EntryField for typing the filename and saving it 
        case entry_1: ret = gtk_entry_get_text(GTK_ENTRY(MyGUI.MyEntry1)); break;
        case savePDFButton: ret = &MyGUI.savePDF; break; 
        case saveFolderButton: ret = &MyGUI.saveFolder; break;
        case creatButton_ref: ret = MyGUI.MyButton1; break;

        //Referenze to addition widgets
        case task_addition_digit_1_ref:    wdgRes = MyGUI.MySpinButton2; ret = wdgRes; break;
        case task_addition_digit_2_ref:    wdgRes = MyGUI.MySpinButton8; ret = wdgRes; break;
        case task_addition_dezcount_ref:   wdgRes = MyGUI.MySpinButton10; ret = wdgRes; break;
        case task_addition_label_ref:      labRes = MyGUI.MyLabel2; ret = labRes;  break;

        //Reference to subtraction widgets
        case task_subtraction_digit_1_ref:  wdgRes = MyGUI.MySpinButton5; ret = wdgRes; break;
        case task_subtraction_digit_2_ref:  wdgRes = MyGUI.MySpinButton9; ret = wdgRes; break;
        case task_subtraction_dezcount_ref: wdgRes = MyGUI.MySpinButton11; ret = wdgRes; break;
        case task_subtraction_label_ref:    labRes = MyGUI.MyLabel3; ret = labRes; break;

        //Reference to multiplication widgets
        case task_multiplication_digit_1_ref:   wdgRes = MyGUI.MySpinButton3; ret = wdgRes; break;
        case task_multiplication_digit_2_ref:   wdgRes = MyGUI.MySpinButton4; ret = wdgRes; break;
        case task_multiplication_dezcount_ref:  wdgRes = MyGUI.MySpinButton12; ret = wdgRes; break;
        case task_multiplication_label_ref:     labRes = MyGUI.MyLabel4; ret = labRes; break;

        //Reference to division widgets
        case task_division_digit_1_ref:     wdgRes = MyGUI.MySpinButton6; ret = wdgRes; break;
        case task_division_digit_2_ref:     wdgRes = MyGUI.MySpinButton7; ret = wdgRes; break;
        case task_division_dezcount_ref:    wdgRes = MyGUI.MySpinButton13; ret = wdgRes; break;
        case task_division_label_ref:       labRes = MyGUI.MyLabel5; ret = labRes; break;

        //Reference to the displayed GTK-Fixed
        case gtk_stack: wdgRes = gtk_stack_get_visible_child(GTK_STACK(MyGUI.MyStack2)); ret = wdgRes; break;
        case gtk_fixed_1: wdgRes = MyGUI.MySettingsFixed[0]; ret = wdgRes; break;
        case gtk_fixed_2: wdgRes = MyGUI.MySettingsFixed[1]; ret = wdgRes; break;

        //Reference to the baseboard settings
        case base_baseboard_ref:    wdgRes = MyGUI.MyCheckButton5; ret = wdgRes; break;
        case base_date_ref:         wdgRes = MyGUI.MyCheckButton6; ret = wdgRes; break;
        case base_name_ref:         wdgRes = MyGUI.MyCheckButton11; ret = wdgRes; break;
        case base_text_ref:         wdgRes = MyGUI.MyEntry2; ret = wdgRes; break;

        default: break;
    }
    return ret;
}

void WCO_GUI_Set(void *input, int verify)
{
    switch (verify)
    {
        case filename: sprintf(MyPDF.fileName, "%s", WCO_ENTRY(input)); break;
        case foldername: sprintf(MyPDF.folderName, "%s", WCO_ENTRY(input)); break;
        case savePDF: MyGUI.savePDF = WCO_BUTTON(input); break;
        case saveFolder: MyGUI.saveFolder = WCO_BUTTON(input); break;

        case label_addition:        gtk_label_set_text(MyGUI.MyLabel2, WCO_CHAR(input)); break;
        case label_subtraction:     gtk_label_set_text(MyGUI.MyLabel3, WCO_CHAR(input)); break;
        case label_multiplication:  gtk_label_set_text(MyGUI.MyLabel4, WCO_CHAR(input)); break;
        case label_division:        gtk_label_set_text(MyGUI.MyLabel5, WCO_CHAR(input)); break;
    }
}




