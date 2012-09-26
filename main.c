#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "word_generator.h"

arguments* processArguments(int argc, char**argv);
void printHelp();

int main(int argc, char **argv)
{
    arguments *args;
    Rule *rules;
    int i;
    
    srand(time(NULL));
    args = processArguments(argc, argv);
    rules = processRuleFile(args);
    for(i=0;i<args->name_number;i++)
    {
        if(args->name_length<1)
            generateName(rules, 3+rand()%6);
        else
            generateName(rules, args->name_length);
    }
    return 0;
}

arguments* processArguments(int argc, char**argv)
{
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->name_length = 0;
    args->name_number = 1;
    int i;
    if(argc>1)
    {
        args->file_name = argv[argc-1];
        for(i = 1; i<argc-1; i++)
        {
            if(strcmp(argv[i], "-l") == 0)
            {
                args->name_length = atoi(argv[i+1]);
                i++;
            }
            else if(strcmp(argv[i], "-n") == 0)
            {
                args->name_number = atoi(argv[i+1]);
                i++;
            }
            else
                printf("Unrecognized %s switch\n", argv[i]);
        }
    }
    else
    {
        printHelp();
        exit(1);
    }
    return args;
}

void printHelp()
{
    printf("\nNagen is a custom language random name generator.\n");
    printf("\nUsage: nagen [-n numberofname] [-l lengthofname] languagefile\n\n");
}
