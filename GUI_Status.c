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

int WCO_GUI_Status_AllOperant_CheckButtons()
{
    gboolean a = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton1));
    gboolean b = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton2));
    gboolean c = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton3));
    gboolean d = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton4));

    if (a && b && c && d)
    {
        return TRUE;
    }else{
        return _FALSE;
    }
}

int WCO_GUI_Status_SpecificOperand_CheckButton(int i)
{
    int ret;

    switch (i)
    {
        case 0: ret = WCO_GUI_Status_AdditionCheck_CheckButton(); break;
        case 1: ret = WCO_GUI_Status_Subtraction_CheckButton(); break;
        case 2: ret = WCO_GUI_Status_Multiplication_CheckButton(); break;
        case 3: ret = WCO_GUI_Status_DivisionButton_CheckButton(); break;
        default: break;
    }

    return ret;
}

int WCO_GUI_Status_AdditionCheck_CheckButton()
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton1));
}

int WCO_GUI_Status_Subtraction_CheckButton()
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton2));   
}

int WCO_GUI_Status_Multiplication_CheckButton()
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton3));   
}

int WCO_GUI_Status_DivisionButton_CheckButton()
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MyGUI.MyCheckButton4));   
}

int WCO_GUI_Status_Addition_SpinButton(int i)
{
    gdouble ret;

    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton2));
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton8));
        default: break;
    }

    return (int)ret;
}

int WCO_GUI_Status_Subtraction_SpinButton(int i)
{
    gdouble ret;

    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton5));
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton9));
        default: break;
    }

    return (int)ret;
}

int WCO_GUI_Status_Multiplication_SpinButton(int i)
{
    gdouble ret;

    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton3));
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton4));
        default: break;
    }

    return (int)ret;
}

int WCO_GUI_Status_Division_SpinButton(int i)
{
    gdouble ret;

    switch (i)
    {
        case 0: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton6));
        case 1: ret = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton7));
        default: break;
    }

    return (int)ret;
}

int WCO_GUI_Status_SpecificOperand_SpinButton(int operand, int i)
{
    int ret;

    switch (operand)
    {
        case 0: ret = WCO_GUI_Status_Addition_SpinButton(i); break;
        case 1: ret = WCO_GUI_Status_Subtraction_SpinButton(i); break;
        case 2: ret = WCO_GUI_Status_Multiplication_SpinButton(i); break;
        case 3: ret = WCO_GUI_Status_Division_SpinButton(i); break;
        default: break;
    }

    return ret;
}

int WCO_GUI_Status_Addition_DecimalPlaces()
{
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton10));
}

int WCO_GUI_Status_Subtraction_DecimalPlaces()
{
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton11));
}

int WCO_GUI_Status_Multiplication_DecimalPlaces()
{
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton12));
}

int WCO_GUI_Status_Division_DecimalPlaces()
{   
    return (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(MyGUI.MySpinButton13));
}

int WCO_GUI_Status_SpecificOperand_DecimalPlaces(int i)
{
    int ret;

    switch (i)
    {
        case 0: ret = WCO_GUI_Status_Addition_DecimalPlaces(); break;
        case 1: ret = WCO_GUI_Status_Subtraction_DecimalPlaces(); break;
        case 2: ret = WCO_GUI_Status_Multiplication_DecimalPlaces(); break;
        case 3: ret = WCO_GUI_Status_Division_DecimalPlaces(); break;
    }

    return ret;
}