#include "nagen.h"
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
    if(args->mode == 0)
    {
        rules = processRuleFile(args);
        for(i=0;i<args->name_number;i++)
        {
            if(args->name_length<1)
                generateName(rules, 3+rand()%6);
            else
                generateName(rules, args->name_length);
        }
    }
    else if(args->mode == 1)
    {
        //rules = generateRules(args);
        //writeRules(rules, args);
    }
    return 0;
}

arguments* processArguments(int argc, char**argv)
{
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->name_length = 0;
    args->name_number = 1;
    args->tolerance = 0;
    int i;
    if(argc>1)
    {
        args->file_name = argv[argc-1];
        if(strcmp(argv[1], "-g") == 0)
        {
            args->mode = 1;
            for(i = 2; i<argc-1; i++)
            {
                if(strcmp(argv[i], "-s") == 0)
                {
                    args->symbol_file_name = argv[i+1];
                    i++;
                }
                else if(strcmp(argv[i], "-t") == 0)
                {
                    args->tolerance = atoi(argv[i+1]);
                    i++;
                }
                else
                    printf("Unrecognized %s switch\n", argv[i]);
            }
        }
        else
        {
            args->mode = 0;
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
    printf("Usage: nagen [-n numberofname] [-l lengthofname] languagefile\n");
    printf("       nagen -g [-s symbolfile] [-t tolerance] wordlistfile\n");
}
