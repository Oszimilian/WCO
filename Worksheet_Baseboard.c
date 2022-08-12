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
#include "Worksheet_Baseboard.h"

void WCO_Worksheet_Baseboard_Init()
{
    MyBase.threashold[0] = 150;
    MyBase.threashold[1] = 50;
}

void WCO_Worksheet_Baseboard_Update()
{
    MyBase.baseEnable = WCO_BUTTON(WCO_GUI_Get(base_baseboard));
    MyBase.dateEnable = WCO_BUTTON(WCO_GUI_Get(base_date));
    MyBase.nameEnable = WCO_BUTTON(WCO_GUI_Get(base_name));

    MyBase.textLen = strlen(WCO_ENTRY(WCO_GUI_Get(base_text)));
    sprintf(MyBase.text, "%s", WCO_ENTRY(WCO_GUI_Get(base_text)));
}

char* WCO_Worksheet_Baseboard_Date(char *str)
{
    time_t now;

    time(&now);

    struct tm *tm_instance;
 
    tm_instance = localtime(&now);

    char *tmp = malloc(100);

    sprintf(tmp, "%s %d.%d.%d", str, tm_instance->tm_mday, tm_instance->tm_mon + 1, tm_instance->tm_year + 1900);

    tmp = (char*) realloc(tmp, strlen(tmp));

    return tmp;
}


void WCO_Worksheet_Baseboard_Creat(int page)
{
    
    if (WCO_BUTTON(WCO_GUI_Get(base_baseboard)))
    {
        int startx[3];

        startx[0] = (int)(HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.9));
        startx[1] = (int)(HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.5));
        startx[2] = (int)(HPDF_Page_GetWidth(MyPDF.page[page]) - (HPDF_Page_GetWidth(MyPDF.page[page]) * 0.3));

        if(WCO_BUTTON(WCO_GUI_Get(base_name)))
        {
            WCO_PDF_WriteText(startx[0], 775, "Name:", page);
            WCO_PDF_DrawSolutionLine("Name:  ", startx[0], 770, 150, page);
        }

        if(strlen(WCO_ENTRY(WCO_GUI_Get(base_text))) >= 1)
        {
            WCO_PDF_WriteText(startx[1], 775, WCO_ENTRY(WCO_GUI_Get(base_text)), page);
        }

        if(WCO_BUTTON(WCO_GUI_Get(base_date)))
        {
            char *tmp = WCO_Worksheet_Baseboard_Date("Datum: ");
            WCO_PDF_WriteText(startx[2], 775, tmp, page);
            free(tmp);
        }

        WCO_PDF_DrawLine(50, 750, HPDF_Page_GetWidth(MyPDF.page[page]) - 50, 750, page);
    }
}

int *WCO_Worksheet_Baseboard_Threashold()
{
    return (WCO_BUTTON(WCO_GUI_Get(base_baseboard))) ? &MyBase.threashold[0] : &MyBase.threashold[1];
}