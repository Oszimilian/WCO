#ifndef PDF_H_INCLUDED
#define PDF_H_INCLUDED

#define _Zahler 0
#define _Nenner 1

typedef struct{
    HPDF_Doc pdf;
    HPDF_Page page[20];

    int pageSize[2];

    char systemOpenFile[2][100];
    char fileName[2][100];
    char folderName[100];

} MyPDF_t;






//struct WCO_PDF_t MyPDF;

static jmp_buf env;

//PDF
void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
int WCO_PDF_Check();
void WCO_PDF_SetupPage(int page);
void WCO_PDF_SetFoldername(char *folderName);
void WCO_PDF_SetFilename(const char *fileName, int page);
void WCO_PDF_WriteText(int x, int y, char *text, int page);
void WCO_PDF_SavePDF(int page);
void WCO_PDF_DrawSolutionLine(char *text, int x1, int y1, int line_Lengh, int page);
void WCO_PDF_DrawLine(int x1, int y1, int x2, int y2, int page);




#endif