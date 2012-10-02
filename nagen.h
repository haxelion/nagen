#ifndef NAGEN_H
#define NAGEN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 256

typedef struct
{
    int mode;
    int tolerance;
    int name_length;
    int name_number;
    FILE *input_file;
    FILE *symbol_file;
    FILE *output_file;
} Arguments;

typedef struct
{
    char *name;
    int connection_number;
    int *connections;
    int *connection_weight;
    int connection_total_weight;
    int symbol_number;
    char **symbols;
    int *symbol_weight;
    int symbol_total_weight;
} Rule;

#endif
