/*
This file is part of nagen.

Nagen is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nagen is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2012 Charles Hubain <haxelion@gmail.com>
*/
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
