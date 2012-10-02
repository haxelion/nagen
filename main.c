#include "nagen.h"
#include "word_generator.h"

Arguments* processArguments(int argc, char**argv);
void printHelp();

int main(int argc, char **argv)
{
    Arguments *args;
    Rule *rules;
    int rules_number;
    int i;
    
    srand(time(NULL));
    args = processArguments(argc, argv);
    if(args->mode == 0)
    {
        rules = processRuleFile(args);
        for(i=0;i<args->name_number;i++)
        {
            if(args->name_length<1)
                generateName(args->output_file, rules, 3+rand()%6);
            else
                generateName(args->output_file, rules, args->name_length);
        }
    }
    else if(args->mode == 1)
    {
        rules_number = generateRules(args, rules);
        //writeRules(rules, rules_number, args->output_file);
    }
    fclose(args->output_file);
    return 0;
}

Arguments* processArguments(int argc, char**argv)
{
    Arguments *args = (Arguments*) malloc(sizeof(Arguments));
    args->name_length = 0;
    args->name_number = 1;
    args->tolerance = 0;
    args->output_file = stdout;
    int i;
    if(argc>1)
    {
        args->input_file = fopen(argv[argc-1], "r");
        if(args->input_file == NULL)
        {
            printf("Input file %s not found.\n", argv[argc-1]);
            exit(1);
        }
        if(strcmp(argv[1], "-g") == 0)
        {
            args->mode = 1;
            for(i = 2; i<argc-1; i++)
            {
                if(strcmp(argv[i], "-s") == 0)
                {
                    args->symbol_file = fopen(argv[i+1], "r");
                    if(args->symbol_file == NULL)
                    {
                        printf("Symbol file %s not found.\n", argv[i+1]);
                        exit(1);
                    }
                    i++;
                }
                else if(strcmp(argv[i], "-t") == 0)
                {
                    args->tolerance = atoi(argv[i+1]);
                    i++;
                }
                else if(strcmp(argv[i], "-o") == 0)
                {
                    args->output_file = fopen(argv[i+1], "w");
                    if(args->output_file == NULL)
                    {
                        printf("Output file %s not found.\n", argv[i+1]);
                        exit(1);
                    }
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
                else if(strcmp(argv[i], "-o") == 0)
                {
                    args->output_file = fopen(argv[i+1], "w");
                    if(args->output_file == NULL)
                    {
                        printf("Output file %s not found.\n", argv[i+1]);
                        exit(1);
                    }
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
    printf("Usage: nagen [-n numberofname] [-l lengthofname] [-o outputfile] languagefile\n");
    printf("       nagen -g [-s symbolfile] [-t tolerance] [-o outputfile] wordlistfile\n");
}
