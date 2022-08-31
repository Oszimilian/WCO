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
#include "main.h"

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
        case frac_zahler_1: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton14)); ret = &intRes; break;
        case frac_nenner_1: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton15)); ret = &intRes; break;
        case frac_zahler_2: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton16)); ret = &intRes; break;
        case frac_nenner_2: intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton17)); ret = &intRes; break;

        //CheckButtons for the fractionmode
        case frac_addition:       intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton7));  ret = &intRes; break;
        case frac_subtraction:    intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton8));  ret = &intRes; break;
        case frac_multiplication: intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton9));  ret = &intRes; break;
        case frac_division:       intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton10)); ret = &intRes; break;

        //CheckButtons for the baseboard
        case base_baseboard:    intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton5)); ret = &intRes; break;
        case base_date:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton6)); ret = &intRes; break;
        case base_name:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton11)); ret = &intRes; break;
        case base_text:         ret = (char*)gtk_entry_get_text(GTK_ENTRY(WCO_GUI_Ref()->MyEntry2)); break;

        //CheckButtons for the taskmode
        case task_addition:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton1)); ret = &intRes; break;
        case task_subtraction:      intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton2)); ret = &intRes; break;
        case task_multiplication:   intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton3)); ret = &intRes; break; 
        case task_division:         intRes = (int)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WCO_GUI_Ref()->MyCheckButton4)); ret = &intRes; break;

        //SpinButtons for the decimal places in the taskmode
        case task_addition_dezcount:           intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton10)); ret = &intRes; break;
        case task_subtraction_dezcount:        intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton11)); ret = &intRes; break;
        case task_multiplication_dezcount:     intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton12)); ret = &intRes; break;
        case task_division_dezcount:           intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton13)); ret = &intRes; break;

        //SpinButtons for the left digits in the taskmode
        case task_addition_digit_1:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton2)); ret = &intRes; break;
        case task_subtraction_digit_1:      intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton5)); ret = &intRes; break;
        case task_multiplication_digit_1:   intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton3)); ret = &intRes; break;
        case task_division_digit_1:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton6)); ret = &intRes; break;

        //SpinButton for the right digits in the taskmode
        case task_addition_digit_2:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton8)); ret = &intRes; break;
        case task_subtraction_digit_2:      intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton9)); ret = &intRes; break;
        case task_multiplication_digit_2:   intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton4)); ret = &intRes; break;
        case task_division_digit_2:         intRes = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(WCO_GUI_Ref()->MySpinButton7)); ret = &intRes; break;

        //EntryField for typing the filename and saving it 
        case entry_1: ret = (char*)gtk_entry_get_text(GTK_ENTRY(WCO_GUI_Ref()->MyEntry1)); break;
        case savePDFButton: ret = &WCO_GUI_Ref()->savePDF; break; 
        case saveFolderButton: ret = &WCO_GUI_Ref()->saveFolder; break;
        case creatButton_ref: ret = WCO_GUI_Ref()->MyButton1; break;
        case folder_name: ret = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(WCO_GUI_Ref()->MyFileChosserButton1)); break;

        //Referenze to addition widgets
        case task_addition_digit_1_ref:    wdgRes = WCO_GUI_Ref()->MySpinButton2; ret = wdgRes; break;
        case task_addition_digit_2_ref:    wdgRes = WCO_GUI_Ref()->MySpinButton8; ret = wdgRes; break;
        case task_addition_dezcount_ref:   wdgRes = WCO_GUI_Ref()->MySpinButton10; ret = wdgRes; break;
        case task_addition_label_ref:      labRes = WCO_GUI_Ref()->MyLabel2; ret = labRes;  break;

        //Reference to subtraction widgets
        case task_subtraction_digit_1_ref:  wdgRes = WCO_GUI_Ref()->MySpinButton5; ret = wdgRes; break;
        case task_subtraction_digit_2_ref:  wdgRes = WCO_GUI_Ref()->MySpinButton9; ret = wdgRes; break;
        case task_subtraction_dezcount_ref: wdgRes = WCO_GUI_Ref()->MySpinButton11; ret = wdgRes; break;
        case task_subtraction_label_ref:    labRes = WCO_GUI_Ref()->MyLabel3; ret = labRes; break;

        //Reference to multiplication widgets
        case task_multiplication_digit_1_ref:   wdgRes = WCO_GUI_Ref()->MySpinButton3; ret = wdgRes; break;
        case task_multiplication_digit_2_ref:   wdgRes = WCO_GUI_Ref()->MySpinButton4; ret = wdgRes; break;
        case task_multiplication_dezcount_ref:  wdgRes = WCO_GUI_Ref()->MySpinButton12; ret = wdgRes; break;
        case task_multiplication_label_ref:     labRes = WCO_GUI_Ref()->MyLabel4; ret = labRes; break;

        //Reference to division widgets
        case task_division_digit_1_ref:     wdgRes = WCO_GUI_Ref()->MySpinButton6; ret = wdgRes; break;
        case task_division_digit_2_ref:     wdgRes = WCO_GUI_Ref()->MySpinButton7; ret = wdgRes; break;
        case task_division_dezcount_ref:    wdgRes = WCO_GUI_Ref()->MySpinButton13; ret = wdgRes; break;
        case task_division_label_ref:       labRes = WCO_GUI_Ref()->MyLabel5; ret = labRes; break;

        //Reference to the displayed GTK-Fixed
        case gtk_stack: wdgRes = gtk_stack_get_visible_child(GTK_STACK(WCO_GUI_Ref()->MyStack2)); ret = wdgRes; break;
        case gtk_fixed_1: wdgRes = WCO_GUI_Ref()->MySettingsFixed[0]; ret = wdgRes; break;
        case gtk_fixed_2: wdgRes = WCO_GUI_Ref()->MySettingsFixed[1]; ret = wdgRes; break;

        //Reference to the baseboard settings
        case base_baseboard_ref:    wdgRes = WCO_GUI_Ref()->MyCheckButton5; ret = wdgRes; break;
        case base_date_ref:         wdgRes = WCO_GUI_Ref()->MyCheckButton6; ret = wdgRes; break;
        case base_name_ref:         wdgRes = WCO_GUI_Ref()->MyCheckButton11; ret = wdgRes; break;
        case base_text_ref:         wdgRes = WCO_GUI_Ref()->MyEntry2; ret = wdgRes; break;

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
        case filename: sprintf(WCO_PDF_Ref()->fileName[0], "%s", WCO_ENTRY(input)); break;
        case foldername: sprintf(WCO_PDF_Ref()->folderName, "%s", WCO_ENTRY(input)); break;
        case savePDF: WCO_GUI_Ref()->savePDF = WCO_BUTTON(input); break;
        case saveFolder: WCO_GUI_Ref()->saveFolder = WCO_BUTTON(input); break;

        case label_addition:        gtk_label_set_text(WCO_GUI_Ref()->MyLabel2, WCO_CHAR(input)); break;
        case label_subtraction:     gtk_label_set_text(WCO_GUI_Ref()->MyLabel3, WCO_CHAR(input)); break;
        case label_multiplication:  gtk_label_set_text(WCO_GUI_Ref()->MyLabel4, WCO_CHAR(input)); break;
        case label_division:        gtk_label_set_text(WCO_GUI_Ref()->MyLabel5, WCO_CHAR(input)); break;
    }
}




