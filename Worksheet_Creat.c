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

/*
*   function initializes the variables in the worksheet struct
*/
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
    //init a lokal return var which is presset to a success value
    int ret = _succeded;

    //initialise a pdf instanze
    MyPDF.pdf = HPDF_New (Error_Handler, NULL);

    //Check if the pdf instanze already exist or something goes wrong
    if (WCO_PDF_Check())
    {
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");

        //setting the lokal return var to an error value
        ret = _error;

        //if a failure occurs the programm jumps with the goto instruction to the end of this function end returns a error
        goto failed;
    }else{
        //everything works fine
        printf("PDF wurde erfolgreich erzeugt \n");
    }

    //Generating a new page zero in a array
    WCO_PDF_SetupPage(_Tasks);

    //Generating the task sheet
    if (!WCO_Worksheet_Creat_TaskSheet())
    {
        //if a error okurs this ret var is set to error
        ret = _error;

        //end the programm jumps to the end of this function
        goto failed;
    }


    //Save pdf and show it witch okular viewer
    WCO_PDF_SavePDF(_Tasks);

    //Neue PDF wird erzeugt
    HPDF_NewDoc(MyPDF.pdf);

    //Generatign a new pdf
    WCO_PDF_SetupPage(_Solutions);



    //generating a new solution task sheed
    if (!WCO_Worksheet_Create_SolutionSheed())
    {
        //if a error occurs the local return var is set to an error value
        ret = _error;

        //and the programm will be skiped to the and of this function
        goto failed;
    }

    //Saves the Solution - PDF
    WCO_PDF_SavePDF(_Solutions);

    //ends the hole progress with generating a pdf
    HPDF_Free(MyPDF.pdf);

    //converts the PDF into an png
    WCO_PNG_Set_ConvertToPNG(0.3);

    //goto flag 
    failed:

    return ret;
}

/*
*   Creats a sheed with the asked solutions
*/
int WCO_Worksheet_Creat_TaskSheet()
{   
    //inti a lokal return value and set it to a success value
    int ret = _succeded;

    //var to store the height of the sheed
    int pageSize;
    
    //var which is declared and initialized with the pageSize to manage the position of each task
    int pageSizeCounter;

    //counter to store the amount of task of each sheed
    int taskCounter = 0;

    //Array which includes the 3 x start points of each "spalte"
    int startx[3];
    //The "spalten" are positionate at 30, 60, 90 percent of the page leangh
    startx[0] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.6);
    startx[2] = HPDF_Page_GetWidth(MyPDF.page[_Tasks]) - (HPDF_Page_GetWidth(MyPDF.page[_Tasks]) * 0.3);

    //printing a baseboard at the top of the sheed where the pupils can write there names down
    if(!WCO_Worksheet_Creat_Baseboard(_Tasks))
    {
        //error handling
        ret = _error;

        //jump to the end of the function
        goto failed;
    }

    //if the user whished a baseboard this will need extraspace 
    //to avoid that tasks are printet over the baseboard the pageSize is modified by a certain threashold
    if (WCO_Worksheet_Status_Baseboard())
    {
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Tasks]) - WCO_Worksheet_Status_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Tasks]);
    }

    //to generate random numbers the generator uses the time functions
    srand(time(NULL));

    //start a loop which counts untill 3, which stands for the 3 "Spalten"
    for(int i = 0; i <= 2; i++)
    {
        //at the beginning of each "Spalten" the pageSizeCounter is set to the fix value of pageSize
        pageSizeCounter = pageSize;

        //this while loop be execute untill the value of the pageSizeCounter is lower or equal to 50
        //if this happens a new "Spalte" will be started
        while(pageSizeCounter >= 50)
        {
            //this function creats a random generated task and stores the task in the MyWorksheed sturct in a array
            if (!WCO_Worksheet_Create_RandomTask(taskCounter))
            {
                //errorhandling
                ret = _error;

                goto failed;
            } 

            //this function returns a pointer to the array in the MyWorksheed sturct 
            char *task = WCO_Worksheet_Status_Task(taskCounter, _Tasks);

            //this fuction prints the task on the pdf-sheet
            WCO_PDF_WriteText(startx[i], pageSizeCounter, task, _Tasks);

            //Behind every math-task this function prints a solution line 
            WCO_PDF_DrawSolutionLine(task, startx[i], pageSizeCounter, 60, _Tasks);

            //All task in a "spalte" are printed below the others so the new starting point is 50 points under the previous
            pageSizeCounter -= 50;

            //increment the taskCounter after every task
            taskCounter ++;
        }
    }

    //error handling in this function
    failed:

    return ret;
}

/*
*   Creas a sheed with the solutions
*/
int WCO_Worksheet_Create_SolutionSheed()
{   
    //local return value with preset success
    int ret = _succeded;

    //var to store the height of the sheed
    int pageSize;

    //var which is declared and initialized with the pageSize to manage the position of each task
    int pageSizeCounter;

    //counter to store the amount of task of each sheed
    int taskCounter = 0;

    //Array which includes the 3 x start points of each "spalte"
    int startx[3];
    //The "spalten" are positionate at 30, 60, 90 percent of the page leangh
    startx[0] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.9);
    startx[1] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.6);
    startx[2] = HPDF_Page_GetWidth(MyPDF.page[_Solutions]) - (HPDF_Page_GetWidth(MyPDF.page[_Solutions]) * 0.3);

    //printing a baseboard at the top of the sheed where the pupils can write there names down
    if (!WCO_Worksheet_Creat_Baseboard(_Solutions))
    {
        //error handling
        ret = _error;

        goto failed;
    }

    //if the user whished a baseboard this will need extraspace 
    //to avoid that tasks are printet over the baseboard the pageSize is modified by a certain threashold
    if (WCO_Worksheet_Status_Baseboard())
    {
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Solutions]) - WCO_Worksheet_Status_Threashold();
    }else{
        pageSize = HPDF_Page_GetHeight(MyPDF.page[_Solutions]);
    }

    //start a loop which counts untill 3, which stands for the 3 "Spalten"
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

        if (!WCO_GUI_Status_Get_AllOperand_CheckButtons())
        {
            gtk_label_set_text(MyGUI.MyLabel1, "Sie müssen auf jeden Fall einen Operator auswählen!");
            
            ret = _error;

            goto fail;
        }
    
        if (WCO_GUI_Status_Get_SpecificOperand_CheckButton(operand)) break;
    }

    /*
    *   This part
    */
    spinButtonValue[0] = WCO_GUI_Status_Get_SpecificOperandDigitRange_spinButton(operand, 0);
    spinButtonValue[1] = WCO_GUI_Status_Get_SpecificOperandDigitRange_spinButton(operand, 1);

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
   decimalPlaces = WCO_GUI_Status_Get_SpecificOperandDecimalPlaces_SpinButton(operand);

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