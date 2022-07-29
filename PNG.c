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

void WCO_PNG_Init()
{
    sprintf(MyPNG.folderName,"/home/maximilian/NewGit/WCO/Bild/");
    sprintf(MyPNG.fileName[0], "%sTask.png", MyPNG.folderName);
    sprintf(MyPNG.fileName[1], "%sSolution.png", MyPNG.folderName);
}

void WCO_PNG_Set_ConvertToPNG(float resize)
{
    int x = (int)(resize * MyPDF.pageSize[0]);
    int y = (int)(resize * MyPDF.pageSize[1]);

    for(int i = 0; i <= 1; i++)
    {
        sprintf(MyPNG.convertCommand, "convert -density 300 %s -resize %dx%d -quality 100 -colorspace RGB %s", MyPDF.fileName[i], x, y, MyPNG.fileName[i]);
        printf("%s\n", MyPNG.convertCommand);
        system(MyPNG.convertCommand);
        WCO_GUI_Show_Worksheet(i);
    }

}


char *WCO_PNG_Get_FileName(int page)
{
    char *file;
    file = MyPNG.fileName[page];
    return file;
}