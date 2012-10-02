#include "nagen.h"


int interpret(char *buffer);
int extractLine(FILE *file, int length, char *buffer);
Rule* processRuleFile(Arguments *args);
int countRules(FILE *file);
void initPass(FILE *file, Rule *rules, int rules_number); 
void finalPass(FILE *file, Rule *rules, int rules_number); 
void setName(char *name, Rule *rule);
void setConnection(char *buffer, Rule *rules, int rules_number, int i, int j);
void setSymbol(char *buffer, Rule *rule, int j);
void generateName(FILE *file,Rule *rules, int length);
