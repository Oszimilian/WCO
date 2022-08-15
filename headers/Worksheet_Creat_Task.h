#define _enable 1
#define _disable 0
#define _succeded 1
#define _error 0
#define _Tasks 0
#define _Solutions 1

#define _Terms 0 
#define _Fractions 1

#define _X 0
#define _Y 1

typedef struct {
    char task[2][50][50];
    int operand[50];
}MyTask_t;

void WCO_Worksheet_Task_Start();
MyTask_t *WCO_Worksheet_Task_Init();
void WCO_Worksheet_Task_Default(MyTask_t *MyTask);
void WCO_Worksheet_Task_Free(MyTask_t *MyTask);
void WCO_Worksheet_Task_Creat(MyTask_t *MyTask, int page);
void WCO_Worksheet_Task_Random(MyTask_t *MyTask, int count);
float WCO_Worksheet_Task_Calculate(MyTask_t *MyTask, int *count, float *a, float *b);
void WCO_Worksheet_Task_Draw(MyTask_t *MyTask, int *x, int *y, int count, int page);