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
#include "GUI_Status.h"
#include "GUI_Update.h"
#include "GUI.h"
#include "PDF.h"
#include "PNG.h"
#include "Worksheet_Baseboard.h"
#include "Worksheet_Creat_Fraction.h"
#include "Worksheet_Creat_Task.h"
#include "Worksheet_Rand.h"
#include "main.h"


typedef struct
{
    MyGUI_t *MyGUI_r;
    MyPDF_t *MyPDF_r;
    MyPNG_t *MyPNG_r;
    MyBase_t *MyBase_r;
    MyRand_t *MyRand_r;
}MyExchange_t;
MyExchange_t MyExchange;

void WCO_Exchange_Init()
{
    MyGUI_t *MyGUI = malloc(sizeof(MyGUI_t));
    MyPDF_t *MyPDF = malloc(sizeof(MyPDF_t));
    MyPNG_t *MyPNG = malloc(sizeof(MyPNG_t));
    MyBase_t *MyBase = malloc(sizeof(MyBase_t));
    MyRand_t *MyRand = malloc(sizeof(MyRand_t));

    MyExchange.MyGUI_r = MyGUI;
    MyExchange.MyPDF_r = MyPDF;
    MyExchange.MyPNG_r = MyPNG;
    MyExchange.MyBase_r = MyBase;
    MyExchange.MyRand_r = MyRand;
}

MyGUI_t *WCO_GUI_Ref()
{
    return MyExchange.MyGUI_r;
} 
MyPDF_t *WCO_PDF_Ref()
{
    return MyExchange.MyPDF_r;
}
MyPNG_t *WCO_PNG_Ref()
{
    return MyExchange.MyPNG_r;
}
MyBase_t *WCO_Baseboard_Ref()
{
    return MyExchange.MyBase_r;
}

MyRand_t *WCO_Rand_Ref()
{
    return MyExchange.MyRand_r;
}

char dirSyntaxHelper()
{
    return (OP == Linux) ? '/' : '\\';
}

int main(void)
{
    if (OP == 1) printf("OP: Linux \n\n");
    else printf("OP: Windows \n\n");
    //Init
    WCO_Exchange_Init();


    WCO_PNG_Init();
    WCO_Worksheet_Baseboard_Init();
    

    WCO_GUI_Start();



    return EXIT_SUCCESS;
}




