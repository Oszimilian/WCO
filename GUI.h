#define _ON 1
#define _OFF 0
#define _TRUE 1
#define _FALSE 0

typedef struct {
    GtkBuilder *MyBuilder;
    GtkWidget *MyWindow1;
    GtkWidget *MyFixed1;
    GtkLabel  *MyLabel1;
    GtkLabel  *MyLabel2;
    GtkLabel  *MyLabel3;
    GtkLabel  *MyLabel4;
    GtkLabel  *MyLabel5;
    GtkWidget *MyButton1;
    GtkWidget *MyButton2;
    GtkWidget *MyButton3;
    GtkWidget *MyButton4;
    GtkWidget *MyCheckButton1;
    GtkWidget *MyCheckButton2;
    GtkWidget *MyCheckButton3;
    GtkWidget *MyCheckButton4;
    GtkWidget *MyCheckButton5;
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
    GtkWidget *MyFileChosserButton1;
    GtkWidget *MyEntry1;

    int showPDF;
}WCO_GUI_t;
    
WCO_GUI_t MyGUI = {
    .showPDF = _OFF
};

void WCO_GUI_Start();

void exitApp();
void WCO_GUI_Start_PDFViewer();
void WCO_GUI_Close_PDFViewer();
int WCO_GUI_Status_PDFViewer();

void *WCO_GUI_PDFViewer();

int WCO_GUI_Status_AllOperant_CheckButtons();
int WCO_GUI_Status_SpecificOperand_CheckButton(int i);
int WCO_GUI_Status_AdditionCheck_CheckButton();
int WCO_GUI_Status_Subtraction_CheckButton();
int WCO_GUI_Status_Multiplication_CheckButton();
int WCO_GUI_Status_DivisionButton_CheckButton();
int WCO_GUI_Status_Addition_SpinButton(int i);
int WCO_GUI_Status_Subtraction_SpinButton(int i);
int WCO_GUI_Status_Multiplication_SpinButton(int i);
int WCO_GUI_Status_Division_SpinButton(int i);
int WCO_GUI_Status_SpecificOperand_SpinButton(int operand, int i);
int WCO_GUI_Status_Addition_DecimalPlaces();
int WCO_GUI_Status_Subtraction_DecimalPlaces();
int WCO_GUI_Status_Multiplication_DecimalPlaces();
int WCO_GUI_Status_Division_DecimalPlaces();
int WCO_GUI_Status_SpecificOperand_DecimalPlaces(int i);


