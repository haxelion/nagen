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
    float tolerance;
    int name_length;
    int name_number;
    FILE *input_file;
    FILE *symbol_file;
    FILE *output_file;
} Arguments;

typedef struct
{
    char *name;
    int connections_number;
    int *connections;
    int *connections_weight;
    int connections_total_weight;
    int symbols_number;
    char **symbols;
    int *symbols_weight;
    int symbols_total_weight;
} Rule;

int blank(char *buffer);
int getLine(char *buffer, int size, FILE *file);

#endif
