#include "rule_generator.h"

int generateRules(Arguments *args, Rule * rules)
{
    char **symbols;
    int symbols_number;
    int **frequency;
    int total_count;
    int i;
    int rules_number;

    symbols_number = countSymbols(args->symbol_file);
    loadSymbols(args->symbol_file, symbols, symbols_number);
    frequency = (int**)malloc(sizeof(int*)*symbols_number);
    for(i=0;i<symbols_number; i++)
        frequency[i] = (int*)malloc(sizeof(int)*symbols_number);
    //total_count = calculateFrequency(args->input_file, symbols, frequency, symbols_number);
    //rules_number = setRuleSymbols(symbols, frequency, symbols_number, args->tolerance);
    //connectRules(rules, frequency, symbols, symbol_number);
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
    int i, j;

    fseek(file, 0, SEEK_SET);
    symbols = (char**) malloc(sizeof(char*)*symbols_number);
    for(i=0; i<symbols_number; i++)
    {
        fgets(buffer, BUFFER_LENGTH, file);
        for(j=0; buffer[j] != '\0'; j++)
            if((buffer[j] == '\n')||(buffer[j] == '\r')||(buffer[j] == '\t'))
                buffer[j] = '\0';
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
