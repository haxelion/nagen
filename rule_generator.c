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
#include "rule_generator.h"

Rule* generateRules(Arguments *args, int *rules_number)
{
    char **symbols;
    int symbols_number;
    int **frequency;
    int total_count;
    int i,j;
    Rule *rules;

    symbols_number = countSymbols(args->symbol_file);
    symbols = (char**) malloc(sizeof(char*)*(symbols_number+1));
    loadSymbols(args->symbol_file, symbols, symbols_number);
    frequency = (int**)malloc(sizeof(int*)*(symbols_number+1));
    for(i=0;i<symbols_number+1; i++)
    {
        frequency[i] = (int*)malloc(sizeof(int)*symbols_number);
        for(j=0; j<symbols_number; j++)
            frequency[i][j] = 0;
    }  

    total_count = calculateFrequency(args->input_file, symbols, frequency, symbols_number);
    *rules_number = symbols_number+1;
    rules = (Rule*) malloc(sizeof(Rule)*(symbols_number+1));
    buildRules(symbols, frequency, symbols_number, args->tolerance, rules);
    return rules;
}

int countSymbols(FILE *file)
{
    char buffer[BUFFER_LENGTH];
    int count = 0;

    fseek(file, 0, SEEK_SET);
    while(fgets(buffer, BUFFER_LENGTH, file) != NULL)
        count++;
    return count;
}

void loadSymbols(FILE *file, char **symbols, int symbols_number)
{
    char buffer[BUFFER_LENGTH];
    int i;

    fseek(file, 0, SEEK_SET);
    for(i=0; i<symbols_number; i++)
    {
        getLine(buffer, BUFFER_LENGTH, file);
        symbols[i] = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(symbols[i], buffer);
    }
    symbols[symbols_number] = (char*)malloc(sizeof(char));
    symbols[symbols_number][0] = '\0';
    sortByLength(symbols, symbols_number);
}

void sortByLength(char **symbols, int symbols_number)
{
    int max_length, max_i;
    int i, j;
    char *temp;

    for(i=0; i<symbols_number; i++)
    {        
        max_length = strlen(symbols[i]);
        max_i = i;
        for(j=i+1; j<symbols_number; j++)
            if(strlen(symbols[j])>max_length)
                max_i = j;
        temp = symbols[i];
        symbols[i] = symbols[max_i];
        symbols[max_i] = temp;
    }
}

int calculateFrequency(FILE *file, char **symbols, int **frequency, int symbols_number)
{
    char buffer[BUFFER_LENGTH];
    int found_symbols[BUFFER_LENGTH];
    int found_symbols_number;
    int total_count = 0;
    int i;

    while(getLine(buffer, BUFFER_LENGTH, file) != 0)
    {
        found_symbols_number = findSymbols(buffer, symbols, symbols_number, found_symbols);
        for(i=1; i<found_symbols_number; i++)
        {
            frequency[found_symbols[i-1]][found_symbols[i]]++;
            total_count++;
        }
    }
    return total_count;
}

int findSymbols(char *buffer, char **symbols, int symbols_number, int *found_symbols)
{
    int i, j, k, equal;
    int a=1;
    found_symbols[0] = symbols_number;

    for(i=0; buffer[i]!='\0'; i++)
    {
        equal = 0;
        for(j=0; j<symbols_number&&equal == 0; j++)
        {
            equal = 1;
            for(k=0; symbols[j][k]!='\0'; k++)
            {
                if(symbols[j][k]!=buffer[i+k]||buffer[i+k]=='\0')
                {
                    equal = 0;
                    break;
                }
            }
        } 
        if(equal == 0)
        {
            printf("Line \"%s\" contains an unknown symbol at %d and was dropped.\n", buffer, i);
            return 0;
        }
        else
        {
            found_symbols[a++] = j-1;   
            i+=k-1;
        }
    }
    return a;
}

void buildRules(char **symbols, int **frequency, int symbols_number, float tolerance, Rule *rules)
{
    int i, j, k;
    
    for(i=0; i<symbols_number+1; i++)
    {
        rules[i].name = (char*)malloc(sizeof(char)*(strlen(symbols[i])+1));
        rules[i].symbols_number = 1;
        rules[i].symbols = (char**)malloc(sizeof(char*)*1);
        rules[i].symbols[0] = malloc(sizeof(char)*(strlen(symbols[i])+1));
        rules[i].symbols_weight = (int*)malloc(sizeof(int)*1);
        rules[i].symbols_weight[0] = 1;
        strcpy(rules[i].symbols[0], symbols[i]);
        strcpy(rules[i].name, symbols[i]);
        rules[i].connections_number = 0;
        for(j=0; j<symbols_number; j++)
            if(frequency[i][j]>0)
                rules[i].connections_number++;
        rules[i].connections = (int*)malloc(sizeof(int)*rules[i].connections_number);
        rules[i].connections_weight = (int*)malloc(sizeof(int)*rules[i].connections_number);
        k=0;
        for(j=0; j<symbols_number; j++)
            if(frequency[i][j]>0)
            {
                rules[i].connections_weight[k] = frequency[i][j];
                rules[i].connections[k] = j;
                k++;
            }
    }
}

void writeRules(Rule* rules, int rules_number, FILE *file)
{
    int i, j;

    for(i=rules_number-1; i>=0; i--)
    {
        fprintf(file, "[%s]\n", rules[i].name);
        for(j=0;j<rules[i].connections_number; j++)
            fprintf(file, "-%s %d\n", rules[rules[i].connections[j]].name, rules[i].connections_weight[j]);
        for(j=0;j<rules[i].symbols_number; j++)
            fprintf(file, "*%s %d\n", rules[i].symbols[j], rules[i].symbols_weight[j]);

        fprintf(file, "\n");
    }
}
