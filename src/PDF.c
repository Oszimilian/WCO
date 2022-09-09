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

/*
*   This function is a official error handler
*   Error-codes can be found on the git-hub-repo
*/
void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%d\n", (unsigned int) error_no, (int) detail_no);
    longjmp (env, 1); /* invoke longjmp() on error */
}

/*
*   This function checks if pointer to the pdf-doc-struct is avalible
*/
int WCO_PDF_Check()
{
    if (!WCO_PDF_Ref()->pdf)
    {
        printf ("ERROR: cannot create pdf object.\n");
        return 1;
    }

    if (setjmp(env))
    {
        HPDF_Free (WCO_PDF_Ref()->pdf);
        return 1;
    }

    return 0;
}

/*
*   Generates a new slide of a pdf or in case of previous called HPDF_NewDoc function it will generate a new pdf
*/
void WCO_PDF_SetupPage(int page)
{
    WCO_PDF_Ref()->page[page] = HPDF_AddPage(WCO_PDF_Ref()->pdf);
    HPDF_Font font = HPDF_GetFont(WCO_PDF_Ref()->pdf, "Courier", NULL);
    HPDF_Page_SetFontAndSize(WCO_PDF_Ref()->page[page], font, 14);

    WCO_PDF_Ref()->pageSize[0] = 2479;
    WCO_PDF_Ref()->pageSize[1] = 3504; 
}

/*
*   Set the name of the Folder-Tree
*/
void WCO_PDF_SetFoldername(char *folderName)
{
    sprintf(WCO_PDF_Ref()->folderName, "%s", folderName);
}

/*
*   Set the filename for task and solution pdf global
*/
void WCO_PDF_SetFilename(const char *fileName, int page)
{
    if (page == 0)
    {
        sprintf(WCO_PDF_Ref()->fileName[page], "%s/%s.pdf", WCO_PDF_Ref()->folderName, fileName);
    }else{
        sprintf(WCO_PDF_Ref()->fileName[page], "%s/%s_Lösungen.pdf", WCO_PDF_Ref()->folderName, fileName);
    }

    sprintf(WCO_PDF_Ref()->systemOpenFile[page], "okular %s", WCO_PDF_Ref()->fileName[page]);

    printf("PDF Path: %s\n", WCO_PDF_Ref()->fileName[page]);
}

/*
*   Writes some text on the pdf
*/
void WCO_PDF_WriteText(int x, int y, char *text, int page)
{
    HPDF_Page_BeginText(WCO_PDF_Ref()->page[page]);
    HPDF_Page_TextOut(WCO_PDF_Ref()->page[page], x, y, text);
    HPDF_Page_EndText(WCO_PDF_Ref()->page[page]);
}

/*
*   Saves the pdf // it is nesecarely to hand the full file name over .pdf
*/
void WCO_PDF_SavePDF(int page)
{
    HPDF_SaveToFile(WCO_PDF_Ref()->pdf, WCO_PDF_Ref()->fileName[page]);
    printf("PDF Save: %s\n", WCO_PDF_Ref()->fileName[page]);
}


/*
*   This function draws a line after every math-task to note down the handwritten answer
*/
void WCO_PDF_DrawSolutionLine(char *text, int x1, int y1, int line_Lengh, int page)
{
    int task_lengh = strlen(text) + 1;
    const int pattern_lengh = 8;
    int x2 = x1;
    int y2 = y1;

    x1 = x1 + (task_lengh * pattern_lengh);
    x2 = x2 + (task_lengh * pattern_lengh) + line_Lengh;

    HPDF_Page_MoveTo(WCO_PDF_Ref()->page[page], x1, y1);
    HPDF_Page_LineTo(WCO_PDF_Ref()->page[page], x2, y2);
    HPDF_Page_Stroke(WCO_PDF_Ref()->page[page]);
}

/*
*   This function draws a line from point a to b
*/
void WCO_PDF_DrawLine(int x1, int y1, int x2, int y2, int page)
{
    HPDF_Page_MoveTo(WCO_PDF_Ref()->page[page], x1, y1);
    HPDF_Page_LineTo(WCO_PDF_Ref()->page[page], x2, y2);
    HPDF_Page_Stroke(WCO_PDF_Ref()->page[page]);
}







