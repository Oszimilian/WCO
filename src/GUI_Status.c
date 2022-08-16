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
*   Function returns a NULL-Pointer to the requested thing
*/
void *WCO_GUI_Get(int i)
{
    void *ret;
    int intRes;
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
        case folder_name: ret = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(MyGUI.MyFileChosserButton1)); break;

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

/*
*   Function sets specific variabels in the programms
*   -> needs a void pointer as input
*   -> needs a verify value to the specific variable
*/
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




