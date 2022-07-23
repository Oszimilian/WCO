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
    if (!MyPDF.pdf)
    {
        printf ("ERROR: cannot create pdf object.\n");
        return 1;
    }

    if (setjmp(env))
    {
        HPDF_Free (MyPDF.pdf);
        return 1;
    }

    return 0;
}

/*
*   Generates a new slide of a pdf or in case of previous called HPDF_NewDoc function it will generate a new pdf
*/
void WCO_PDF_SetupPage(int page)
{
    MyPDF.page[page] = HPDF_AddPage(MyPDF.pdf);
    HPDF_Font font = HPDF_GetFont(MyPDF.pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(MyPDF.page[page], font, 14);
}

/*
*   Set the name of the Folder-Tree
*/
void WCO_PDF_SetFoldername(char *folderName)
{
    sprintf(MyPDF.folderName, "%s", folderName);
}

/*
*   Set the filename for task and solution pdf global
*/
void WCO_PDF_SetFilename(char *fileName, int page)
{
    if (page == 0)
    {
        sprintf(MyPDF.fileName[page], "%s.pdf", fileName);
    }else{
        sprintf(MyPDF.fileName[page], "Lösungen.pdf");
    }

    sprintf(MyPDF.systemOpenFile[page], "okular %s%s", MyPDF.folderName, MyPDF.fileName[page]);

    printf("PDF Path: %s\n", MyPDF.systemOpenFile[page]);
}

/*
*   Writes some text on the pdf
*/
void WCO_PDF_WriteText(int x, int y, char *text, int page)
{
    HPDF_Page_BeginText(MyPDF.page[page]);
    HPDF_Page_TextOut(MyPDF.page[page], x, y, text);
    HPDF_Page_EndText(MyPDF.page[page]);
}

/*
*   Saves the pdf // it is nesecarely to hand the full file name over .pdf
*/
void WCO_PDF_SavePDF(int page)
{
    HPDF_SaveToFile(MyPDF.pdf, MyPDF.fileName[page]);
    printf("PDF Save: %s\n", MyPDF.fileName[page]);
}


/*
*   This function draws a line after every math-task to note down the handwritten answer
*/
void WCO_PDF_DrawSolutionLine(char *text, int x1, int y1, int line_Lengh, int page)
{
    int task_lengh = strlen(text) + 1;
    int pattern_lengh = 6;
    int x2 = x1;
    int y2 = y1;

    x1 = x1 + (task_lengh * pattern_lengh);
    x2 = x2 + (task_lengh * pattern_lengh) + line_Lengh;

    HPDF_Page_MoveTo(MyPDF.page[page], x1, y1);
    HPDF_Page_LineTo(MyPDF.page[page], x2, y2);
    HPDF_Page_Stroke(MyPDF.page[page]);
}

/*
*   This function draws a line from point a to b
*/
void WCO_PDF_DrawLine(int x1, int y1, int x2, int y2, int page)
{
    HPDF_Page_MoveTo(MyPDF.page[page], x1, y1);
    HPDF_Page_LineTo(MyPDF.page[page], x2, y2);
    HPDF_Page_Stroke(MyPDF.page[page]);
}



