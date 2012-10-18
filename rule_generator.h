#include "nagen.h"

Rule* generateRules(Arguments *args, int *rules_number);
int countSymbols(FILE *file);
void loadSymbols(FILE *file, char **symbols, int symbols_number);
void sortByLength(char **symbols, int symbols_number);
int calculateFrequency(FILE *file, char **symbols, int **frequency, int symbols_number);
int findSymbols(char *buffer, char **symbols, int symbols_number, int *found_symbols);
void buildRules(char **symbols, int **frequency, int symbols_number, float tolerance, Rule *rules);
void writeRules(Rule* rules, int rules_number, FILE *file);
