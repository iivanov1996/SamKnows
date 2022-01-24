#include "get_request.h"
	
	
int get_number_of_headers(int argc, char **argv) {
    int iterator = 1, number_of_headers = 0;

    while (iterator < argc) {
        if (strcmp(argv[iterator], "-H") == 0) {
            number_of_headers++;
        }
        iterator += 2;
    }
    return number_of_headers;
}

int parse_arguments(int argc, char **argv, int *number_of_requests, char **header_to_add ) {
	
	int iterator = 1, current_number_of_headers = 0;
	char *check_variable;
    while (iterator < argc) {
        check_variable = argv[iterator];

        if (strcmp(check_variable, "-H") == 0) {
            header_to_add[current_number_of_headers] = argv[iterator + 1];
            current_number_of_headers++;
        } else if (strcmp(check_variable, "-n") == 0)
            *number_of_requests = atoi(argv[iterator + 1]);
        else
            return ARGUMENT_READ_ERROR;

        iterator += 2;
	}
	
	return SUCCESS;
}

int test_connectivity(int argc, char **argv) {
	int total_number_of_headers, number_of_requests = 1;
    char *ip_addr;
    timing_latency report_timings;
    int error_code;
	int http_response_code;

    total_number_of_headers = get_number_of_headers(argc, argv);

    char *header_to_add[total_number_of_headers];  // array for storing the headers

	error_code = parse_arguments(argc, argv,&number_of_requests, header_to_add);
	if(error_code != SUCCESS)
		return error_code;

    if (init_program_env() != SUCCESS)
        return INIT_PROGRAM_ENV_ERROR;

    error_code = send_requests(number_of_requests, header_to_add, total_number_of_headers,
                       &report_timings, &ip_addr, &http_response_code);
    if (error_code != SUCCESS)
        return error_code;

    printf("SKTEST;%s;%d;%f;%f;%f;%f\n", ip_addr, http_response_code, report_timings.name_lookup, report_timings.connect, report_timings.start,
           report_timings.total);


    cleanup();
    return SUCCESS;	
	
}

