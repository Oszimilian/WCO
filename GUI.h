#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#define _ON 1
#define _OFF 0
#define _TRUE 1
#define _FALSE 0

typedef int bool;





enum Buttons{
    frac_zahler_1 = 0,
    frac_nenner_1 = 1,
    frac_zahler_2 = 2,
    frac_nenner_2 = 3,

    frac_addition = 4,
    frac_subtraction = 5,
    frac_multiplication = 6,
    frac_division = 7,

    task_setting,
    fraction_setting,

    entry_1,
};

struct WCO_GUI_t{
    GtkBuilder *MyBuilder;
    GtkWidget *MyWindow1;
    GtkWidget *MyFixed1;
    GtkWidget *MyWorksheetFixed[2];
    GtkWidget *MySettingsFixed[2];
    GtkLabel  *MyLabel1;
    GtkLabel  *MyLabel2;
    GtkLabel  *MyLabel3;
    GtkLabel  *MyLabel4;
    GtkLabel  *MyLabel5;
    GtkWidget *MyButton1;
    GtkWidget *MyButton2;
    GtkWidget *MyButton3;
    GtkWidget *MyButton4;
    GtkWidget *MyButton5;
    GtkWidget *MyCheckButton1;
    GtkWidget *MyCheckButton2;
    GtkWidget *MyCheckButton3;
    GtkWidget *MyCheckButton4;
    GtkWidget *MyCheckButton5;
    GtkWidget *MyCheckButton6;
    GtkWidget *MyCheckButton7;
    GtkWidget *MyCheckButton8;
    GtkWidget *MyCheckButton9;
    GtkWidget *MyCheckButton10;
    GtkWidget *MyRadioButton1;
    GtkWidget *MyRadioButton2;
    GtkWidget *MySpinButton1;
    GtkWidget *MySpinButton2;
    GtkWidget *MySpinButton3;
    GtkWidget *MySpinButton4;
    GtkWidget *MySpinButton5;
    GtkWidget *MySpinButton6;
    GtkWidget *MySpinButton7;
    GtkWidget *MySpinButton8;
    GtkWidget *MySpinButton9;
    GtkWidget *MySpinButton10;
    GtkWidget *MySpinButton11;
    GtkWidget *MySpinButton12;
    GtkWidget *MySpinButton13;
    GtkWidget *MySpinButton14;
    GtkWidget *MySpinButton15;
    GtkWidget *MySpinButton16;
    GtkWidget *MySpinButton17;
    GtkWidget *MyFileChosserButton1;
    GtkWidget *MyEntry1;
    GtkWidget *MyWorksheetImage[2];
    GtkStackSwitcher *MyStackSwitcher2;
    GtkWidget *MyStack2;
    //GtkWidget *MySpinButton18;


    int showPDF;
    int savePDF;
    int saveFolder;
    int showPNG;

    char **label;
}MyGUI;


void WCO_GUI_Init();
void WCO_GUI_Start();
void WCO_GUI_Start_PDFViewer();
void WCO_GUI_Close_PDFViewer();

void *WCO_GUI_PDFViewer();
void exitApp();

int WCO_GUI_Get_Stack();

int WCO_GUI_Status_Get_AllOperand_CheckButtons();
int WCO_GUI_Status_Get_SpecificOperand_CheckButton(int i);
int WCO_GUI_Status_Get_Addition_CheckButton();
int WCO_GUI_Status_Get_Subtraction_CheckButton();
int WCO_GUI_Status_Get_Multiplication_CheckButton();
int WCO_GUI_Status_Get_Division_CheckButton();
int WCO_GUI_Status_Get_AdditionDigitRange_SpinButton(int i);
int WCO_GUI_Status_Get_SubtractionDigitRange_SpinButton(int i);
int WCO_GUI_Status_Get_MultiplicationDigitRange_SpinButton(int i);
int WCO_GUI_Status_Get_DivisionDigitRange_SpinButton(int i);
int WCO_GUI_Status_Get_SpecificOperandDigitRange_spinButton(int operand, int i);
int WCO_GUI_Status_Get_AdditionDecimalPlaces_SpinButton();
int WCO_GUI_Status_Get_SubtractionDecimalPlaces_SpinButton();
int WCO_GUI_Status_Get_MultiplicationDecimalPlaces_SpinButton();
int WCO_GUI_Status_Get_DevisionDecimalPlaces_SpinButton();
int WCO_GUI_Status_Get_SpecificOperandDecimalPlaces_SpinButton(int operand);
int WCO_GUI_Status_Get_PDFViewer();
int WCO_GUI_Status_Get_ShowPNG();

void WCO_GUI_Status_Set_ShowPNG();

void WCO_GUI_Status_Reset_ShowPNG();

void *WCO_GUI_Get(int i);

const char *WCO_GUI_Status_FileName();
int WCO_GUI_Status_SaveButton4();
char *WCO_GUI_Status_FolderName();
int WCO_GUI_Status_FolderButton();
int WCO_GUI_Status_Baseboard_CheckButton5();

void WCO_GUI_Update_Addition();
void WCO_GUI_Update_Subtraction();
void WCO_GUI_Update_Multiplication();
void WCO_GUI_Update_Division();

void WCO_GUI_Update_PermissionButton1();

void WCO_GUI_Update_Set_SavePDF();
void WCO_GUI_Update_Reset_SavePDF();
void WCO_GUI_Update_Set_SaveFolder();
void WCO_GUI_Update_Reset_SaveFolder();

void WCO_GUI_Show_Worksheet(int page);

#endif