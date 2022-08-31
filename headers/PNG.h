#ifndef PNG_H_INCLUDED
#define PNG_H_INCLUDED

typedef struct{
    char convertCommand[300];
    char fileName[2][200];
    char folderName[100];
    int showPNG;
}MyPNG_t;



enum PNG_Gets{
    get_showPNG,
    set_showPNG,
};


void WCO_PNG_Init();
void WCO_PNG_Set_ConvertToPNG(float resize);
char *WCO_PNG_Get_FileName(int page);
void *WCO_PNG_Get(int verify);
void WCO_PNG_Set(void *input, int verify);

#endif