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
#include <MagickWand/MagickWand.h>

/*
*   This function initalices some requirements to display the pdf
*/
void WCO_PNG_Init()
{
    //store a fix path where the png is stored every time
    sprintf(MyPNG.folderName,"/home/maximilian/WCO/Bild/");

    //store the two images to the fix folderpath 
    sprintf(MyPNG.fileName[0], "%sTask.png", MyPNG.folderName);
    sprintf(MyPNG.fileName[1], "%sSolution.png", MyPNG.folderName);
}

/*
*   This function converts the pdf to an png using an installed converter on the system via the system command
*/
void WCO_PNG_Set_ConvertToPNG(float resize)
{
    //resizing the pdf by an given factor and casting it to an int
    int x = (int)(resize * MyPDF.pageSize[0]);
    int y = (int)(resize * MyPDF.pageSize[1]);

    //converting both pages. The task and the solution sheet via a for loop
    for(int i = 0; i <= 1; i++)
    {
        //making the command to convert the pdf 
        //sprintf(MyPNG.convertCommand, "convert -density 300 %s -resize %dx%d -quality 100 -colorspace RGB %s", MyPDF.fileName[i], x, y, MyPNG.fileName[i]);
        
        //printing the command for debuging
        //printf("%s\n", MyPNG.convertCommand);

        //executing the command in the command line
        //system(MyPNG.convertCommand);

        MagickWand *newWand;

        MagickWandGenesis();

        newWand = NewMagickWand();

        MagickReadImage(newWand, MyPDF.fileName[i] );

        MagickResizeImage(newWand,x,y,LanczosFilter);

        MagickSetImageCompressionQuality(newWand,100);

        MagickWriteImage(newWand, MyPNG.fileName[i]);

        if(newWand) DestroyMagickWand(newWand);

        void MagickWandTerminus(void);

        //displaying the converted pdf in the gtk window
        WCO_GUI_Show_Worksheet(i);
    }

    //Set the PNGShowFlag 
    //This is only done once. After that the flag is always set
    WCO_GUI_Status_Set_ShowPNG();
}

/*
*   this function returns a pointer to the file name depanding on the page
*/
char *WCO_PNG_Get_FileName(int page)
{
    //creating a pointer
    char *file;

    //write the adress of the filename into the pointer
    file = MyPNG.fileName[page];

    //return the adress
    return file;
}