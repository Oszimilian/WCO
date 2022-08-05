#ifndef WORKSHEET_H_INCLUDED
#define WORKSHEET_H_INCLUDED

#define _enable 1
#define _disable 0
#define _succeded 1
#define _error 0
#define _Tasks 0
#define _Solutions 1

#define _Terms 0 
#define _Fractions 1

#define _X 0
#define _Y 1

struct WCO_Worksheet_t{
    int printBaseboard;
    int baseboardThreashold;
    char task[2][50][50];
}MyWorksheet;

typedef struct Fraction_s
{
    int frac[3][2];
    int operand;

}MyFraction_t;



void WCO_Worksheet_Init();

int WCO_Worksheet_Status_Baseboard();
int WCO_Worksheet_Status_Threashold();
float WCO_Worksheet_Status_Calculation(int operand, float *a, float *b);
char* WCO_Worksheet_Status_Task(int number, int page);
char* WCO_Worksheet_Status_GetDate(char *str);
char *WCO_Worksheet_Status_Get_ConvertCommand();

int WCO_Worksheet_Create_Start();
int WCO_Worksheet_Creat_Baseboard(int page);
int WCO_Worksheet_Create_RandomTask(int counter);
int WCO_Worksheet_Creat_TaskSheet();
int WCO_Worksheet_Create_SolutionSheed();

void WCO_Worksheet_Status_Config_Baseboard(int i);

int WCO_Worksheet_Creat_Fraction_Start();
void WCO_Worksheet_Creat_FractionSheed(int page);

void WCO_PDF_DrawFractionTask(MyFraction_t *MyFrac, int *x, int *y, int page);

int IntLen(int *i);

#endif