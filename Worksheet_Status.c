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

/*
*   This function returns the value of the printBaseboard flag which is responsible for printing a baseboard or not
*/
int WCO_Worksheet_Status_Baseboard()
{
    return MyWorksheet.printBaseboard;
}

/*
*   set or reset the Baseboard flag
*/
void WCO_Worksheet_Status_Config_Baseboard(int i)
{
    if (i) 
    {
        MyWorksheet.printBaseboard = _enable;
    }else{
        MyWorksheet.printBaseboard = _disable;
    }
}

/*
*   This function returns the Threashold value
*/
int WCO_Worksheet_Status_Threashold()
{
    return MyWorksheet.baseboardThreashold;
}

/*
*   this function caluclates the generated task
*/
float WCO_Worksheet_Status_Calculation(int operand, float *a, float *b)
{
    float ret; 

    switch (operand)
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
*   this function returns the adress to the solution string or the task
*/
char* WCO_Worksheet_Status_Task(int number, int page)
{
    char *tmp;
    tmp = MyWorksheet.task[page][number];
    return tmp;
}

/*
*   This function return the date 
*   The string can be modified by attaching a string to the front such as "Datum"
*/
char* WCO_Worksheet_Status_GetDate(char *str)
{
    //declarate a new instance of the time struct
    time_t now;

    //telling the time function the adress of the time struct
    time(&now);

    //declarate a new struct which hold the time datas
    struct tm *tm_instance;

    //initializing the struct 
    tm_instance = localtime(&now);

    //generating dynamic space for the return string and store the adress in the tmp pointer
    char *tmp = malloc(100);

    //store the date in a readable
    sprintf(tmp, "%s %d.%d.%d", str, tm_instance->tm_mday, tm_instance->tm_mon + 1, tm_instance->tm_year + 1900);

    //return the adress of this string
    return tmp;
}

