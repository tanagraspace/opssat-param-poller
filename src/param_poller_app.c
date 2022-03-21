/*  =========================================================================
    param_poller_app - Param Poller

    The MIT License (MIT)
    =========================================================================
*/

/*
@header
    param_poller_app - Param Poller
@discuss
@end
*/


#include "param_poller_classes.h"

/* configuration struct */
typedef struct
{
    int iterations;
    int sleep;

    bool params1_flag;
    char params1_csv[32];     /* eg. value toGround/params1_1647837518.csv (31 characters) */
    const char* params1_names;

    bool params2_flag;
    char params2_csv[32];
    const char* params2_names;

    bool params3_flag;
    char params3_csv[32];
    const char* params3_names;

    bool params4_flag;
    char params4_csv[32];
    const char* params4_names;

    bool params5_flag;
    char params5_csv[32];
    const char* params5_names;

} configuration;



int print_config (configuration *config)
{
    /* verbosity */
    printf("Config loaded from app.ini:\n");

    /* general configs */
    printf("  General:\n    iteration: %d\n    sleep: %d\n", config->iterations, config->sleep);

    /* params config */
    printf("  Params:\n");
    
    if(config->params1_flag)
    {
        printf("    #1: %s\n", config->params1_names);
    }

    if(config->params2_flag)
    {
        printf("    #2: %s\n", config->params2_names);
    }

    if(config->params3_flag)
    {
        printf("    #3: %s\n", config->params3_names);
    }

    if(config->params4_flag)
    {
        printf("    #4: %s\n", config->params4_names);
    }

    if(config->params5_flag)
    {
        printf("    #5: %s\n", config->params5_names);
    }

    return 0;
}


static int handler (void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

    if (MATCH("general", "iterations"))
    {
        pconfig->iterations = atoi(value);
    }
    else if (MATCH("general", "sleep"))
    {
        pconfig->sleep = atoi(value);
    }
    else if (MATCH("params", "params1"))
    {
        pconfig->params1_flag = true;
        pconfig->params1_names = strdup(value);
    }
    else if (MATCH("params", "params2"))
    {
        pconfig->params2_flag = true;
        pconfig->params2_names = strdup(value);
    }
    else if (MATCH("params", "params3"))
    {
        pconfig->params3_flag = true;
        pconfig->params3_names = strdup(value);
    }
    else if (MATCH("params", "params4"))
    {
        pconfig->params4_flag = true;
        pconfig->params4_names = strdup(value);
    }
    else if (MATCH("params", "params5"))
    {
        pconfig->params5_flag = true;
        pconfig->params5_names = strdup(value);
    }
    else
    {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}


int init_config (configuration *config)
{
    /* the timestamp that will be used as part of the csv filename */
    uint32_t timestamp = (unsigned)time(NULL);

    /* init flags */
    config->params1_flag = false;
    config->params2_flag = false;
    config->params3_flag = false;
    config->params4_flag = false;
    config->params5_flag = false;

    /* init csv filenames */
    strcpy(config->params1_csv, "toGround/params1_");
    sprintf(config->params1_csv+17, "%d", timestamp);
    strcpy(config->params1_csv+27, ".csv");

    strcpy(config->params2_csv, "toGround/params2_");
    sprintf(config->params2_csv+17, "%d", timestamp);
    strcpy(config->params2_csv+27, ".csv");

    strcpy(config->params3_csv, "toGround/params3_");
    sprintf(config->params3_csv+17, "%d", timestamp);
    strcpy(config->params3_csv+27, ".csv");

    strcpy(config->params4_csv, "toGround/params4_");
    sprintf(config->params4_csv+17, "%d", timestamp);
    strcpy(config->params4_csv+27, ".csv");

    strcpy(config->params5_csv, "toGround/params5_");
    sprintf(config->params5_csv+17, "%d", timestamp);
    strcpy(config->params5_csv+27, ".csv");

    /* return */
    return 0;
}


int main (int argc, char *argv [])
{
    bool verbose = false;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-h")) {
            puts ("param_poller_app [options] ...");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --help / -h            this information");
            return 0;
        }
        else
        if (streq (argv [argn], "--verbose")
        ||  streq (argv [argn], "-v"))
            verbose = true;
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }
    
    /* init config struct */
    configuration config;

    /* init config */
    if(init_config(&config) < 0)
    {
        printf("Can't init configuration\n");
        return 1;
    }

    /* parse configuration file */
    if(ini_parse("app.ini", handler, &config) < 0) 
    {
        printf("Can't load app.ini\n");
        return 1;
    }

    /* verbosity on loaded configuration values */
    if(verbose)
    {
        print_config(&config);
    }

    /* init csv file pointers */

    FILE *fpt_params1;
    if(config.params1_flag)
    {
        fpt_params1 = fopen(config.params1_csv, "w+");      /* open file */
        fprintf(fpt_params1, "%s\n", config.params1_names); /* write header row */
    }

    FILE *fpt_params2;
    if(config.params2_flag)
    {
        fpt_params2 = fopen(config.params2_csv, "w+");
        fprintf(fpt_params2, "%s\n", config.params2_names);
    }

    FILE *fpt_params3;
    if(config.params3_flag)
    {
        fpt_params3 = fopen(config.params3_csv, "w+");
        fprintf(fpt_params3, "%s\n", config.params3_names);
    }

    FILE *fpt_params4;
    if(config.params4_flag)
    {
        fpt_params4 = fopen(config.params4_csv, "w+");
        fprintf(fpt_params4, "%s\n", config.params4_names);
    }

    FILE *fpt_params5;
    if(config.params5_flag)
    {
        fpt_params5 = fopen(config.params5_csv, "w+");
        fprintf(fpt_params5, "%s\n", config.params5_names);
    }


    /* fetch values */

    for(size_t i = 0; i < config.iterations; i++)
    {
        if(config.params1_flag)
        {
            printf("Fetching %s\n", config.params1_names);
            fprintf(fpt_params1, "%s\n", config.params1_names); /* TODO: write param values (writing param names for now) */
        }

        if(config.params2_flag)
        {
            printf("Fetching %s\n", config.params2_names);
            fprintf(fpt_params1, "%s\n", config.params2_names); /* TODO: write param values (writing param names for now) */
        }

        if(config.params3_flag)
        {
            printf("Fetching %s\n", config.params3_names);
            fprintf(fpt_params1, "%s\n", config.params3_names); /* TODO: write param values (writing param names for now) */
        }

        if(config.params4_flag)
        {
            printf("Fetching %s\n", config.params4_names);
            fprintf(fpt_params1, "%s\n", config.params4_names); /* TODO: write param values (writing param names for now) */
        }

        if(config.params5_flag)
        {
            printf("Fetching %s\n", config.params5_names);
            fprintf(fpt_params1, "%s\n", config.params5_names); /* TODO: write param values (writing param names for now) */
        }
        
        /* sleep before fetching new values */
        if(i != config.iterations - 1)
        {
            sleep(config.sleep);
        }
    }

    /* close csv file pointers */
    if(config.params1_flag) fclose(fpt_params1);
    if(config.params2_flag) fclose(fpt_params2);
    if(config.params3_flag) fclose(fpt_params3);
    if(config.params4_flag) fclose(fpt_params4);
    if(config.params5_flag) fclose(fpt_params5);

    return 0;
}
