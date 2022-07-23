#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>a
#include <math.h>

#include "hpdf.h"
#include "GUI_Call.h"
#include "GUI.h"
#include "PDF.h"
#include "Worksheet.h"

int WCO_Worksheet_Status_Baseboard()
{
    return MyWorksheet.printBaseboard;
}

int WCO_Worksheet_Status_Threashold()
{
    return MyWorksheet.baseboardThreashold;
}

float *WCO_Worksheet_Status_Calculation(int operand, float *a, float *b)
{
    float *ret; 

    switch (operand)
    {
        case 0: (*ret) = (*a) + (*b); break;
        case 1: (*ret) = (*a) - (*b); break;
        case 2: (*ret) = (*a) * (*b); break;
        case 3: (*ret) = (*a) / (*b); break;
        default: break;
    }

    return ret;
}

char *WCO_Worksheet_Status_Task(int number, int page)
{
    char *tmp = malloc (50);
    sprintf(tmp, "%s" MyWorksheet.task[page][number]);
    return tmp;
}

char* WCO_Worksheet_Status_GetDate(char *str)
{
    time_t now;
    time(&now);
    struct tm *tm_instance;
    tm_instance = localtime(&now);
    char *tmp = malloc(100);
    sprintf(tmp, "%s %d.%d.%d", str, tm_instance->tm_mday, tm_instance->tm_mon + 1, tm_instance->tm_year + 1900);
    return tmp;
}
