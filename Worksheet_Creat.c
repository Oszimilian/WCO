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

void WCO_Worksheet_Init()
{
    MyWorksheet.printBaseboard = _enable;
    MyWorksheet.baseboardThreashold = 150;
}

/*
*   This Funktion starts the process of generating a math-task-pdf from the beginning till the end
*/
int WCO_Worksheet_Create_Start()
{
    int ret = _succeded;

    //initialise a pdf instanze
    MyPDF.pdf = HPDF_New (Error_Handler, NULL);

    //Check this pdf instanze
    if (WCO_PDF_Check())
    {
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");

        goto failed;
    }else{
        printf("PDF wurde erfolgreich erzeugt \n");
    }

    //Generating a new page zero
    WCO_PDF_SetupPage(_Tasks);

    

    //Wirte some text
    if (!WCO_Worksheet_Creat_TaskSheet())
    {
        ret = _error;

        goto failed;
    }


    //Save pdf and show it witch okular viewer
    WCO_PDF_SavePDF(_Tasks);

    //Neue PDF wird erzeugt
    HPDF_NewDoc(MyPDF.pdf);

    //Generatign a new pdf
    WCO_PDF_SetupPage(_Solutions);



    //Creates a Solution  - PDF
    if (!WCO_Worksheet_Create_SolutionSheed())
    {
        ret = _error;

        goto failed;
    }

    //Saves the Solution - PDF
    WCO_PDF_SavePDF(_Solutions);

    //ends the hole progress with generating a pdf
    HPDF_Free(MyPDF.pdf);

    failed:

    return ret;
}

/*
*   Creats a sheed with the asked solutions
*/
int WCO_Worksheet_Creat_TaskSheet()
{
    int ret = _succeded;

    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[3];
    startx[0] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.6);
    startx[2] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.3);

    //print a baseboard
    if(!WCO_Worksheet_Creat_Baseboard(_Tasks))
    {
        ret = _error;

        goto failed;
    }

    if (WCO_Worksheet_Status_Baseboard())
    {
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Tasks]) - WCO_Worksheet_Status_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Tasks]);
    }


    srand(time(NULL));

    for(int i = 0; i <= 2; i++)
    {
        pageSizeCounter = pageSize;

        while(pageSizeCounter >= 50)
        {

            if (!WCO_Worksheet_Create_RandomTask(taskCounter))
            {
                ret = _error;

                goto failed;
            } 

            char *task = WCO_Worksheet_Status_Task(taskCounter, _Tasks);

            WCO_PDF_WriteText(startx[i], pageSizeCounter, task, _Tasks);

            WCO_PDF_DrawSolutionLine(task, startx[i], pageSizeCounter, 60, _Tasks);

            pageSizeCounter -= 50;

            taskCounter ++;

        }

    }

    failed:

    return ret;
}

/*
*   Creas a sheed with the solutions
*/
int WCO_Worksheet_Create_SolutionSheed()
{   
    int ret = _succeded;

    int pageSize;
    int pageSizeCounter;
    int taskCounter = 0;
    int startx[3];
    startx[0] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.6);
    startx[2] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.3);

    //print a baseboard
    if (!WCO_Worksheet_Creat_Baseboard(_Solutions))
    {
        ret = _error;

        goto failed;
    }

    if (WCO_Worksheet_Status_Baseboard())
    {
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Solutions]) - WCO_Worksheet_Status_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Solutions]);
    }

     for(int i = 0; i <= 2; i++)
    {
        pageSizeCounter = pageSize;

        while(pageSizeCounter >= 50)
        {
            char *task = WCO_Worksheet_Status_Task(taskCounter, _Solutions);

            WCO_PDF_WriteText(startx[i], pageSizeCounter, task, _Solutions);

            pageSizeCounter -= 50;

            taskCounter ++;

        }

    }

    failed:

    return ret;
}


/*
*   This function creats random math task and writes it into a struct defined string
*/
int WCO_Worksheet_Create_RandomTask(int counter)
{

    int ret = _succeded;

    int operand;
    int termLeangh[2];
    int spinButtonValue[2];
    float value[2];
    int decimalPlaces;
    char taskOperand[] = {'+', '-', '*', '/'};
    float solution;


    /*
    *   Generate a operand
    *   If All OperandFlags are false this while-loop will be skipped
    *   If one, two, or three Operand Flags are false this will-loop will generate random typs of operands untill a not denied one appears
    */
    while(1)
    {
        operand = rand() % 4;

        if (!WCO_GUI_Status_AllOperant_CheckButtons())
        {
            gtk_label_set_text(MyGUI.MyLabel1, "Sie müssen auf jeden Fall einen Operator auswählen!");
            
            ret = _error;

            goto fail;
        }
    
        if (WCO_GUI_Status_SpecificOperand_CheckButton(operand)) break;
    }

    /*
    *   This part
    */
    spinButtonValue[0] = WCO_GUI_Status_SpecificOperand_SpinButton(operand, 0);
    spinButtonValue[1] = WCO_GUI_Status_SpecificOperand_SpinButton(operand, 1);

    for (int i = 0; i <= 1; i++)
    {
        switch (spinButtonValue[i])
        {
        case 1: termLeangh[i]  = 10; break;
        case 2: termLeangh[i]  = 100; break;
        case 3: termLeangh[i]  = 1000; break;
        case 4: termLeangh[i]  = 10000; break;
        case 5: termLeangh[i]  = 100000; break;
        default: break;
        }
    }

    /*
    *   This part generates random numbers until the generated number is higher than zero
    *   Secondly the int number is casted into float datatyp
    */
    do
    {
        value[0] = (float)(rand() % termLeangh[0]);
        value[1] = (float)(rand() % termLeangh[1]);
    }while(value[0] < 0 && value[1] < 0);


    /*
    *   stores the DecimalPlaces dependent of the operand into a local var "localDecimalPlaces"
    */
   decimalPlaces = WCO_GUI_Status_SpecificOperand_DecimalPlaces(operand);

    /*
    *   if the current DecimalPlaces count is zero the task is print as a integer
    *   Otherwise the task is print as a float with the demanded decimal place
    */
    switch(decimalPlaces)
    {
        case 0: value[0] *= 1;        value[1] *= 1;       break;
        case 1: value[0] *= 0.1;      value[1] *= 0.1;     break;
        case 2: value[0] *= 0.01;     value[1] *= 0.01;    break;
        case 3: value[0] *= 0.001;    value[1] *= 0.001;   break;
        case 4: value[0] *= 0.0001;   value[1] *= 0.0001;  break;
        case 5: value[0] *= 0.00001;  value[1] *= 0.00001; break;
        default: break;
    }

    solution = WCO_Worksheet_Status_Calculation(operand, &value[0], &value[1]);

    switch (decimalPlaces)
    {
        case 0:
            sprintf(MyWorksheet.task[0][counter], "%d %c %d =", (int)value[0], taskOperand[operand], (int)value[1]);
            sprintf(MyWorksheet.task[1][counter], "%d %c %d = %.2f", (int)value[0], taskOperand[operand], (int)value[1], solution);
        break;

        case 1:
            sprintf(MyWorksheet.task[0][counter], "%.1f %c %.1f =", value[0], taskOperand[operand], value[1]);
            sprintf(MyWorksheet.task[1][counter], "%.1f %c %.1f = %.2f", value[0], taskOperand[operand], value[1], solution);
        break;

        case 2:
            sprintf(MyWorksheet.task[0][counter], "%.2f %c %.2f =", value[0], taskOperand[operand], value[1]);
            sprintf(MyWorksheet.task[1][counter], "%.2f %c %.2f = %.2f", value[0], taskOperand[operand], value[1], solution);
        break;

        case 3:
            sprintf(MyWorksheet.task[0][counter], "%.3f %c %.3f =", value[0], taskOperand[operand], value[1]);
            sprintf(MyWorksheet.task[1][counter], "%.3f %c %.3f = %.2f", value[0], taskOperand[operand], value[1], solution);
        break;

        case 4:
            sprintf(MyWorksheet.task[0][counter], "%.4f %c %.4f =", value[0], taskOperand[operand], value[1]);
            sprintf(MyWorksheet.task[1][counter], "%.4f %c %.4f = %.2f", value[0], taskOperand[operand], value[1], solution);
        break;

        case 5:
            sprintf(MyWorksheet.task[0][counter], "%.5f %c %.5f =", value[0], taskOperand[operand], value[1]);
            sprintf(MyWorksheet.task[1][counter], "%.5f %c %.5f = %.2f", value[0], taskOperand[operand], value[1], solution);
        break;

        default: break;
    }

    //Jumpt to because a fail occures
    fail:

    return ret;
}



/*
*   This function creats a baseboard "Kopfzeile" with up to date date and the possibility to handwrite your name
*/
int WCO_Worksheet_Creat_Baseboard(int page)
{
    int ret = _succeded;

    //Jump into if the Baseboard Checkbutton is set
    if (WCO_Worksheet_Status_Baseboard())
    {
        //Divide the page into three colums
        int startx1 = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.9);
        int startx2 = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.5);
        int startx3 = HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.3);

        //Print a name field
        WCO_PDF_WriteText(startx1, 775, "Name:", page);
        WCO_PDF_DrawSolutionLine("Name:  ", startx1, 770, 150, page);

        //Depandent on the type of sheet two different strings will print
        if(page == _Tasks)
        {
            WCO_PDF_WriteText(startx2, 775, "AUFGABEN", page);
        }else{
            WCO_PDF_WriteText(startx2, 775, "SOLUTION", page);
        }

        //print the date
        char *tmp = WCO_Worksheet_Status_GetDate("Datum: ");
        WCO_PDF_WriteText(startx3, 775, tmp, page);
        WCO_PDF_DrawLine(50, 750, HPDF_Page_GetWidth(MyPDF.page[page]) - 50, 750, page);
    }

    return ret;
}






