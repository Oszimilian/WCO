#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#define _ON 1
#define _OFF 0
#define _TRUE 1
#define _FALSE 0

#define _ADDITION 0
#define _SUBTRACTION 1
#define _MULTIPLICATION 2
#define _DIVISION 3

typedef int bool;

typedef struct{
    GtkBuilder *MyBuilder;
    GtkWidget *MyWindow1;
    GtkWidget *MyFixed1;
    GtkWidget *MyWorksheetFixed[2];
    GtkWidget *MySettingsFixed[2];

    //GtkLabel  *MyLabel1;
    GtkLabel  *MyLabel2;
    GtkLabel  *MyLabel3;
    GtkLabel  *MyLabel4;
    GtkLabel  *MyLabel5;

    GtkWidget *MyButton1;
    //GtkWidget *MyButton2;
    GtkWidget *MyButton3;
    GtkWidget *MyButton4;
    //GtkWidget *MyButton5;

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
    GtkWidget *MyCheckButton11;
    GtkWidget *MyCheckButton12;
    GtkWidget *MyCheckButton13;

    //GtkWidget *MyRadioButton1;
    //GtkWidget *MyRadioButton2;

    //GtkWidget *MySpinButton1;
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


    GtkWidget *MyFileChooserButton1;

    GtkWidget *MyEntry1;
    GtkWidget *MyEntry2;

    GtkWidget *MyWorksheetImage[2];

    GtkStackSwitcher *MyStackSwitcher2;
    GtkWidget *MyStack2;
    //GtkWidget *MySpinButton18;

    GtkWidget *MyDrawArea[2];

    int savePDF;
    int saveFolder;
    int showPNG;

    char **label;
    char folderName[100];
}MyGUI_t;





void WCO_GUI_Start();
void WCO_GUI_Init();
void exitApp();
int WCO_GUI_Get_Stack();
void WCO_GUI_Show_Worksheet(int page);


#endif