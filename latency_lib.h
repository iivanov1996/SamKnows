#include "curl/curl.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    SUCCESS,
    ARGUMENT_READ_ERROR,
    INIT_PROGRAM_ENV_ERROR,
    HEADER_APPEND_ERROR,
    HEADER_SET_ERROR,
    INIT_TRANSFER_ERROR,
    URL_SET_ERROR,
    PERFORM_ERROR,
	GET_RESPONSE_CODE_ERROR,
    IP_GET_ERROR,
	TIME_GET_ERROR
} ERROR_CODES;


typedef struct timing_latency {
    double total, start, connect, name_lookup;
} timing_latency;



int init_program_env();

int send_requests(int number_of_requests, char **header_string, int num_headers, timing_latency *latency_returns,
          char **ip_http, int* http_response_code);

void cleanup();
