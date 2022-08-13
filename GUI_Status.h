void *WCO_GUI_Get(int i);
void WCO_GUI_Set(void *input, int verify);

#define WCO_ENTRY(obj)  ((gchar *)(obj))
#define WCO_BUTTON(obj) (*(gboolean*)(obj))
#define WCO_CHAR(obj) ((char*)(obj))
#define WCO_WDG(obj) ((GtkWidget*)(obj))
#define WCO_LAB(obj) ((GtkLabel*)(obj))
#define WCO_INT(obj) ((int*)(obj))

enum Gets{
    frac_zahler_1 = 0,
    frac_nenner_1 = 1,
    frac_zahler_2 = 2,
    frac_nenner_2 = 3,

    frac_addition,
    frac_subtraction,
    frac_multiplication,
    frac_division,

    task_addition,
    task_subtraction,
    task_multiplication ,
    task_division,

    task_addition_digit_1_ref,
    task_addition_digit_2_ref,
    task_addition_dezcount_ref,
    task_addition_label_ref,

    task_subtraction_digit_1_ref,
    task_subtraction_digit_2_ref,
    task_subtraction_dezcount_ref,
    task_subtraction_label_ref,
    
    task_multiplication_digit_1_ref,
    task_multiplication_digit_2_ref,
    task_multiplication_dezcount_ref,
    task_multiplication_label_ref,

    task_division_digit_1_ref,
    task_division_digit_2_ref,
    task_division_dezcount_ref,
    task_division_label_ref,

    task_addition_digit_1,
    task_subtraction_digit_1,
    task_multiplication_digit_1,
    task_division_digit_1,
    
    task_addition_digit_2,
    task_subtraction_digit_2,
    task_multiplication_digit_2,
    task_division_digit_2,

    task_addition_dezcount,
    task_subtraction_dezcount,
    task_multiplication_dezcount,
    task_division_dezcount,

    task_setting,
    fraction_setting,

    base_baseboard,
    base_date,
    base_name,
    base_text,

    base_baseboard_ref,
    base_date_ref,
    base_name_ref,
    base_text_ref,


    entry_1,
    savePDFButton,
    saveFolderButton,
    creatButton_ref,
    folder_name,

    gtk_stack,
    gtk_fixed_1,
    gtk_fixed_2,
};

enum Sets{

    filename,
    foldername,
    savePDF,
    saveFolder,

    label_addition,
    label_subtraction,
    label_multiplication,
    label_division,

};