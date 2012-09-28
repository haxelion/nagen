#include "nagen.h"


int blank(char *buffer);
int interpret(char *buffer);
int getLine(FILE *file, int length, char *buffer);
Rule* processRuleFile(Arguments *args);
int countRules(FILE *file);
void initPass(FILE *file, Rule *rules, int rules_number); 
void finalPass(FILE *file, Rule *rules, int rules_number); 
void setName(char *name, Rule *rule);
void setConnection(char *buffer, Rule *rules, int rules_number, int i, int j);
void setSymbol(char *buffer, Rule *rule, int j);
void generateName(FILE *file,Rule *rules, int length);
