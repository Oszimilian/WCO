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

int WCO_Worksheet_Creat_Fraction_Start()
{
    int ret = _succeded;

    MyPDF.pdf = HPDF_New(Error_Handler, NULL);

    if (WCO_PDF_Check())
    {
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");

        ret = _error;

        goto failed;
    }else{
        printf("PDF wurde erfolgreich erzeugt \n");
    }

    WCO_PDF_SetupPage(_Tasks);

    WCO_Worksheet_Creat_FractionSheed(_Tasks);

    WCO_PDF_SavePDF(_Tasks);

    printf("Test before \n");  
    HPDF_Free(MyPDF.pdf);
    printf("Test after \n");

    WCO_PNG_Set_ConvertToPNG(0.23);



    failed:

    return ret;
}



void WCO_Worksheet_Creat_FractionSheed(int page)
{
    MyFraction_t *MyFraction = malloc(sizeof(MyFraction_t));

    MyFraction->frac[0][0] = 5000000;
    MyFraction->frac[0][1] = 500;
    MyFraction->frac[1][0] = 5000;
    MyFraction->frac[1][1] = 50000;
    MyFraction->frac[2][0] = 10;
    MyFraction->frac[2][1] = 1;

    MyFraction->operand = 0;

    int x = 200;
    int y = 200;

    WCO_PDF_DrawFractionTask(MyFraction, &x, &y, page);

    free(MyFraction);
    
}

int IntLen(int *i)
{
    char str[10];
    sprintf(str, "%d", *i);
    return strlen(str);
}

void WCO_PDF_DrawFractionTask(MyFraction_t *MyFrac, int *x, int *y, int page)
{
    
    const int patLen = 11;
    const int gabLen = 50;
    int numLen[2];
    int endPos[2];
    int staPos[2];
    int numPos[3][2][2];

    printf("Test \n");

    char *numStr = malloc(10 * sizeof(char));

    for (int i = 0; i <= 2; i++)
    {
        numLen[i] = (IntLen(&MyFrac->frac[i][0]) > IntLen(&MyFrac->frac[i][1])) ? IntLen(&MyFrac->frac[i][0]) : IntLen(&MyFrac->frac[i][1]);
        staPos[i] = (i == 0) ? *x : (staPos[i - 1] + (numLen[i] * patLen) + gabLen);
        endPos[i] = (i == 0) ? (staPos[i] + (numLen[i] * patLen)) : (staPos[i] + (numLen[i] * patLen));

        if ((page == _Tasks) && i == 2) break;

        WCO_PDF_DrawLine(staPos[i], *y, endPos[i], *y, page);

        for (int k = 0; k <= 1; k++)
        {
            sprintf(numStr, "%d", MyFrac->frac[i][k]);
            numPos[i][k][_X] = staPos[i] + patLen;
            numPos[i][k][_Y] = (k == 0) ? (*y + 5) : (*y - 15);
            WCO_PDF_WriteText(numPos[i][k][_X], numPos[i][k][_Y], numStr, page);
        }
    }

    switch (MyFrac->operand)
    {
        case 0: sprintf(numStr, "+"); break;
        case 1: sprintf(numStr, "-"); break;
        case 2: sprintf(numStr, "*"); break;
        case 3: sprintf(numStr, "/"); break;
        default: break;
    }

    WCO_PDF_WriteText((staPos[1] - (gabLen / 2) + 9), *y - 4, numStr, page);
 
    WCO_PDF_WriteText((endPos[1] + ((staPos[2] - endPos[1]) / 2) - 3), *y - 4, "=", page);

    if (page == _Tasks) WCO_PDF_DrawLine(staPos[2], *y - 20, endPos[2] + gabLen, *y - 20, page);

    free(numStr);
}