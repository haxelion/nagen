#include "nagen.h"

int generateRules(Arguments *args, Rule *rules);
int countSymbols(FILE *file);
void loadSymbols(FILE *file, char **symbols, int symbols_number);
void sortByLength(char **symbols, int symbols_number);
void writeRules(Rule* rules, int rules_number, FILE *file);
int calculateFrequency(FILE *file, char **symbols, int **frequency, int symbols_number);
int findSymbols(char *buffer, char **symbols, int symbols_number, int *found_symbols);
