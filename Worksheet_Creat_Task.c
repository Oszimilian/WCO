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


void WCO_Worksheet_Task_Start()
{
    MyTask_t *MyTask = WCO_Worksheet_Task_Init();

    MyPDF.pdf = HPDF_New(Error_Handler, NULL);

    if (WCO_PDF_Check())
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    else
        printf("PDF wurde erfolgreich erzeugt \n");

    WCO_PDF_SetupPage(_Tasks);

    WCO_Worksheet_Task_Creat(MyTask, _Tasks);

    WCO_PDF_SavePDF(_Tasks);

    HPDF_NewDoc(MyPDF.pdf);

    WCO_PDF_SetupPage(_Solutions);

    WCO_Worksheet_Task_Creat(MyTask, _Solutions);

    WCO_PDF_SavePDF(_Solutions);

    WCO_Worksheet_Task_Free(MyTask);

    WCO_PNG_Set_ConvertToPNG(0.23);
}

MyTask_t *WCO_Worksheet_Task_Init()
{
    MyTask_t *MyTask = malloc(sizeof(MyTask_t));
    if(MyTask == NULL)
    {
        fprintf(stderr, "Worksheet_Task konnte nicht erzeugt werden! \n");
    }
    WCO_Worksheet_Task_Default(MyTask);
    return MyTask;
}

void WCO_Worksheet_Task_Default(MyTask_t *MyTask)
{
    for(int i = 0; i <= 1; i++)
    {
        for(int k = 0; k <= 49; k++)
        {
            if (i == 0) sprintf(MyTask->task[i][k], "1 + 1 = ");
            else sprintf(MyTask->task[i][k], "1 + 1 = 2");
        }
    }
    /*
    WCO_PDF_SetFoldername("/home/maximilian/Git/WCO/PDF");
    WCO_PDF_SetFilename("001", _Tasks);
    WCO_PDF_SetFilename("001", _Solutions);
    */
}

void WCO_Worksheet_Task_Free(MyTask_t *MyTask)
{
    free(MyTask);
}

void WCO_Worksheet_Task_Creat(MyTask_t *MyTask, int page)
{
    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[3];

    startx[0] = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.6);
    startx[2] = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.3);

    WCO_Worksheet_Baseboard_Creat(page);

    pageSize = HPDF_Page_GetHeight(MyPDF.page[page]) - *WCO_Worksheet_Baseboard_Threashold();

    for(int i = 0; i <= 2; i++)
    {
        pageSizeCounter = pageSize;

        while(pageSizeCounter >= 50)
        {
            if (page == _Tasks) WCO_Worksheet_Task_Random(MyTask, taskCounter);

            WCO_Worksheet_Task_Draw(MyTask, &startx[i], &pageSizeCounter, taskCounter, page);

            pageSizeCounter -= 50;

            taskCounter ++;
        }
    }
}

void WCO_Worksheet_Task_Random(MyTask_t *MyTask, int count)
{
    int digit[2];
    float value[2];
    float solution[2];
    char ops[4] = "+-*/";
    

    if(count == 0) srand(time(NULL));

    while(1)
    {
        MyTask->operand[count] = rand() % 4;
        if(WCO_BUTTON(WCO_GUI_Get(task_addition + MyTask->operand[count]))) break;
    }

    for(int i = 0; i <= 1; i++)
    {
        switch (WCO_BUTTON(WCO_GUI_Get(task_addition_digit_1 + MyTask->operand[count] + ((!i) ? 0 : 4) )))
        {
            case 1: digit[i]  = 10;       break;
            case 2: digit[i]  = 100;      break;
            case 3: digit[i]  = 1000;     break;
            case 4: digit[i]  = 10000;    break;
            case 5: digit[i]  = 100000;   break;
            case 6: digit[i]  = 1000000;  break;
            case 7: digit[i]  = 10000000; break;
            default: break;
        }
    }

    do
    {
        value[0] = (float)(rand() % digit[0]);
        value[1] = (float)(rand() % digit[1]);
    }while(value[0] < 0 && value[1] < 0);

    for(int i = 0; i <= 1; i++)
    {
        switch (WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + MyTask->operand[count])))
        {
            case 0: value[i] *= 1;       break;
            case 1: value[i] *= 0.1;     break;
            case 2: value[i] *= 0.01;    break;
            case 3: value[i] *= 0.001;   break;
            case 4: value[i] *= 0.0001;  break;
            case 5: value[i] *= 0.00001; break;
            default: break;
        }
    }

    solution[1] = WCO_Worksheet_Task_Calculate(MyTask, &count, &value[0], &value[1]);

    switch(WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + MyTask->operand[count])))
    {
        case 0: sprintf(MyTask->task[0][count], "%d %c %d =", (int)value[0], ops[MyTask->operand[count]], (int)value[1]); break;
        case 1: sprintf(MyTask->task[0][count], "%.1f %c %.1f =", value[0], ops[MyTask->operand[count]], value[1]); break;
        case 2: sprintf(MyTask->task[0][count], "%.2f %c %.2f =", value[0], ops[MyTask->operand[count]], value[1]); break;
        case 3: sprintf(MyTask->task[0][count], "%.3f %c %.3f =", value[0], ops[MyTask->operand[count]], value[1]); break;
        case 4: sprintf(MyTask->task[0][count], "%.4f %c %.4f =", value[0], ops[MyTask->operand[count]], value[1]); break;
        case 5: sprintf(MyTask->task[0][count], "%.5f %c %.5f =", value[0], ops[MyTask->operand[count]], value[1]); break;
        default: break;
    }

    switch(WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + MyTask->operand[count])))
    {
        case 0: sprintf(MyTask->task[1][count], "%d %c %d = %.2f", (int)value[0], ops[MyTask->operand[count]], (int)value[1], solution[1]); break;
        case 1: sprintf(MyTask->task[1][count], "%.1f %c %.1f = %.2f", value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 2: sprintf(MyTask->task[1][count], "%.2f %c %.2f = %.2f", value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 3: sprintf(MyTask->task[1][count], "%.3f %c %.3f = %.2f", value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 4: sprintf(MyTask->task[1][count], "%.4f %c %.4f = %.2f", value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 5: sprintf(MyTask->task[1][count], "%.5f %c %.5f = %.2f", value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        default: break;
    }
}

float WCO_Worksheet_Task_Calculate(MyTask_t *MyTask, int *count, float *a, float *b)
{
    float ret; 

    switch (MyTask->operand[*count])
    {
        case 0: ret = (*a) + (*b); break;
        case 1: ret = (*a) - (*b); break;
        case 2: ret = (*a) * (*b); break;
        case 3: ret = (*a) / (*b); break;
        default: break;
    }

    return ret;
}

void WCO_Worksheet_Task_Draw(MyTask_t *MyTask, int *x, int *y, int count, int page)
{
    WCO_PDF_WriteText(*x, *y, MyTask->task[page][count], page);
    if (page == _Tasks) WCO_PDF_DrawSolutionLine(MyTask->task[page][count], *x, *y, 60, page);
}