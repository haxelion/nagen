#include "nagen.h"


int blank(char *buffer)
{
    int i;
    for(i=0;buffer[i]!='\0'; i++)
        if(buffer[i]>32)
            return 0;
    return 1;
}

int getLine(char *buffer, int size, FILE *file)
{
    int i;
    int valid = 0;
    while(valid == 0)
    {
        if(fgets(buffer, BUFFER_LENGTH, file)==NULL)
            return 0;
        if(blank(buffer) == 0)
            valid = 1;
    }
    for(i=0; buffer[i] != '\0'; i++)
        if((buffer[i] == '\n')||(buffer[i] == '\r')||(buffer[i] == '\t'))
            buffer[i] = '\0';
    return 1;
}

