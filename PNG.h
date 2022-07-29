struct PNG_t
{
    char convertCommand[300];
    char fileName[2][200];
    char folderName[100];
}MyPNG;


void WCO_PNG_Init();
void WCO_PNG_Set_ConvertToPNG(float resize);
char *WCO_PNG_Get_FileName(int page);