/*  =========================================================================
    param_poller_utils - A utils class

    The MIT License (MIT)
    =========================================================================
*/

#ifndef PARAM_POLLER_UTILS_H_INCLUDED
#define PARAM_POLLER_UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* path of the file containing the directory service uri */
#define DIRECTORY_SERVICE_URI_FILEPATH          "/home/nmf/supervisor/centralDirectoryService.uri"
#define DIRECTORY_SERVICE_URI_MAX_CHAR                                                         100

#define CSV_OUTPUT_FILENAME_SIZE                                                                32
#define MAX_PARAM_LIST_SIZE                                                                     20


/* params definition struct */
typedef struct
{
    long *inst_id_list;
    long *def_id_list;
    size_t list_size;
} params_definitions;

/* params attributes */
typedef struct
{
    union mal_attribute_t *attr_list;
    unsigned char *tag_list;
    size_t list_size;
    
} params_attributes;

/* params struct request */
typedef struct
{
    uint32_t timestamp;
    bool presence_flag;
    char filename[CSV_OUTPUT_FILENAME_SIZE];    /* e.g. value toGround/params1_1647837518.csv (31 characters) */
    char* names_csv;
    char* names_list[MAX_PARAM_LIST_SIZE];
    size_t names_list_size;
    params_definitions definitions;
    params_attributes attributes;
} params;

/* configuration struct */
typedef struct
{
    int iterations;
    int sleep;

    params params1;
    params params2;
    params params3;
    params params4;
    params params5;

} configuration;

//  Get index of the nth char occurence in a given string
PARAM_POLLER_EXPORT int
    param_poller_utils_get_index_of_nth_char_occurence (char *str, char c, int n);


//  Init the provider host and port
PARAM_POLLER_EXPORT int
    param_poller_utils_init_provider_host_and_port (char *host, char *port);


//  Init the configuration struct
PARAM_POLLER_EXPORT int
    param_poller_utils_init_config (configuration *config);


//  Init the config param name list created from the param names comma separated string
//  The comma separate string is read from the app.ini config file1
PARAM_POLLER_EXPORT int
    param_poller_utils_init_config_param_name_list (char* param_names, char** param_name_list, size_t *param_name_list_size);


//  Destroy the names list
PARAM_POLLER_EXPORT int
    param_poller_utils_destroy_config_param_name_list (configuration *config);


//  Fetch and set params definitions
PARAM_POLLER_EXPORT int
    param_poller_utils_fetch_and_set_params_definitions (mc_parameter_service_t *parameter_service, params *parameters);


//  Fetch and set params attributes
PARAM_POLLER_EXPORT int
    param_poller_utils_fetch_and_set_params_attributes (mc_parameter_service_t *parameter_service, params *parameters);


//  Fetch and set all params attributes
PARAM_POLLER_EXPORT int
    param_poller_utils_fetch_and_set_params_attributes_all (mc_parameter_service_t *parameter_service, configuration *config);


//  Write the param values as a row in a csv file
PARAM_POLLER_EXPORT int
    param_poller_utils_write_params_csv_row (FILE *fpt, uint32_t timestamp, union mal_attribute_t *attr_list, unsigned char *tag_list, size_t attr_count);


#ifdef __cplusplus
}
#endif

#endif
