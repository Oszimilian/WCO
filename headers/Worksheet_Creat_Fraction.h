/*
*
*   STRUCT FOR GENERATING A FRACTION-SHEET
*   
*/
typedef struct 
{
    int frac[50][3][2];
    int operand[50];
    int negFlag[50];

}MyFraction_t;

/*
*
*   FUNKTIONS FOR CREAT_FRACTION
*
*/
void WCO_Worksheet_Fraction_Start();
void WCO_Worksheet_Fraction_Default(MyFraction_t *Frac);
MyFraction_t *WCO_Worksheet_Fraction_Init();
void WCO_Worksheet_Fraction_Free(MyFraction_t *MyFraction);
void WCO_Worksheet_Fraction_Random(MyFraction_t *MyFrac, int count);
void WCO_Worksheet_Fraction_Simplify(MyFraction_t *MyFrac, int count);
void WCO_Worksheet_Fraction_Calculate(MyFraction_t *MyFrac, int count);
void WCO_Worksheet_Fraction_Creat(MyFraction_t *MyFraction, int page);
int IntLen(int *i);
int floatLen(float f);
void WCO_Worksheet_Fraction_Draw(MyFraction_t *MyFrac, int *x, int *y,int count, int page);
int WCO_Worksheet_Fraction_Draw_Single_Fraction(int x, int y, int a, int b, int neg, int page);
void WCO_Worksheet_Fraction_Suggestion(MyFraction_t *MyFrac, int max_task, int page);
