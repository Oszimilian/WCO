#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char s[100];
    printf("Dir: %s \n", getcwd(s, 100));
    chdir("/home/maximilian/Git/WCO/bin/");
    printf("Dir: %s \n", getcwd(s, 100));
    system("./prog");

    return 0;
}