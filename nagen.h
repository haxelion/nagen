#ifndef NAGEN_H
#define NAGEN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


typedef struct
{
    int mode;
    char *symbol_file_name;
    int tolerance;
    int name_length;
    int name_number;
    char *file_name;
} arguments;

#endif
