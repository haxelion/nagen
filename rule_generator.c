#include "rule_generator.h"

int generateRules(Arguments *args, Rule * rules)
{
    char **symbols;
    int symbols_number;
    int **frequency;
    int total_count;
    int i,j;
    int rules_number;

    symbols_number = countSymbols(args->symbol_file);
    symbols = (char**) malloc(sizeof(char*)*symbols_number);
    loadSymbols(args->symbol_file, symbols, symbols_number);
    frequency = (int**)malloc(sizeof(int*)*symbols_number);
    for(i=0;i<symbols_number; i++)
    {
        frequency[i] = (int*)malloc(sizeof(int)*symbols_number);
        for(j=0; j<symbols_number; j++)
            frequency[i][j] = 0;
    }  

    total_count = calculateFrequency(args->input_file, symbols, frequency, symbols_number);
    rules_number = buildRules(symbols, frequency, symbols_number, args->tolerance, rules);
    return rules_number;
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
    int a=0;

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
            printf("Symbol '%c' not found and has been skipped.\n", buffer[i]);
        else
        {
            found_symbols[a++] = j-1;   
            i+=k-1;
        }
    }
    return a;
}

int buildRules(char **symbols, int **frequency, int symbols_number, float tolerance, Rule *rules)
{
    int *groups;
    int groups_number;
    int i, j;

    groups = malloc(sizeof(int)*symbols_number);
    for(i=0; i<symbols_number; i++)
        groups[i] = i;
    for(i=0; i<symbols_number; i++)
        if(groups[i] == i)
            for(j=i+1; j<symbols_number; j++)
                if(groups[j] == j)
                    if(isSimilar(frequency, symbols_number, i, j, tolerance) == 1)
                        groups[j] = groups[i];
    //DEBUG
    for(i=0;i<symbols_number; i++)
        printf("%s : %d\n", symbols[i], groups[i]);
    return 0;
    //groups_number = countGroups(groups, symbols_number);
}

int isSimilar(int **frequency, int symbols_number, int i, int j, float tolerance)
{
    int k;
    int total_i=0, total_j=0;
    int tolerance_i, tolerance_j;
    float factor;

    
    for(k=0; k<symbols_number; k++)
    {
        total_i += frequency[i][k];
        total_j += frequency[j][k];
    }
    tolerance_i = (int)(total_i*tolerance);
    tolerance_j = (int)(total_j*tolerance);
    for(k=0; k<symbols_number; k++)
    {
        if(frequency[j][k]+tolerance_j<frequency[i][k]-tolerance_i)
            return 0;
        if(frequency[j][k]-tolerance_j>frequency[i][k]+tolerance_i)
            return 0;
    }

    total_i = 0;
    total_j = 0;
    for(k=0; k<symbols_number; k++)
    {
        total_i += frequency[k][i];
        total_j += frequency[k][j];
    }
    tolerance_i = (int)(total_i*tolerance);
    tolerance_j = (int)(total_j*tolerance);
    if(total_j == 0)
        factor = 1.0f;
    else
        factor = (float)total_i/total_j;
    for(k=0; k<symbols_number; k++)
    {
        if((frequency[k][j]+tolerance_j)*factor<frequency[k][i]-tolerance_i)
            return 0;
        if((frequency[k][j]-tolerance_j)*factor>frequency[k][i]+tolerance_i)
            return 0;
    }
    return 1;

}
