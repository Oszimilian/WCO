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

#include "hpdf.h"
#include "GUI_Call.h"
#include "GUI.h"
#include "PDF.h"
#include "Worksheet.h"
#include "PNG.h"
#include "Worksheet_Creat_Fraction.h"
#include "Worksheet_Creat_Task.h"
#include "Worksheet_Baseboard.h"

#define WCO_ENTRY(obj)  ((gchar *)(obj))
#define WCO_BUTTON(obj) (*(gboolean*)(obj))

void WCO_Worksheet_Fraction_Start()
{
    MyFraction_t *MyFraction = WCO_Worksheet_Fraction_Init();

    /*
    WCO_PDF_SetFoldername("/home/maximilian/Git/WCO/PDF");
    WCO_PDF_SetFilename("001", _Tasks);
    WCO_PDF_SetFilename("001", _Solutions);
    */

    MyPDF.pdf = HPDF_New(Error_Handler, NULL);

    if (WCO_PDF_Check())
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    else
        printf("PDF wurde erfolgreich erzeugt \n");
    
    WCO_PDF_SetupPage(_Tasks);

    WCO_Worksheet_Fraction_Creat(MyFraction, _Tasks);

    WCO_PDF_SavePDF(_Tasks);

    HPDF_NewDoc(MyPDF.pdf);

    WCO_PDF_SetupPage(_Solutions);

    WCO_Worksheet_Fraction_Creat(MyFraction, _Solutions);

    WCO_PDF_SavePDF(_Solutions);

    HPDF_Free(MyPDF.pdf);

    WCO_PNG_Set_ConvertToPNG(0.23);

    WCO_Worksheet_Fraction_Free(MyFraction);
}

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

void WCO_Worksheet_Fraction_Creat(MyFraction_t *MyFraction, int page)
{
    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[2];

    startx[0] = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.5);

    WCO_Worksheet_Baseboard_Creat(page);
    if (WCO_BUTTON(WCO_GUI_Get(base_baseboard)))
    {
        pageSize = HPDF_Page_GetHeight(MyPDF.page[page]) - *WCO_Worksheet_Baseboard_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(MyPDF.page[page]) - 50;
    }


    for(int i = 0; i <= 1; i++)
    {
        pageSizeCounter = pageSize;

        while(pageSizeCounter >= 50)
        {
            if (page == _Tasks) WCO_Worksheet_Fraction_Random(MyFraction, taskCounter);

            if (page == _Tasks) WCO_Worksheet_Fraction_Calculate(MyFraction, taskCounter);

            WCO_Worksheet_Fraction_Draw(MyFraction, &startx[i], &pageSizeCounter, taskCounter, page);

            pageSizeCounter -= 50;

            taskCounter ++;
        }
    }
}

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

void WCO_Worksheet_Fraction_Draw(MyFraction_t *MyFrac, int *x, int *y,int count, int page)
{
    const int patLen = 15;
    const int gabLen = 30;
    int numLen[3];
    int endPos[3];
    int staPos[3];
    int numPos[3][2][2];
    char ops[4] = "+-*/";
    int printSol = (page == _Solutions) ? 2 : 1;

    char *numStr = malloc(10 * sizeof(char));

    for (int i = 0; i <= 2; i++)
    {
        numLen[i] = (IntLen(&MyFrac->frac[count][i][0]) > IntLen(&MyFrac->frac[count][i][1])) ? IntLen(&MyFrac->frac[count][i][0]) : IntLen(&MyFrac->frac[count][i][1]);
        staPos[i] = (i == 0) ? *x : (staPos[i - 1] + (numLen[i] * patLen) + gabLen);
        endPos[i] = (i == 0) ? (staPos[i] + (numLen[i] * patLen)) : (staPos[i] + (numLen[i] * patLen));

        if (printSol == 1 && i == 2)
        {
            break;
        }else{
            //staPos[i] = (MyFrac->negFlag[count]) ? (staPos[i] + 10) : staPos[i];
            //endPos[i] = (MyFrac->negFlag[count]) ? (endPos[i] + 10) : endPos[i];
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

void WCO_Worksheet_Fraction_Free(MyFraction_t *MyFraction)
{
    free(MyFraction);
}

int IntLen(int *i)
{
    char str[10];
    sprintf(str, "%d", *i);
    return strlen(str);
}







