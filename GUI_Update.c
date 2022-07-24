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

void WCO_GUI_Update_Addition()
{
    char numberSpace;
    double minRange = 0;

    if (WCO_GUI_Status_Addition_DecimalPlaces() == 0)
    {
        numberSpace = 'Z';
    }else{
        numberSpace = 'R';
    }

    if (WCO_GUI_Status_AdditionCheck_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton2);
        gtk_widget_show(MyGUI.MySpinButton8);
        gtk_widget_show(MyGUI.MySpinButton10);
        gtk_label_set_text(MyGUI.MyLabel2, &numberSpace);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton2);
        gtk_widget_hide(MyGUI.MySpinButton8);
        gtk_widget_hide(MyGUI.MySpinButton10);
        gtk_label_set_text(MyGUI.MyLabel2, "");
    }

    if (WCO_GUI_Status_Addition_SpinButton(0) < WCO_GUI_Status_Addition_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton10), minRange, (double) WCO_GUI_Status_Addition_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton10), minRange, (double) WCO_GUI_Status_Addition_SpinButton(1));
    }

    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Subtraction()
{
    char numberSpace;
    double minRange = 0;

    if (WCO_GUI_Status_Subtraction_DecimalPlaces() == 0)
    {
        numberSpace = 'Z';
    }else{
        numberSpace = 'R';
    }

    if (WCO_GUI_Status_Subtraction_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton5);
        gtk_widget_show(MyGUI.MySpinButton9);
        gtk_widget_show(MyGUI.MySpinButton11);
        gtk_label_set_text(MyGUI.MyLabel3, &numberSpace);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton5);
        gtk_widget_hide(MyGUI.MySpinButton9);
        gtk_widget_hide(MyGUI.MySpinButton11);
        gtk_label_set_text(MyGUI.MyLabel3, "");
    }

    if (WCO_GUI_Status_Subtraction_SpinButton(0) < WCO_GUI_Status_Subtraction_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton11), minRange, (double) WCO_GUI_Status_Subtraction_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton11), minRange, (double) WCO_GUI_Status_Subtraction_SpinButton(1));
    }

    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Multiplication()
{
    char numberSpace;
    double minRange = 0;

    if (WCO_GUI_Status_Multiplication_DecimalPlaces() == 0)
    {
        numberSpace = 'Z';
    }else{
        numberSpace = 'R';
    }

    if (WCO_GUI_Status_Multiplication_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton3);
        gtk_widget_show(MyGUI.MySpinButton4);
        gtk_widget_show(MyGUI.MySpinButton12);
        gtk_label_set_text(MyGUI.MyLabel4, &numberSpace);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton3);
        gtk_widget_hide(MyGUI.MySpinButton4);
        gtk_widget_hide(MyGUI.MySpinButton12);
        gtk_label_set_text(MyGUI.MyLabel4, "");
    }

    if (WCO_GUI_Status_Multiplication_SpinButton(0) < WCO_GUI_Status_Multiplication_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton12), minRange, (double) WCO_GUI_Status_Multiplication_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton12), minRange, (double) WCO_GUI_Status_Multiplication_SpinButton(1));
    }

    WCO_GUI_Update_PermissionButton1();
}

void WCO_GUI_Update_Division()
{
    char numberSpace;
    double minRange = 0;

    if (WCO_GUI_Status_Division_DecimalPlaces() == 0)
    {
        numberSpace = 'Z';
    }else{
        numberSpace = 'R';
    }

    if (WCO_GUI_Status_DivisionButton_CheckButton())
    {
        gtk_widget_show(MyGUI.MySpinButton6);
        gtk_widget_show(MyGUI.MySpinButton7);
        gtk_widget_show(MyGUI.MySpinButton13);
        gtk_label_set_text(MyGUI.MyLabel5, &numberSpace);
    }else{
        gtk_widget_hide(MyGUI.MySpinButton6);
        gtk_widget_hide(MyGUI.MySpinButton7);
        gtk_widget_hide(MyGUI.MySpinButton13);
        gtk_label_set_text(MyGUI.MyLabel5, "");
    }

    if (WCO_GUI_Status_Division_SpinButton(0) < WCO_GUI_Status_Division_SpinButton(1))
    {
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton13), minRange, (double) WCO_GUI_Status_Division_SpinButton(0));
    }else{
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MyGUI.MySpinButton13), minRange, (double) WCO_GUI_Status_Division_SpinButton(1));
    }

    WCO_GUI_Update_PermissionButton1();
}



void WCO_GUI_Update_PermissionButton1()
{
    int fileName = strlen(WCO_GUI_Status_FileName());

    if(!WCO_GUI_Status_AllOperant_CheckButtons() || fileName == 0)
    {
        gtk_widget_hide(MyGUI.MyButton1);
    }else{
        gtk_widget_show(MyGUI.MyButton1);
    }
}