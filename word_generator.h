#include "nagen.h"

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


int blank(char *buffer);
int interpret(char *buffer);
int getLine(FILE *file, int length, char *buffer);
Rule* processRuleFile(arguments *args);
int countRules(FILE *file);
void initPass(FILE *file, Rule *rules, int rules_number); 
void finalPass(FILE *file, Rule *rules, int rules_number); 
void setName(char *name, Rule *rule);
void setConnection(char *buffer, Rule *rules, int rules_number, int i, int j);
void setSymbol(char *buffer, Rule *rule, int j);
void generateName(Rule *rules, int length);
