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
#include "GUI_Status.h"
#include "GUI_Update.h"
#include "GUI.h"
#include "PDF.h"
#include "PNG.h"
#include "Worksheet_Baseboard.h"
#include "Worksheet_Creat_Fraction.h"
#include "Worksheet_Creat_Task.h"
#include "Worksheet_Rand.h"
#include "main.h"

/*
*   This function actually builds the worksheets
*/
void WCO_Worksheet_Task_Start()
{
    MyTask_t *MyTask = WCO_Worksheet_Task_Init();

    WCO_PDF_Ref()->pdf = HPDF_New(Error_Handler, NULL);

    if (WCO_PDF_Check())
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    else
        printf("PDF wurde erfolgreich erzeugt \n");

    WCO_PDF_SetupPage(_Tasks);

    WCO_Worksheet_Task_Creat(MyTask, _Tasks);

    WCO_PDF_SavePDF(_Tasks);

    HPDF_NewDoc(WCO_PDF_Ref()->pdf);

    WCO_PDF_SetupPage(_Solutions);

    WCO_Worksheet_Task_Creat(MyTask, _Solutions);

    WCO_PDF_SavePDF(_Solutions);

    WCO_Worksheet_Task_Free(MyTask);

    WCO_PNG_Set_ConvertToPNG(0.23);
}

/*
*   This function creats space on the heap and returns a pointer to this storage space on which the worksheet is stored
*/
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

/*
*   This function sets up a default worksheet (only for developing)
*/
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
}



/*
*   This function frees the space in the heap of the worksheet struct
*/
void WCO_Worksheet_Task_Free(MyTask_t *MyTask)
{
    free(MyTask);
}

/*
*   This function creats the task sheet
*/
void WCO_Worksheet_Task_Creat(MyTask_t *MyTask, int page)
{
    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[2];

    startx[0] = HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) * 0.5);

    WCO_Worksheet_Baseboard_Creat(page);

    pageSize = HPDF_Page_GetHeight(WCO_PDF_Ref()->page[page]) - *WCO_Worksheet_Baseboard_Threashold();

    for(int i = 0; i <= 1; i++)
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

    if (WCO_BUTTON(WCO_GUI_Get(solution_advice)) && page == 0) WCO_Worksheet_Task_Suggestion(MyTask, taskCounter, page);

}

/*
*   This function creats random tasks and stores it in a string
*/
void WCO_Worksheet_Task_Random(MyTask_t *MyTask, int count)
{
    long int digit[2];
    float value[2];
    float solution[2];
    char ops[4] = "+-*:";

    char *enum_task = (char*) malloc(sizeof(char) * ((WCO_BUTTON(WCO_GUI_Get(task_enum)))? 6:1 ) );
    if (WCO_BUTTON(WCO_GUI_Get(task_enum)))
    {
        sprintf(enum_task, "(%d): ", (count + 1));
    }else{
        sprintf(enum_task, " ");
    }

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
            case 1:  digit[i]   = 10;          break;
            case 2:  digit[i]   = 100;         break;
            case 3:  digit[i]   = 1000;        break;
            case 4:  digit[i]   = 10000;       break;
            case 5:  digit[i]   = 100000;      break;
            case 6:  digit[i]   = 1000000;     break;
            case 7:  digit[i]   = 10000000;    break;
            case 8:  digit[i]   = 100000000;   break;
            case 9:  digit[i]   = 1000000000;  break;
            case 10: digit[i]   = 10000000000;  break;
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
            case 0:  value[i] *= 1;            break;
            case 1:  value[i] *= 0.1;          break;
            case 2:  value[i] *= 0.01;         break;
            case 3:  value[i] *= 0.001;        break;
            case 4:  value[i] *= 0.0001;       break;
            case 5:  value[i] *= 0.00001;      break;
            case 6:  value[i] *= 0.000001;     break;
            case 7:  value[i] *= 0.0000001;    break;
            case 8:  value[i] *= 0.00000001;   break;
            case 9:  value[i] *= 0.000000001;  break;
            case 10: value[i] *= 0.0000000001; break;
            default: break;
        }
    }

    solution[1] = WCO_Worksheet_Task_Calculate(MyTask, &count, &value[0], &value[1]);
    sprintf(MyTask->solutions[count], "%.2f", solution[1]);

    switch(WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + MyTask->operand[count])))
    {
        case 0: sprintf(MyTask->task[0][count], "%s%d %c %d =", enum_task, (int)value[0], ops[MyTask->operand[count]], (int)value[1]); break;
        case 1: sprintf(MyTask->task[0][count], "%s%.1f %c %.1f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 2: sprintf(MyTask->task[0][count], "%s%.2f %c %.2f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 3: sprintf(MyTask->task[0][count], "%s%.3f %c %.3f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 4: sprintf(MyTask->task[0][count], "%s%.4f %c %.4f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 5: sprintf(MyTask->task[0][count], "%s%.5f %c %.5f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 6: sprintf(MyTask->task[0][count], "%s%.6f %c %.6f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 7: sprintf(MyTask->task[0][count], "%s%.7f %c %.7f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 8: sprintf(MyTask->task[0][count], "%s%.8f %c %.8f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 9: sprintf(MyTask->task[0][count], "%s%.9f %c %.9f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;
        case 10: sprintf(MyTask->task[0][count], "%s%.10f %c %.10f =", enum_task, value[0], ops[MyTask->operand[count]], value[1]); break;

        default: break;
    }

    switch(WCO_BUTTON(WCO_GUI_Get(task_addition_dezcount + MyTask->operand[count])))
    {
        case 0: sprintf(MyTask->task[1][count], "%s%d %c %d = %.2f", enum_task, (int)value[0], ops[MyTask->operand[count]], (int)value[1], solution[1]); break;
        case 1: sprintf(MyTask->task[1][count], "%s%.1f %c %.1f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 2: sprintf(MyTask->task[1][count], "%s%.2f %c %.2f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 3: sprintf(MyTask->task[1][count], "%s%.3f %c %.3f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 4: sprintf(MyTask->task[1][count], "%s%.4f %c %.4f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 5: sprintf(MyTask->task[1][count], "%s%.5f %c %.5f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 6: sprintf(MyTask->task[1][count], "%s%.6f %c %.6f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 7: sprintf(MyTask->task[1][count], "%s%.7f %c %.7f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 8: sprintf(MyTask->task[1][count], "%s%.8f %c %.8f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 9: sprintf(MyTask->task[1][count], "%s%.9f %c %.9f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        case 10: sprintf(MyTask->task[1][count], "%s%.10f %c %.10f = %.2f", enum_task, value[0], ops[MyTask->operand[count]], value[1], solution[1]); break;
        default: break;
    }
}

/*
*   This function caluclates the function and returns the solution float
*/
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

/*
*   This functiion draws the task on the pdfSheet
*/
void WCO_Worksheet_Task_Draw(MyTask_t *MyTask, int *x, int *y, int count, int page)
{
    WCO_PDF_WriteText(*x, *y, MyTask->task[page][count], page);
    if (page == _Tasks) WCO_PDF_DrawSolutionLine(MyTask->task[page][count], *x, *y, 60, page);
}

void WCO_Worksheet_Task_Suggestion(MyTask_t *MyTask, int max_task, int page)
{
    HPDF_Font font = HPDF_GetFont(WCO_PDF_Ref()->pdf, "Courier", NULL);
    HPDF_Page_SetFontAndSize(WCO_PDF_Ref()->page[page], font, 8);

    const int caracterLen = 5;

    WCO_Worksheet_Get_Rand_List(max_task - 1);

    int x = 50;
    int y = 50;

    for(int i = 0; i <= (max_task - 1); i++)
    {
        WCO_PDF_WriteText(x, y, MyTask->solutions[WCO_Rand_Ref()->rand_list[i]], page);
    
        x += (int)(caracterLen * floatLen(strtof(MyTask->solutions[WCO_Rand_Ref()->rand_list[i]], NULL)));
        
        
        if (x >= (HPDF_Page_GetWidth(WCO_PDF_Ref()->page[page]) - 100))
        {
            x = 50;
            y -= 10;
        }
    } 
}