#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int user_input_flag;
char user_input[250];

typedef struct
{
    char *directory;
    char *input;
    FILE *file;
    char user_input[250];
    

    int input_Len;
    char *mode;
    char *prog_folder;
    char *docker_cmd;

}MyStart_t;



void WCO_Start_Add_Dir(MyStart_t *MyStart, char *folder, char *name)
{
    strcat(MyStart->directory, getcwd(NULL, 0));
    strcat(MyStart->directory, folder);

    int folder_flag = 0;
    int file_flag = 0;
    

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if(d != NULL)
    {
        while((dir = readdir(d)) != NULL)
        {
            if(!strcmp("File", dir->d_name))
            {
                folder_flag = 1;
            }
        }
        if(!folder_flag)
        {
            system("mkdir File");

        } 
        closedir(d);
    }

    chdir(MyStart->directory);
    strcat(MyStart->directory, name);


    struct dirent *dir2;
    d = opendir(".");
    if(d != NULL)
    {
        while((dir2 = readdir(d)) != NULL)
        {
            if(!strcmp("path.txt", dir2->d_name))
            {
                file_flag = 1;
            }
        }
        if(!file_flag || user_input_flag)
        {
            if(user_input_flag == 0) 
            {
                fprintf(stderr, "Neu Inizialisierung nur mit Input möglich! \n");
                goto FAIL;
            }
            FILE *fp;
            fp = fopen("path.txt", "w");
            fputs(user_input, fp);
            fclose(fp);
        }
        closedir(d);
    }
    FAIL:
}

void WCO_Start_Get_Txt(MyStart_t *MyStart, int pos)
{
    int counter = pos;
    while((MyStart->input[counter] = fgetc(MyStart->file)) != EOF && MyStart->input[counter] != '\r' && MyStart->input[counter] != '\n')
    {
        //printf("TXT: %d -> %c -> %x \n", counter, MyStart->input[counter], MyStart->input[counter]);
        counter++;
    }

    if (MyStart->input[counter] == '\r')
    {
        MyStart->input[++counter] = fgetc(MyStart->file);
        if (MyStart->input[counter] != '\n')
        {
            ungetc(MyStart->input[counter], MyStart->file);
        }
    }
   
    if ((MyStart->input[counter] = fgetc(MyStart->file)) != EOF)
    {
        counter++;
        WCO_Start_Get_Txt(MyStart, counter);
    }else{
        ungetc(MyStart->input[counter], MyStart->file);
        MyStart->input = realloc(MyStart->input, sizeof(char) * counter);
        MyStart->input[counter] = '\0';
        MyStart->input_Len = counter;
        return;
    }
    
}

MyStart_t *WCO_Start_Init(char *folder, char *name)
{
    MyStart_t *MyStart = (MyStart_t*) malloc(sizeof(MyStart_t));

    MyStart->directory = (char*) malloc(sizeof(char) * strlen(getcwd(NULL, 0)));
    WCO_Start_Add_Dir(MyStart, folder, name);
    MyStart->file = fopen(MyStart->directory, "r");
    MyStart->input = (char*) malloc((sizeof(char) * 250) + sizeof(char));

    
    return MyStart;
}

void WCO_Start_Free(MyStart_t *MyStart)
{
    free(MyStart->mode);
    free(MyStart->prog_folder);
    free(MyStart->docker_cmd);
    free(MyStart->directory);
    fclose(MyStart->file);
    free(MyStart);
}

void WCO_Start_CMD_Seperate(MyStart_t *MyStart)
{
    int k = 0;
    int i = 0;

    MyStart->mode = (char*) malloc(sizeof(char) * MyStart->input_Len);
    MyStart->prog_folder = (char*) malloc(sizeof(char) * MyStart->input_Len);
    MyStart->docker_cmd = (char*) malloc(sizeof(char) * MyStart->input_Len);

    while(MyStart->input[i] != '\0')
    {
        
        if(MyStart->input[i] == '-')
        {
            k = 0;
            switch(MyStart->input[++i])
            {
                case 'm':   
                            while(MyStart->input[++i] != '-' && MyStart->input[i] != '\0' )
                            {
                                if (MyStart->input[i] != ' ') MyStart->mode[k++] = MyStart->input[i];                         
                            }
                break;

                case 'f':
                            while(MyStart->input[++i] != '-' && MyStart->input[i] != '\0')
                            {
                                if (MyStart->input[i] != ' ') MyStart->prog_folder[k++] = MyStart->input[i];
                            } 
                break;

                case 'd':
                            while(MyStart->input[++i] != '-' && MyStart->input[i] != '\0')
                            {
                                //printf("i: %d -> k: %d -> %c -> %x \n", i, k,  MyStart->input[i], MyStart->input[i]);
                                MyStart->docker_cmd[k++] = MyStart->input[i];
                            }
                break; 

                default: break;
            }
        }
    }

    MyStart->mode[strlen(MyStart->mode)] = '\0';
    MyStart->prog_folder[strlen(MyStart->prog_folder)] = '\0';
    MyStart->docker_cmd[strlen(MyStart->docker_cmd)] = '\0';

    MyStart->mode = realloc(MyStart->mode, strlen(MyStart->mode));
    MyStart->prog_folder = realloc(MyStart->prog_folder, strlen(MyStart->prog_folder));
    MyStart->docker_cmd = realloc(MyStart->docker_cmd, strlen(MyStart->docker_cmd));

    for(int i = 0; i <= strlen(MyStart->docker_cmd);i++)
    {
        //printf("%d -> %c -> %x \n", i, MyStart->docker_cmd[i], MyStart->docker_cmd[i]);
    }
}

void WCO_Start_wco(MyStart_t *MyStart)
{
    if (!strcmp("Docker", MyStart->mode))
    {
        printf("Docker modus aktiv \n");

        if(system(MyStart->prog_folder) != 0)
        {
            if((!system(MyStart->docker_cmd) != 0))
            {
                printf("Docker-Container konnte nicht gestartet werden: %s\n", MyStart->docker_cmd);
            }
        }else{
            printf("X-Server konnte nicht gestartet werden: %s\n", MyStart->prog_folder);
        }
        
    }
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        user_input_flag = 1;
        for(int i = 1; i <= (argc - 1); i++)
        {    
            strcat(user_input, argv[i]);
            user_input[strlen(user_input)] = '\0';
        }
    }

    MyStart_t *MyStart = WCO_Start_Init("/File", "/path.txt");

    WCO_Start_Get_Txt(MyStart, 0);

    WCO_Start_CMD_Seperate(MyStart);

        printf("CMD: %s \nCMD: %s \nCMD: %s \n", MyStart->mode, MyStart->prog_folder, MyStart->docker_cmd);

    WCO_Start_wco(MyStart);

    WCO_Start_Free(MyStart);

    return 0;
}

