#define Linux 1
#define Windows 2

//#define OP Linux

#ifndef GUI_CALL_H_INCLUDED
#define GUI_CALL_H_INCLUDED

#if OP == Linux
void MyButton1_Clicked(GtkButton *b);
void MyButton2_Clicked(GtkButton *b);

void MyCheckButton1_Toggled(GtkCheckButton *b);
void MyCheckButton2_Toggled(GtkCheckButton *b);
void MyCheckButton3_Toggled(GtkCheckButton *b);
void MyCheckButton4_Toggled(GtkCheckButton *b);

void MyCheckButton5_Toggled(GtkCheckButton *b);
void MyCheckButton6_Toggled(GtkCheckButton *b);
void MyCheckButton11_Changed(GtkCheckButton *b);
void MyEntry2_Changed(GtkCheckButton *b);

void MyRadioButton1_Toggled(GtkRadioButton *b);
void MyRadioButton2_Toggled(GtkRadioButton *b);
void MySpinButton1_Changed(GtkSpinButton *s);

void MySpinButton2_Changed(GtkSpinButton *s);
void MySpinButton8_Changed(GtkSpinButton *s);
void MySpinButton5_Changed(GtkSpinButton *s);
void MySpinButton9_Changed(GtkSpinButton *s);
void MySpinButton3_Changed(GtkSpinButton *s);
void MySpinButton4_Changed(GtkSpinButton *s);
void MySpinButton6_Changed(GtkSpinButton *s);
void MySpinButton7_Changed(GtkSpinButton *s);

void MySpinButton10_Changed(GtkSpinButton *s);
void MySpinButton11_Changed(GtkSpinButton *s);
void MySpinButton12_Changed(GtkSpinButton *s);
void MySpinButton13_Changed(GtkSpinButton *s);


void MyEntry1_Changed(GtkEntry *e);
void MyButton4_Clicked(GtkButton *b);
void MyFileChooserButton1_Clicked();
void MyButton5_Clicked(GtkButton *b);

void MySpinButton14_Changed(GtkSpinButton *b);
void MySpinButton15_Changed(GtkSpinButton *b);
void MySpinButton16_Changed(GtkSpinButton *b);
void MySpinButton17_Changed(GtkSpinButton *b);

void MyCheckButton7_Changed(GtkCheckButton *b);
void MyCheckButton8_Changed(GtkCheckButton *b);
void MyCheckButton9_Changed(GtkCheckButton *b);
void MyCheckButton10_Changed(GtkCheckButton *b);

void MyStackSwitcher2_Changed();
#endif

#if OP == Windows
G_MODULE_EXPORT void MyButton1_Clicked(GtkButton *b);
G_MODULE_EXPORT void MyButton2_Clicked(GtkButton *b);

G_MODULE_EXPORT void MyCheckButton1_Toggled(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton2_Toggled(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton3_Toggled(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton4_Toggled(GtkCheckButton *b);

G_MODULE_EXPORT void MyCheckButton5_Toggled(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton6_Toggled(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton11_Changed(GtkCheckButton *b);
G_MODULE_EXPORT void MyEntry2_Changed(GtkCheckButton *b);

G_MODULE_EXPORT void MyRadioButton1_Toggled(GtkRadioButton *b);
G_MODULE_EXPORT void MyRadioButton2_Toggled(GtkRadioButton *b);
G_MODULE_EXPORT void MySpinButton1_Changed(GtkSpinButton *s);

G_MODULE_EXPORT void MySpinButton2_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton8_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton5_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton9_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton3_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton4_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton6_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton7_Changed(GtkSpinButton *s);

G_MODULE_EXPORT void MySpinButton10_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton11_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton12_Changed(GtkSpinButton *s);
G_MODULE_EXPORT void MySpinButton13_Changed(GtkSpinButton *s);

G_MODULE_EXPORT void MyFileChooserButton1_Clicked();
G_MODULE_EXPORT void MyEntry1_Changed(GtkEntry *e);
G_MODULE_EXPORT void MyButton4_Clicked(GtkButton *b);

G_MODULE_EXPORT void MyButton5_Clicked(GtkButton *b);

G_MODULE_EXPORT void MySpinButton14_Changed(GtkSpinButton *b);
G_MODULE_EXPORT void MySpinButton15_Changed(GtkSpinButton *b);
G_MODULE_EXPORT void MySpinButton16_Changed(GtkSpinButton *b);
G_MODULE_EXPORT void MySpinButton17_Changed(GtkSpinButton *b);

G_MODULE_EXPORT void MyCheckButton7_Changed(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton8_Changed(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton9_Changed(GtkCheckButton *b);
G_MODULE_EXPORT void MyCheckButton10_Changed(GtkCheckButton *b);

G_MODULE_EXPORT void MyStackSwitcher2_Changed();

#endif

#endif
