#include "latency_lib.h"
#include <stdio.h>


static int compare(const void *a, const void *b) {
    if (*(double *) a > *(double *) b) return 1;
    if (*(double *) a < *(double *) b) return -1;
    return 0;
}

static void find_median(double *array_to_sort, int number_of_elements, double *median_value) {
    qsort(array_to_sort, number_of_elements, sizeof(array_to_sort), compare);
    if (number_of_elements % 2)
        *median_value = array_to_sort[number_of_elements / 2];
    else
        *median_value = (array_to_sort[number_of_elements / 2 - 1] + array_to_sort[number_of_elements / 2]) / 2;

}

int init_program_env() {
    return curl_global_init(CURL_GLOBAL_DEFAULT); // Global libcurl initialisation, allocate resources
}

int perform_request(int current_request_number, double *latency_total_time, double *latency_start_transfer, double *latency_connect_time,
                    double *latency_name_lookup_time, char **ip_http, char *header_string[], int num_headers, int* http_response_code) {
    CURL *curl;
    timing_latency tmp;
    char *ip;
	int http_code = 0;

    curl = curl_easy_init();
    struct curl_slist *list = NULL;
    if (curl) {
        if (curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/") != CURLE_OK)
            return URL_SET_ERROR;

        for (int i = 0; i < num_headers; i++) {
            list = curl_slist_append(list, header_string[i]);
            if (list == NULL)
                return HEADER_APPEND_ERROR;
        }
        if (curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) != CURLE_OK)
            return HEADER_SET_ERROR;
		
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);  // Not to print the HTML response
		
        if (curl_easy_perform(curl) != CURLE_OK)
            return PERFORM_ERROR;
		
		if(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code) != CURLE_OK)
			return GET_RESPONSE_CODE_ERROR;
		
		*http_response_code = http_code;
        
        if (!curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip) && ip) {
                *ip_http = (char *) malloc((strlen(ip) + 1) * sizeof(char));
                strcpy(*ip_http, ip);
            }
            else
                return IP_GET_ERROR;

        if (curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &tmp.total) == CURLE_OK)
            latency_total_time[current_request_number] = tmp.total;
		else
			return TIME_GET_ERROR;


        if (curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &tmp.start) == CURLE_OK)
            latency_start_transfer[current_request_number] = tmp.start;
		else
			return TIME_GET_ERROR;


        if (curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &tmp.connect) == CURLE_OK)
            latency_connect_time[current_request_number] = tmp.connect;
		else
			return TIME_GET_ERROR;


        if (curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &tmp.name_lookup) == CURLE_OK)
            latency_name_lookup_time[current_request_number] = tmp.name_lookup;
		else
			return TIME_GET_ERROR;

        curl_slist_free_all(list); /* free the list again */
        curl_easy_cleanup(curl);
        return SUCCESS;
    }
    else
        return INIT_TRANSFER_ERROR;
}

int send_requests(int number_of_requests, char **header_string, int num_headers, timing_latency *latency_returns,
          char **ip_http, int* http_response_code) {

    double latency_total_time[number_of_requests], latency_start_transfer[number_of_requests];
    double latency_connect_time[number_of_requests], latency_name_lookup_time[number_of_requests];
    timing_latency tmp;

    for (int i = 0; i < number_of_requests; i++) {
        int status_code = perform_request(i, latency_total_time, latency_start_transfer, latency_connect_time,
                                          latency_name_lookup_time, ip_http, header_string, num_headers, http_response_code);
        if (status_code != SUCCESS)
            return status_code;
    }

	
    find_median(latency_total_time, number_of_requests, &tmp.total);
    find_median(latency_start_transfer, number_of_requests, &tmp.start);
    find_median(latency_connect_time, number_of_requests, &tmp.connect);
    find_median(latency_name_lookup_time, number_of_requests, &tmp.name_lookup);


    latency_returns->total = tmp.total;
    latency_returns->start = tmp.start;
    latency_returns->connect = tmp.connect;
    latency_returns->name_lookup = tmp.name_lookup;
    return SUCCESS;
}

void cleanup() {
    curl_global_cleanup(); //releases resources
}
