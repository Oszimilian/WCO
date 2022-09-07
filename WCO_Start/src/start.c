#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    if(argc >= 2)
    {
        char *path = (char*) malloc(sizeof(char) * strlen(getcwd(NULL, 0)));
        strcat(path, getcwd(NULL, 0));
        printf("%d -> %s\n", argc, strcat(path, "/File/path.txt"));
        FILE *init = fopen(path, "r");
        char *text = (char*) malloc((sizeof(char) * fgetc(init)));
        printf("%s", fgets(text, fgetc(init), init));
        fclose(init);
    }


    return 0;
}