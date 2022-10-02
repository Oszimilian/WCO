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

void WCO_Worksheet_Get_Rand_List(int range)
{
    

    for (int j = 0; j <= range; j++)
    {
        WCO_Rand_Ref()->rand_list[j] = range + 1;
    }

    srand(time(NULL));
    int value;
    int check;


    for (int i = 0; i <= (range); i++)
    {
        check = _TRUE;
        value = rand() % range;
        while(_TRUE)
        { 
            check = _TRUE;

            for (int k = 0; k <= i; k++)
            {
                if (value == WCO_Rand_Ref()->rand_list[k])
                {
                    check = _FALSE;

                } 
            }
            if (check)
            {
                break;
            }else{
                if (value < range) value++;
                else value = 0;
            }
        }
        WCO_Rand_Ref()->rand_list[i] = value;
    }
}

