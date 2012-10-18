#include "word_generator.h"


int interpret(char *buffer)
{
    int start=0, end, i;
    int c = -2;
    for(i=0; buffer[i]!='\0'; i++)
        if(buffer[i]=='[' || buffer[i]=='-' || buffer[i]=='*')
        {
            c = buffer[i];
            start = i+1;
            break;
        }
    for(i=start;buffer[i]!='\0'; i++)
        if(buffer[i]==']' || buffer[i]=='\r' || buffer[i]=='\n')
            break;
    end = i;
    for(i=0;i<end-start; i++)
        buffer[i]=buffer[start+i];
    buffer[i]='\0';
    return c;
}


int extractLine(FILE *file, int length, char *buffer)
{
    int valid = -1;
    while(valid==-1)
    {
        if(getLine(buffer, length, file)!=NULL)
        {
            valid = interpret(buffer);
            if(valid == -2)
                printf("Line \"%s\" has no meaning. Like your life.\n", buffer);
        }
        else
        {
            valid=0;
            buffer[0]='\0';
        }
    }
    return valid;
}

Rule* processRuleFile(Arguments *args)
{
    int rules_number;
    Rule *rules;
    rules_number = countRules(args->input_file);
    rules = malloc(sizeof(Rule)*rules_number);
    initPass(args->input_file, rules, rules_number);
    finalPass(args->input_file, rules, rules_number);
    fclose(args->input_file);
    return rules;
}

int countRules(FILE *file)
{
    char buffer[BUFFER_LENGTH];
    int c;
    int rules_number = 0;

    fseek(file, 0, SEEK_SET);
    do
    {
        c = extractLine(file, BUFFER_LENGTH, buffer);
        if(c=='[')
            rules_number++;
    }while(c!=0);
    return rules_number;
}

void initPass(FILE *file, Rule *rules, int rules_number) 
{
    char buffer[BUFFER_LENGTH];
    int i, c;
    int count;

    fseek(file, 0, SEEK_SET);
    c = extractLine(file, BUFFER_LENGTH, buffer);
    for(i=0; i<rules_number;i++)
    {
        while(c!='[')
            c = extractLine(file, BUFFER_LENGTH, buffer);
        rules[i].name = malloc(strlen(buffer)+1);
        strcpy(rules[i].name, buffer);
        count = 0;
        c = extractLine(file, BUFFER_LENGTH, buffer);
        while(c=='-')
        {
            count++;
            c = extractLine(file, BUFFER_LENGTH, buffer);
        }
        rules[i].connections_number = count;
        rules[i].connections = (int*) malloc(sizeof(int)*count);
        rules[i].connections_weight = (int*) malloc(sizeof(int)*count);
        
        count = 0;
        while(c=='*')
        {
            count++;
            c=extractLine(file, BUFFER_LENGTH, buffer);
        }
        rules[i].symbols_number = count;
        rules[i].symbols_weight = (int*) malloc(sizeof(int)*count);
        rules[i].symbols = (char**) malloc(sizeof(char*)*count);
    }
}

void finalPass(FILE *file, Rule *rules, int rules_number) 
{
    char buffer[BUFFER_LENGTH];
    int i, j, c;
    
    fseek(file, 0, SEEK_SET);
    c = extractLine(file, BUFFER_LENGTH, buffer);
    for(i=0; i<rules_number;i++)
    {
        while(c!='[')
            c = extractLine(file, BUFFER_LENGTH, buffer);
        c = extractLine(file, BUFFER_LENGTH, buffer);
        for(j=0; j<rules[i].connections_number; j++)
        {
            setConnection(buffer, rules, rules_number, i, j);
            c = extractLine(file, BUFFER_LENGTH, buffer);
        }

        for(j=0; j<rules[i].symbols_number; j++)
        {
            setSymbol(buffer, &rules[i], j);
            c = extractLine(file, BUFFER_LENGTH, buffer);
        }
        
        rules[i].connections_total_weight = 0;
        for(j=0;j<rules[i].connections_number;j++)
            rules[i].connections_total_weight+=rules[i].connections_weight[j];

        rules[i].symbols_total_weight = 0;
        for(j=0;j<rules[i].symbols_number;j++)
            rules[i].symbols_total_weight+=rules[i].symbols_weight[j];
    }
}

void setConnection(char *buffer, Rule *rules, int rules_number, int i, int j)
{
    int k;

    rules[i].connections_weight[j] = atoi(strchr(buffer, ' '));
    if(rules[i].connections_weight[j] == 0)
        printf("The weight \"%s\" was evaluated to null. Like your IQ.\n", strchr(buffer, ' '));
    strchr(buffer, ' ')[0]='\0';
    for(k=0;k<rules_number; k++)
    {
        if(strcmp(buffer, rules[k].name)==0)
            break;
        else if(k+1==rules_number)
        {
            printf("The rule \"%s\" wasn't found. Like your brain.\n", buffer);
            exit(1);
        }
    }
    rules[i].connections[j] = k;
}

void setSymbol(char *buffer, Rule *rule, int j)
{
    rule->symbols_weight[j] = atoi(strchr(buffer, ' '));
    if(rule->symbols_weight[j] == 0)
        printf("The weight \"%s\" was evaluated to null. Like your skills.\n", strchr(buffer, ' '));
    strchr(buffer, ' ')[0]='\0';
    rule->symbols[j] = malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(rule->symbols[j], buffer);
}

void generateName(FILE *file,Rule *rules, int length)
{
    int i,k,r,current_rule;
    char buffer[1024];
    buffer[0] = '\0';
    current_rule = 0;
    for(i=0; i<length;)
    {
        if(rules[current_rule].symbols_total_weight>0)
        {   
            r = rand()%(rules[current_rule].symbols_total_weight);
            for(k=-1; r>=0; r-=rules[current_rule].symbols_weight[++k]);
            strcat(buffer, rules[current_rule].symbols[k]);
            i++;
        }
        if(rules[current_rule].connections_total_weight==0)
            break;
        r = rand()%(rules[current_rule].connections_total_weight);
        for(k=-1; r>=0; r-=rules[current_rule].connections_weight[++k]);
        current_rule = rules[current_rule].connections[k];
    }
    fprintf(file,"%s\n", buffer);
}
