static struct MyBase_t{
    int baseEnable;
    int dateEnable;
    int nameEnable;
    char text[50];
    int textLen;
    int threashold[2];
}MyBase;

void WCO_Worksheet_Baseboard_Init();
void WCO_Worksheet_Baseboard_Update();
char* WCO_Worksheet_Baseboard_Date(char *str);
void WCO_Worksheet_Baseboard_Creat(int page);
int *WCO_Worksheet_Baseboard_Threashold();