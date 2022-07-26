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

#define WCO_ENTRY(obj)  ((gchar *)(obj))
#define WCO_BUTTON(obj) (*(gboolean*)(obj))

/*
*   This function actually builds the worksheets
*/
void WCO_Worksheet_Fraction_Start()
{
    MyFraction_t *MyFraction = WCO_Worksheet_Fraction_Init();

    WCO_PDF_Ref()->pdf = HPDF_New(Error_Handler, NULL);

    if (WCO_PDF_Check())
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    else
        printf("PDF wurde erfolgreich erzeugt \n");
    
    WCO_PDF_SetupPage(_Tasks);

    WCO_Worksheet_Fraction_Creat(MyFraction, _Tasks);

    WCO_PDF_SavePDF(_Tasks);

    HPDF_NewDoc(WCO_PDF_Ref()->pdf);

    WCO_PDF_SetupPage(_Solutions);

    WCO_Worksheet_Fraction_Creat(MyFraction, _Solutions);

    WCO_PDF_SavePDF(_Solutions);

    HPDF_Free(WCO_PDF_Ref()->pdf);

    WCO_PNG_Set_ConvertToPNG(0.23);

    WCO_Worksheet_Fraction_Free(MyFraction);
}

/*
*   This function creats space on the heap and returns a pointer to this storage space on which the worksheet is stored
*/
MyFraction_t *WCO_Worksheet_Fraction_Init()
{
    MyFraction_t *MyFraction = malloc(sizeof(MyFraction_t));
    if(MyFraction == NULL)
    {
        fprintf(stderr, "Worksheet_Fraction konnte nicht erzeugt werden! \n");
        return NULL;
    }
    WCO_Worksheet_Fraction_Default(MyFraction);
    return MyFraction;
}

/*
*   This function sets up a default worksheet (only for developing)
*/
void WCO_Worksheet_Fraction_Default(MyFraction_t *Frac)
{
    for(int i = 0; i <= 49; i++)
    {
        for(int k = 0; k <= 2; k++)
        {
            for(int j = 0; j <= 1; j++)
            {
                Frac->frac[i][k][j] = 100;
            }
        }
    }
}

/*
*   This function creats the the sheet 
*/
void WCO_Worksheet_Fraction_Creat(MyFraction_t *MyFraction, int page)
{
    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[2];

    startx[0] = HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) * 0.5);

    WCO_Worksheet_Baseboard_Creat(page);
    if (WCO_BUTTON(WCO_GUI_Get(base_baseboard)))
    {
        pageSize = HPDF_Page_GetHeight(WCO_PDF_Ref()->page[page]) - *WCO_Worksheet_Baseboard_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(WCO_PDF_Ref()->page[page]) - 50;
    }


    for(int i = 0; i <= 1; i++)
    {
        pageSizeCounter = pageSize;

        while(pageSizeCounter >= 100)
        {
            if (page == _Tasks) WCO_Worksheet_Fraction_Random(MyFraction, taskCounter);

            if (page == _Tasks) WCO_Worksheet_Fraction_Calculate(MyFraction, taskCounter);

            WCO_Worksheet_Fraction_Draw(MyFraction, &startx[i], &pageSizeCounter, taskCounter, page);

            pageSizeCounter -= 50;

            taskCounter ++;
        }
    }

    if(WCO_BUTTON(WCO_GUI_Get(solution_advice)) && page == _Tasks) WCO_Worksheet_Fraction_Suggestion(MyFraction, taskCounter, page);
}

/*
*   This function creats a random task
*/
void WCO_Worksheet_Fraction_Random(MyFraction_t *MyFrac, int count)
{
    if (count == 0) srand(time(NULL));
    int place = 0;
    for(int i = 0; i <= 1; i++)
    {
        for(int k = 0; k <= 1; k++)
        {
            do
            {
                MyFrac->frac[count][i][k] = rand() % *(int*)WCO_GUI_Get(place);
            } while (MyFrac->frac[count][i][k] <= 0);
            place ++;
        }
    }
    
    while(1)
    {
        MyFrac->operand[count] = rand() % 4;
        if(WCO_BUTTON(WCO_GUI_Get(frac_addition + MyFrac->operand[count]))) break;
    }
}

/*
*   This function calculates the fractions 
*/
void WCO_Worksheet_Fraction_Calculate(MyFraction_t *MyFrac, int count)
{
    int fraction[3][2];
    if (MyFrac->operand[count] == 0)
    {
        fraction[0][1] = MyFrac->frac[count][0][1] * MyFrac->frac[count][1][1];
        fraction[1][1] = MyFrac->frac[count][0][1] * MyFrac->frac[count][1][1];

        fraction[0][0] = MyFrac->frac[count][0][0] * MyFrac->frac[count][1][1];
        fraction[1][0] = MyFrac->frac[count][1][0] * MyFrac->frac[count][0][1];

        fraction[2][0] = fraction[0][0] + fraction[1][0];
        fraction[2][1] = fraction[1][1];

        if (fraction[2][0] < 0)
        {
            fraction[2][0] *= -1;
            MyFrac->negFlag[count] = _TRUE;
        }else{
            MyFrac->negFlag[count] = _FALSE;
        }

        MyFrac->frac[count][2][0] = fraction[2][0];

        MyFrac->frac[count][2][1] = fraction[2][1];
    }
    if (MyFrac->operand[count] == 1)
    {
        fraction[0][1] = MyFrac->frac[count][0][1] * MyFrac->frac[count][1][1];
        fraction[1][1] = MyFrac->frac[count][0][1] * MyFrac->frac[count][1][1];

        fraction[0][0] = MyFrac->frac[count][0][0] * MyFrac->frac[count][1][1];
        fraction[1][0] = MyFrac->frac[count][1][0] * MyFrac->frac[count][0][1];

        fraction[2][0] = fraction[0][0] - fraction[1][0];
        fraction[2][1] = fraction[1][1];

        if (fraction[2][0] < 0)
        {
            fraction[2][0] *= -1;
            MyFrac->negFlag[count] = _TRUE;
        }else{
            MyFrac->negFlag[count] = _FALSE;
        }

        MyFrac->frac[count][2][0] = fraction[2][0];
        MyFrac->frac[count][2][1] = fraction[2][1];
    }
    if (MyFrac->operand[count] == 2)
    {
        MyFrac->frac[count][2][0] = MyFrac->frac[count][0][0] * MyFrac->frac[count][1][0];
        MyFrac->frac[count][2][1] = MyFrac->frac[count][0][1] * MyFrac->frac[count][1][1];

        MyFrac->negFlag[count] = _FALSE;
    }
    if (MyFrac->operand[count] == 3)
    {
        fraction[1][0] = MyFrac->frac[count][1][1];
        fraction[1][1] = MyFrac->frac[count][1][0];

        MyFrac->frac[count][2][0] = MyFrac->frac[count][0][0] * fraction[1][0];
        MyFrac->frac[count][2][1] = MyFrac->frac[count][0][1] * fraction[1][1];

        MyFrac->negFlag[count] = _FALSE;
    }

    WCO_Worksheet_Fraction_Simplify(MyFrac, count);
}

/*
*   This function simplifies the fraction 
*/
void WCO_Worksheet_Fraction_Simplify(MyFraction_t *MyFrac, int count)
{
    int highNum = (MyFrac->frac[count][2][0]>MyFrac->frac[count][2][1]) ? MyFrac->frac[count][2][0] : MyFrac->frac[count][2][1];

    for (int i = 2; i <= highNum; i++)
    {
        while(((MyFrac->frac[count][2][0] % i) == 0) && ((MyFrac->frac[count][2][1] % i) == 0))
        {
            MyFrac->frac[count][2][0] /= i;
            MyFrac->frac[count][2][1] /= i;
        }
    }
}

/*
*   This function draws the fractions on the pdf-sheet
*/
void WCO_Worksheet_Fraction_Draw(MyFraction_t *MyFrac, int *x, int *y,int count, int page)
{
    const int patLen = 15;
    const int gabLen = 30;
    const int enumLen = 50;
    int numLen[3];
    int endPos[3];
    int staPos[3];
    int numPos[3][2][2];
    char ops[4] = "+-*:";
    int printSol = (page == _Solutions) ? 2 : 1;

    char *numStr = malloc(10 * sizeof(char));

    char *enum_task = (char*) malloc(sizeof(char) * ((WCO_BUTTON(WCO_GUI_Get(task_enum)))? 6:1 ) );
    if (WCO_BUTTON(WCO_GUI_Get(task_enum)))
    {
        sprintf(enum_task, "(%d): ", (count + 1));
    }else{
        sprintf(enum_task, " ");
    }

    for (int i = 0; i <= 2; i++)
    {
        numLen[i] = (IntLen(&MyFrac->frac[count][i][0]) > IntLen(&MyFrac->frac[count][i][1])) ? IntLen(&MyFrac->frac[count][i][0]) : IntLen(&MyFrac->frac[count][i][1]);
        staPos[i] = (i == 0) ? *x : (staPos[i - 1] + (numLen[i] * patLen) + gabLen);
        endPos[i] = (i == 0) ? (staPos[i] + (numLen[i] * patLen)) : (staPos[i] + (numLen[i] * patLen));

        if (WCO_BUTTON(WCO_GUI_Get(task_enum)) && i == 0)
        {
            WCO_PDF_WriteText(staPos[i], *y - 2, enum_task, page);

            staPos[i] += enumLen;
            endPos[i] += enumLen;
        }

        if (printSol == 1 && i == 2)
        {
            break;
        }else{

            WCO_PDF_DrawLine(staPos[i], *y, endPos[i], *y, page);
        }
 

        for (int k = 0; k <= 1; k++)
        {
            sprintf(numStr, "%d", MyFrac->frac[count][i][k]);
            numPos[i][k][_X] = staPos[i] + (patLen / 2) - 2;
            numPos[i][k][_Y] = (k == 0) ? (*y + 5) : (*y - 15);
    
            WCO_PDF_WriteText(numPos[i][k][_X], numPos[i][k][_Y], numStr, page);
        }
    }
        
    if(MyFrac->negFlag[count] && page == _Solutions) WCO_PDF_DrawLine((staPos[2]-10), *y, (staPos[2]-5) , *y, page);
        
    sprintf(numStr, "%c", ops[MyFrac->operand[count]]);

    WCO_PDF_WriteText((endPos[0] + ((staPos[1] - endPos[0]) / 2) - 3), *y - 4, numStr, page);
 
    if (MyFrac->negFlag[count])
    {
        WCO_PDF_WriteText((endPos[1] + ((staPos[2] - endPos[1]) / 2) - 10), *y - 4, "=", page);
    }else{
        WCO_PDF_WriteText((endPos[1] + ((staPos[2] - endPos[1]) / 2) - 3), *y - 4, "=", page);
    }

    free(numStr);
}

/*
*   This function frees the space in the heap of the worksheet struct
*/
void WCO_Worksheet_Fraction_Free(MyFraction_t *MyFraction)
{
    free(MyFraction);
}

/*
*   this function gets a pointer to a integar and returns the amount of digits
*/
int IntLen(int *i)
{
    char str[10];
    sprintf(str, "%d", *i);
    return strlen(str);
}

int floatLen(float f)
{
    char str[20];
    sprintf(str, "%f", f);
    return strlen(str);
}

void WCO_Worksheet_Fraction_Suggestion(MyFraction_t *MyFrac, int max_task, int page)
{
    WCO_Worksheet_Get_Rand_List(max_task - 1);
    int x = 50;
    int y = 50;
    const int cabLen = 10;
    int rand;

    for (int i = 0; i <= (max_task - 1); i++)
    {  
        rand = WCO_Rand_Ref()->rand_list[i];
        printf("%d -> %d:%d %d:%d %d:%d \n", rand, MyFrac->frac[rand][0][0], MyFrac->frac[rand][0][1], MyFrac->frac[rand][1][0], MyFrac->frac[rand][1][1], MyFrac->frac[rand][2][0], MyFrac->frac[rand][2][1]);
        x += (int)(cabLen + WCO_Worksheet_Fraction_Draw_Single_Fraction(x, y, MyFrac->frac[rand][2][0], MyFrac->frac[rand][2][1], MyFrac->negFlag[rand], page));

        if (x >= (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - 100))
        {
            x = 50;
            y -= 25;
        }

        
    }
}

int WCO_Worksheet_Fraction_Draw_Single_Fraction(int x, int y, int a, int b, int neg, int page)
{
    HPDF_Font font = HPDF_GetFont(WCO_PDF_Ref()->pdf, "Courier", NULL);
    HPDF_Page_SetFontAndSize(WCO_PDF_Ref()->page[page], font, 8);

    

    static int i = 0;

    const int patLen = 10;
    char num1[IntLen(&a)];
    char num2[IntLen(&b)];
    if (neg) a *= -1;
    sprintf(num1, "%d", a);
    sprintf(num2, "%d", b);
    int fracLen = (IntLen(&a) > IntLen(&b)) ? (IntLen(&a) * patLen) : (IntLen(&b) * patLen);
    WCO_PDF_DrawLine(x, y, (x + fracLen), y, page);
    WCO_PDF_WriteText((x + 2), (y + 2), num1, page);
    WCO_PDF_WriteText((x + 2), (y - 8), num2, page);

    return fracLen;
}







