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


//  --------------------------------------------------------------------------
//  Constants

#define ARRAY_SIZE_HOST                                20
#define ARRAY_SIZE_PPORT                                5
#define ARRAY_SIZE_CPORT                                5


//  --------------------------------------------------------------------------
//  Declare global variables

// The Gateway API object to access all services
nmf_api_t *nmf_api;

//  --------------------------------------------------------------------------
//  Init the NMF Service Provider API

int
init_nmf_api(char *arg_host, char *arg_pport, char *arg_cport)
{
    /* Fetch the default host and port values by reading the centralDirectoryService.uri file */

    /* char array for provider host and port */
    char phost[ARRAY_SIZE_HOST] = {0};
    char pport[ARRAY_SIZE_PPORT] = {0};

    /* char array for consumer port */
    char cport[ARRAY_SIZE_CPORT] = {0};

    /* set provider host and port by reading the centralDirectoryService.uri file, but only if that file exists */
    if(access(DIRECTORY_SERVICE_URI_FILEPATH, F_OK) == 0)
    {
        /* set provider host and port */
        param_poller_utils_init_provider_host_and_port(phost, pport);

        /* set consumer port as an increment of the provider port */
        int cport_int;
        sscanf(pport, "%d", &cport_int);
        cport_int++;

        /* cast consumer port to string */
        sprintf(cport, "%d", cport_int);
    }
    

    /* Default to values that were given via command arguments (overwrite values read from the centralDirectoryService.uri file) */
    if(strlen(arg_host) != 0)
    {
        strcpy(phost, arg_host);
    }

    if(strlen(arg_pport) != 0)
    {
        strcpy(pport, arg_pport);
    }

    if(strlen(arg_cport) != 0)
    {
        strcpy(cport, arg_cport);
    }

    /* initialize the Gateway API object to access NMF services */
    nmf_api = nmf_api_new(phost, pport, cport);

    // Check for error
    if(nmf_api == NULL)
    {
        return 1;
    }

    /* success */
    return 0;
}


//  --------------------------------------------------------------------------
//  Parse main program arguments (all arguments are optional)

int
parse_args (int argc, char *argv [], char *host, char *pport, char *cport, int *log_level)
{
    /* get provider host and port from command arguments */
    int argv_index_host = -1;
    int argv_index_pport = -1;
    int argv_index_cport = -1;
    int argv_index_log = -1;

    /* only log errors by default */
    *log_level = CLOG_ERROR_LEVEL;

    // --------------------------------------------------------------------------
    // parse the command arguments (all arguments are optional)

    int argn;
    for (argn = 1; argn < argc; argn++)
    {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-?"))
        {
            printf("param_poller [options] ...");
            printf("\n  --host  / -h        hostname");
            printf("\n  --pport / -p        provider port");
            printf("\n  --cport / -p        consumer port");
            printf("\n  --debug / -d        enable debug logging");
            printf("\n  --help  / -?        this information\n\n");
            
            /* program exit code */
            return 1;
        }
        else
        if (streq (argv [argn], "--host")
        ||  streq (argv [argn], "-h"))
            argv_index_host = ++argn;
        else
        if (streq (argv [argn], "--pport")
        ||  streq (argv [argn], "-p"))
            argv_index_pport = ++argn;
        else
        if (streq (argv [argn], "--cport")
        ||  streq (argv [argn], "-c"))
            argv_index_cport = ++argn;
        else
        if (streq (argv [argn], "--debug")
        ||  streq (argv [argn], "-d"))
            *log_level = CLOG_DEBUG_LEVEL;
        else
        {
            /* print error message */
            printf("Unknown option: %s\n\n", argv[argn]);

            /* program exit code */
            return 1;
        }
    }

    /* set values for options that have been set via command arguments */
    /* default values for host and ports are read from the centralDirectoryService.uri file  */

    /* set the provider host */
    if(argv_index_host != -1)
    {
        strcpy(host, argv[argv_index_host]);
    }

    /* set the provider port */
    if(argv_index_pport != -1)
    {
        strcpy(pport, argv[argv_index_pport]);
    }

    /* set the consumer port */
    if(argv_index_cport != -1)
    {
        strcpy(cport, argv[argv_index_cport]);
    }
    
    /* parse success */
    return 0;
}


//  --------------------------------------------------------------------------
//  Handle config file entry
//  Unlike other functions in this project this handle function returns 0 in case of error
//  See: https://github.com/benhoyt/inih

static int
handle_config_file_entry (void* user, const char* section, const char* name, const char* value)
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
        pconfig->params1.presence_flag = true;
        pconfig->params1.names_csv = strdup(value);
        if(param_poller_utils_init_config_param_name_list(pconfig->params1.names_csv, pconfig->params1.names_list, &pconfig->params1.names_list_size) != 0)
        {
            printf("Can't init params1 name list\n");
            return 0;
        }
    }
    else if (MATCH("params", "params2"))
    {
        pconfig->params2.presence_flag = true;
        pconfig->params2.names_csv = strdup(value);
        if(param_poller_utils_init_config_param_name_list(pconfig->params2.names_csv, pconfig->params2.names_list, &pconfig->params2.names_list_size) != 0)
        {
            printf("Can't init params2 name list\n");
            return 0;
        }
    }
    else if (MATCH("params", "params3"))
    {
        pconfig->params3.presence_flag = true;
        pconfig->params3.names_csv = strdup(value);
        if(param_poller_utils_init_config_param_name_list(pconfig->params3.names_csv, pconfig->params3.names_list, &pconfig->params3.names_list_size) != 0)
        {
            printf("Can't init params3 name list\n");
            return 0;
        }
    }
    else if (MATCH("params", "params4"))
    {
        pconfig->params4.presence_flag = true;
        pconfig->params4.names_csv = strdup(value);
        if(param_poller_utils_init_config_param_name_list(pconfig->params4.names_csv, pconfig->params4.names_list, &pconfig->params4.names_list_size) != 0)
        {
            printf("Can't init params4 name list\n");
            return 0;
        }
    }
    else if (MATCH("params", "params5"))
    {
        pconfig->params5.presence_flag = true;
        pconfig->params5.names_csv = strdup(value);
        if(param_poller_utils_init_config_param_name_list(pconfig->params5.names_csv, pconfig->params5.names_list, &pconfig->params5.names_list_size) != 0)
        {
            printf("Can't init params5 name list\n");
            return 0;
        }
    }
    else
    {
        return 0;  /* unknown section/name, error */
    }

    return 1;
}


//  --------------------------------------------------------------------------
//  The main program

int
main (int argc, char *argv [])
{
    /* return code to check for errors or program exit codes */
    int rc = 0;

    /* optional program arguments */
    char host[ARRAY_SIZE_HOST] = {0};
    char pport[ARRAY_SIZE_PPORT] = {0};
    char cport[ARRAY_SIZE_CPORT] = {0};
    int log_level;

    /* parse the given program arguments */
    rc = parse_args(argc, argv, host, pport, cport, &log_level);

    /* check for error code or program exit code */
    if (rc != 0)
    {
        /* exit program */
        return rc;
    }

    /* init log level */
    nmf_api_set_global_log_level(log_level);

    /* init the NMF Service Provider API */
    rc = init_nmf_api(host, pport, cport);

    /* check for error code or program exit code */
    if (rc != 0)
    {
        /* exit program */
        return rc;
    }
    
    /* init config struct */
    configuration config;

    /* init config */
    if(param_poller_utils_init_config(&config) != 0)
    {
        printf("Can't init configuration\n");
        return 1;
    }

    /* parse configuration file */
    if(ini_parse("app.ini", handle_config_file_entry, &config) != 0) 
    {
        printf("Can't load app.ini\n");
        return 1;
    }

    /* get pointer to the Parameter service */
    mc_parameter_service_t *parameter_service = nmf_api_get_mc_parameter_service(nmf_api);


    /* init csv file pointers */

    FILE *fpt_params1;
    if(config.params1.presence_flag)
    {
        fpt_params1 = fopen(config.params1.filename, "w+");      /* open file */
        fprintf(fpt_params1, "timestamp,%s\n", config.params1.names_csv);  /* write header row */
    }

    FILE *fpt_params2;
    if(config.params2.presence_flag)
    {
        fpt_params2 = fopen(config.params2.filename, "w+");
        fprintf(fpt_params2, "timestamp,%s\n", config.params2.names_csv);
    }

    FILE *fpt_params3;
    if(config.params3.presence_flag)
    {
        fpt_params3 = fopen(config.params3.filename, "w+");
        fprintf(fpt_params3, "timestamp,%s\n", config.params3.names_csv);
    }

    FILE *fpt_params4;
    if(config.params4.presence_flag)
    {
        fpt_params4 = fopen(config.params4.filename, "w+");
        fprintf(fpt_params4, "timestamp,%s\n", config.params4.names_csv);
    }

    FILE *fpt_params5;
    if(config.params5.presence_flag)
    {
        fpt_params5 = fopen(config.params5.filename, "w+");
        fprintf(fpt_params5, "timestamp,%s\n", config.params5.names_csv);
    }

    /* fetch and set all param attributes */
    /* write the param values as a row in a csv file */

    for(size_t i = 0; i < config.iterations; i++)
    {   
        /* fetch and set all param attributes */
        param_poller_utils_fetch_and_set_params_attributes_all(parameter_service, &config);

        /* write the param values as a row in a csv file */

        if(config.params1.presence_flag)
        {
            param_poller_utils_write_params_csv_row(fpt_params1,
                config.params1.timestamp, config.params1.attributes.attr_list, config.params1.attributes.tag_list, config.params1.attributes.list_size);
        }

        if(config.params2.presence_flag)
        {
            param_poller_utils_write_params_csv_row(fpt_params2,
                config.params2.timestamp, config.params2.attributes.attr_list, config.params2.attributes.tag_list, config.params2.attributes.list_size);
        }

        if(config.params3.presence_flag)
        {
            param_poller_utils_write_params_csv_row(fpt_params3,
                config.params3.timestamp, config.params3.attributes.attr_list, config.params3.attributes.tag_list, config.params3.attributes.list_size);
        }

        if(config.params4.presence_flag)
        {
            param_poller_utils_write_params_csv_row(fpt_params4,
                config.params4.timestamp, config.params4.attributes.attr_list, config.params4.attributes.tag_list, config.params4.attributes.list_size);
        }

        if(config.params5.presence_flag)
        {
            param_poller_utils_write_params_csv_row(fpt_params5,
                config.params5.timestamp, config.params5.attributes.attr_list, config.params5.attributes.tag_list, config.params5.attributes.list_size);
        }
        
        /* sleep before fetching new values */
        if(i != config.iterations - 1)
        {
            sleep(config.sleep);
        }

        /* exit the program if the stop experiment file exists in the app's folder */
        /* this file is created when invoking the stop experiment bash script */
        if(access(".stop", F_OK) == 0)
        {
            break;
        }
    }

    /* close csv file pointers */
    if(config.params1.presence_flag) fclose(fpt_params1);
    if(config.params2.presence_flag) fclose(fpt_params2);
    if(config.params3.presence_flag) fclose(fpt_params3);
    if(config.params4.presence_flag) fclose(fpt_params4);
    if(config.params5.presence_flag) fclose(fpt_params5);

    /* destroy config param name list */
    param_poller_utils_destroy_config_param_name_list(&config);

    /* destoy the API gateway object, also destroys all service objects */
    nmf_api_destroy(&nmf_api);

    /* end of program */
    return rc;
}
