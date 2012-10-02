#include "nagen.h"

int generateRules(Arguments *args, Rule *rules);
int countSymbols(FILE *file);
void loadSymbols(FILE *file, char **symbols, int symbols_number);
void writeRules(Rule* rules, int rules_number, FILE *file);

