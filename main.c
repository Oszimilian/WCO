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



int main(void)
{

    WCO_PNG_Init();
    WCO_Worksheet_Baseboard_Init();
    

    WCO_GUI_Start();



    return EXIT_SUCCESS;
}




