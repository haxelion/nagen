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
    int i;

    fseek(file, 0, SEEK_SET);
    symbols = (char**) malloc(sizeof(char*)*symbols_number);
    for(i=0; i<symbols_number; i++)
    {
        fgets(buffer, BUFFER_LENGTH, file);
        symbols[i] = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(symbols[i], buffer);
    }
    //sortByLength(char **symbols, int symbols_number);
}
