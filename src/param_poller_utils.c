/*  =========================================================================
    param_poller_utils - A utils class

    The MIT License (MIT)
    =========================================================================
*/

/*
@header
    param_poller_utils - A utils class
@discuss
@end
*/

#include "param_poller_classes.h"


//  --------------------------------------------------------------------------
//  Get index of the nth char occurence in a given string

int
param_poller_utils_get_index_of_nth_char_occurence (char *str, char c, int n)
{
    int index = -1;
    int occurence = 0;

    for(int i = 0; i < strlen(str); i++)
    {
        /* increment index as we iterate the string char by char */
        index++;

        /* check if char at current index is equad to char we are looking for */
        if(str[i] == c)
        {
            /* if it is then increment the char occurence counter */
            occurence++;

            /* check if we reached the nth occurance */
            if(occurence == n)
            {
                /* nth occurence of the c char was found */
                /* return the index of the nth occurence of the char */
                return index;
            }
        }
    }

    /* nth occurence of the c char was not found */
    return -1;
}


//  --------------------------------------------------------------------------
//  Init provider host and port

int
param_poller_utils_init_provider_host_and_port (char *host, char *port)
{
    /* the file stream */
    FILE *fs;

    /* the directory service uri fetched from the file */
    char uri[DIRECTORY_SERVICE_URI_MAX_CHAR] = {0};
    
    /* open the file */
    fs = fopen(DIRECTORY_SERVICE_URI_FILEPATH, "r");

    /* read file */
    fgets(uri, DIRECTORY_SERVICE_URI_MAX_CHAR, fs);

    /* close the file */
    fclose(fs);

    /* get required index to fetch host and port substrings from uri */
    int uri_index_start = param_poller_utils_get_index_of_nth_char_occurence(uri, '/', 2);
    int uri_index_end = param_poller_utils_get_index_of_nth_char_occurence(uri, ':', 2);
    int port_index_stop = param_poller_utils_get_index_of_nth_char_occurence(uri, '/', 3);

    /* check for errors */
    if(uri_index_start == -1 || uri_index_end == -1 || port_index_stop == -1)
    {
        return -1;
    }

    /* extract host and port from uri and set their values to their respective char array */
    memcpy(host, &uri[uri_index_start + 1], uri_index_end - uri_index_start - 1);
    memcpy(port, &uri[uri_index_end + 1], port_index_stop - uri_index_end - 1);

    /* return no error response code */
    return 0;
}


//  --------------------------------------------------------------------------
//  Init the configuration struct

int
param_poller_utils_init_config (configuration *config)
{
    /* the timestamp that will be used as part of the csv filename */
    uint32_t timestamp = (unsigned)time(NULL);

    /* init flags */
    config->params1.presence_flag = false;
    config->params2.presence_flag= false;
    config->params3.presence_flag = false;
    config->params4.presence_flag = false;
    config->params5.presence_flag = false;

    /* init csv filenames: toGround folder + params group identifier + timestamp + csv file extension */
    strcpy(config->params1.filename, "toGround/params1_");
    sprintf(config->params1.filename+17, "%d", timestamp);
    strcpy(config->params1.filename+27, ".csv");

    strcpy(config->params2.filename, "toGround/params2_");
    sprintf(config->params2.filename+17, "%d", timestamp);
    strcpy(config->params2.filename+27, ".csv");

    strcpy(config->params3.filename, "toGround/params3_");
    sprintf(config->params3.filename+17, "%d", timestamp);
    strcpy(config->params3.filename+27, ".csv");

    strcpy(config->params4.filename, "toGround/params4_");
    sprintf(config->params4.filename+17, "%d", timestamp);
    strcpy(config->params4.filename+27, ".csv");

    strcpy(config->params5.filename, "toGround/params5_");
    sprintf(config->params5.filename+17, "%d", timestamp);
    strcpy(config->params5.filename+27, ".csv");

    /* return */
    return 0;
}


//  --------------------------------------------------------------------------
//  Init the config param name list created from the param names comma separated string
//  The comma separate string is read from the app.ini config file1

int
param_poller_utils_init_config_param_name_list(char* param_names, char** param_name_list, size_t *param_name_list_size)
{
    size_t j = 0;
    size_t param_name_start_index = 0;
    size_t param_name_length = 0;

    for(size_t i = 0; i < strlen(param_names); i++)
    {
        if(param_names[i] == ',')
        {
            /* allocate memory for the param name string */
            /* +1 for the null terminator at the end of the param name string */
            param_name_list[j] = (char*)malloc((param_name_length + 1) * sizeof(char));

            /* set the param name string */
            strncpy(param_name_list[j], param_names + param_name_start_index, param_name_length);
            
            /* set the null terminator at the end of the param name string */
            param_name_list[j][param_name_length] = '\0'; 

            /* update the param names list index */
            j++;

            /* update the param name start index for the next param name */
            param_name_start_index = i + 1;   

            /* reset the param name  length for the next param name */
            param_name_length = 0;
        }
        else
        {
            param_name_length++;
        }
    }

    /* set the last param name string */
    param_name_list[j] = (char*)malloc((param_name_length + 1) * sizeof(char));
    strncpy(param_name_list[j], param_names + param_name_start_index, param_name_length);
    param_name_list[j][param_name_length] = '\0';

    /* set the param names list size */
    *param_name_list_size = j + 1;

    /* done create param name list */
    return 0;
}


//  --------------------------------------------------------------------------
//  Destroy the config param name list

int
param_poller_utils_destroy_config_param_name_list (configuration *config)
{
    if(config->params1.presence_flag)
    {
        for(size_t i = 0; i < config->params1.names_list_size; i++)
        {
            free(config->params1.names_list[i]);
        }
    }
    
    if(config->params2.presence_flag)
    {
        for(size_t i = 0; i < config->params2.names_list_size; i++)
        {
            free(config->params2.names_list[i]);
        }
    }

    if(config->params3.presence_flag)
    {
        for(size_t i = 0; i < config->params3.names_list_size; i++)
        {
            free(config->params3.names_list[i]);
        }
    }

    if(config->params4.presence_flag)
    {
        for(size_t i = 0; i < config->params4.names_list_size; i++)
        {
            free(config->params4.names_list[i]);
        }
    }

    if(config->params5.presence_flag)
    {
        for(size_t i = 0; i < config->params5.names_list_size; i++)
        {
            free(config->params5.names_list[i]);
        }
    }

    return 0;
}


//  --------------------------------------------------------------------------
//  Fetch and set params definitions

int
param_poller_utils_fetch_and_set_params_definitions (mc_parameter_service_t *parameter_service, params *parameters)
{
    /* return code */
    int rc = 0;

    /* send the listDefinition request with the response variable pointers */
    rc = mc_parameter_service_list_definition(parameter_service, parameters->names_list, parameters->names_list_size,
        &parameters->definitions.inst_id_list, &parameters->definitions.def_id_list, &parameters->definitions.list_size);


    /* error check */
    if(rc < 0)
    {
        /* print error message */
        printf("Error requesting list definition: %s\n",  parameters->names_csv);

        /* return the error code */
        return rc;
    }

    /* size check */
    if(parameters->names_list_size != parameters->definitions.list_size)
    {
        /* print error message */
        printf("Did not fetch the expected number of parameter definitions, expected %lu but was %lu: %s\n",
            parameters->names_list_size, parameters->definitions.list_size,  parameters->names_csv);

        /* return the error code */
        return rc;
    }

    return rc;
}


//  --------------------------------------------------------------------------
//  Fetch and set params attributes

int
param_poller_utils_fetch_and_set_params_attributes (mc_parameter_service_t *parameter_service, params *parameters)
{
    /* return code */
    int rc = 0;

    if(parameters->presence_flag)
    {
        /* fetch and set params definitions */
        rc = param_poller_utils_fetch_and_set_params_definitions(parameter_service, parameters);

        if(rc != 0)
        {
            printf("Error fetching parameter definitions: %s\n", parameters->names_csv);
            parameters->presence_flag = false;
            rc = 1;
        }
        else
        {
            rc = mc_parameter_service_get_value_list(parameter_service, parameters->definitions.inst_id_list, parameters->definitions.list_size,
                &parameters->attributes.attr_list, &parameters->attributes.tag_list, &parameters->attributes.list_size);

            if(rc != 0 || parameters->definitions.list_size != parameters->attributes.list_size)
            {
                printf("Error fetching parameter attributes: %s\n", parameters->names_csv);
                parameters->presence_flag = false;
                rc = 2;
            }
        }
    }

    /* return response code */
    return rc;
}


//  --------------------------------------------------------------------------
//  Fetch and set all params attributes

int
param_poller_utils_fetch_and_set_params_attributes_all (mc_parameter_service_t *parameter_service, configuration *config)
{
    param_poller_utils_fetch_and_set_params_attributes (parameter_service, &config->params1);
    param_poller_utils_fetch_and_set_params_attributes (parameter_service, &config->params2);
    param_poller_utils_fetch_and_set_params_attributes (parameter_service, &config->params3);
    param_poller_utils_fetch_and_set_params_attributes (parameter_service, &config->params4);
    param_poller_utils_fetch_and_set_params_attributes (parameter_service, &config->params5);

    return 0;
}


//  --------------------------------------------------------------------------
//  Write the param values as a row in a csv file

int
param_poller_utils_write_params_csv_row (FILE *fpt, union mal_attribute_t *attr_list, unsigned char *tag_list, size_t attr_count)
{
    union mal_attribute_t attr; 
    unsigned char tag;

    for(size_t i = 0; i < attr_count; i++)
    {
        attr = attr_list[i];
        tag = tag_list[i];

        /* write the parameter value based on the parameter type indicated by the attribute tag */
        switch(tag)
        {
            case MAL_IDENTIFIER_ATTRIBUTE_TAG:
                fprintf(fpt, "%s", attr.identifier_value);
                break;

            case MAL_STRING_ATTRIBUTE_TAG:
                fprintf(fpt, "%s", attr.string_value);
                break;

            case MAL_URI_ATTRIBUTE_TAG:
                fprintf(fpt, "%s", attr.uri_value);
                break;

            case MAL_BOOLEAN_ATTRIBUTE_TAG:
                fprintf(fpt, "%d", attr.boolean_value);
                break;

            case MAL_FLOAT_ATTRIBUTE_TAG:
                fprintf(fpt, "%f", attr.float_value);
                break;

            case MAL_DOUBLE_ATTRIBUTE_TAG:
                fprintf(fpt, "%f", attr.double_value);
                break;

            case MAL_OCTET_ATTRIBUTE_TAG:
                fprintf(fpt, "%c", attr.octet_value);
                break;

            case MAL_UOCTET_ATTRIBUTE_TAG:
                fprintf(fpt, "%u", attr.uoctet_value);
                break;

            case MAL_SHORT_ATTRIBUTE_TAG:
                fprintf(fpt, "%hd", attr.short_value);
                break;

            case MAL_USHORT_ATTRIBUTE_TAG:
                fprintf(fpt, "%hu", attr.ushort_value);
                break;

            case MAL_INTEGER_ATTRIBUTE_TAG:
                fprintf(fpt, "%d", attr.integer_value);
                break;

            case MAL_UINTEGER_ATTRIBUTE_TAG:
                fprintf(fpt, "%u", attr.uinteger_value);
                break;

            case MAL_LONG_ATTRIBUTE_TAG:
                fprintf(fpt, "%ld", attr.long_value);
                break;

            case MAL_ULONG_ATTRIBUTE_TAG:
                fprintf(fpt, "%lu", attr.ulong_value);
                break;

            default:
                /* not handling Blob, Time, and Finetime */
                fprintf(fpt, "");
        }

        /* comma to separate values along the row */
        if(i != attr_count-1)
        {
            fprintf(fpt, ",");
        }
        else
        {
             fprintf(fpt, "\n");
        }
        

        /**
         * IMPORTANT: don't forget to destroy the MAL attribute object
         * calling the destructor is only required for objects that are of type String
         * string objects are attributes of type: Blob, Identifier, String, and URI
         * here we just call the destructor everytime, no harm done.
         */
        mal_attribute_destroy(&attr, tag);
    }

    return 0;
}
