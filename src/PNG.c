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
#include <dirent.h>

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
*   This function initalices some requirements to display the pdf
*/
void WCO_PNG_Init()
{

    DIR *folder;
    struct dirent *entry;
    int files = 0;
    int folder_flag = _FALSE;

    folder = opendir(".");
    if (folder == NULL)
    {
        printf("unable to read the folder \n");
        goto failed;
    }

    while( (entry = readdir(folder)) )
    {
        //printf("File/Folder %d: %s ->%d\n", files, entry->d_name, strlen(entry->d_name));

                

        if (strcmp("png", entry->d_name) && !folder_flag)
        {
            folder_flag = _TRUE;
            //printf("%s \n", entry->d_name);
            system("mkdir png");
            //goto detact_folder;

        }

        if (strcmp("png", entry->d_name)) break;
    }


    closedir(folder);

    failed:

    sprintf(WCO_PNG_Ref()->folderName, "%s/%s/",getcwd(NULL, 0), "png");
    printf("Current Folder: %s \n", getcwd(NULL, 0));
    printf("PNG_Folder: %s \n", WCO_PNG_Ref()->folderName);

    //store the two images to the fix folderpath 
    sprintf(WCO_PNG_Ref()->fileName[0], "%sTask.png", WCO_PNG_Ref()->folderName);
    sprintf(WCO_PNG_Ref()->fileName[1], "%sSolution.png", WCO_PNG_Ref()->folderName);

    int i = _FALSE;
    WCO_PNG_Set(&i, set_showPNG);
}

/*
*   This function converts the pdf to an png using an installed converter on the system via the system command
*/
void WCO_PNG_Set_ConvertToPNG(float resize)
{
    //resizing the pdf by an given factor and casting it to an int
    int x = (int)(resize * WCO_PDF_Ref()->pageSize[0]);
    int y = (int)(resize * WCO_PDF_Ref()->pageSize[1]);

    //converting both pages. The task and the solution sheet via a for loop
    for(int i = 0; i <= 1; i++)
    {

        MagickWand *newWand;

        MagickWandGenesis();

        newWand = NewMagickWand();

        MagickReadImage(newWand, WCO_PDF_Ref()->fileName[i] );

        MagickResizeImage(newWand,x,y,LanczosFilter);

        MagickContrastImage(newWand, 100);

        MagickSetImageCompressionQuality(newWand,100);

        MagickWriteImage(newWand, WCO_PNG_Ref()->fileName[i]);

        if(newWand) DestroyMagickWand(newWand);

        void MagickWandTerminus(void);

        //displaying the converted pdf in the gtk window
        WCO_GUI_Show_Worksheet(i);
    }

    //Set the PNGShowFlag 
    //This is only done once. After that the flag is always set
    int i = _TRUE;
    WCO_PNG_Set(&i, set_showPNG);
}

/*
*   this function returns a pointer to the file name depanding on the page
*/
char *WCO_PNG_Get_FileName(int page)
{
    //creating a pointer
    char *file;

    //write the adress of the filename into the pointer
    file = WCO_PNG_Ref()->fileName[page];

    //return the adress
    return file;
}

void *WCO_PNG_Get(int verify)
{
    void *ret = NULL;

    switch (verify)
    {
        case get_showPNG: ret = &WCO_PNG_Ref()->showPNG;
        default: break;
    }

    return ret;
}

void WCO_PNG_Set(void *input, int verify)
{
    switch(verify)
    {
        case set_showPNG: WCO_PNG_Ref()->showPNG = *(int*)input; break;
        default: break;
    }
}