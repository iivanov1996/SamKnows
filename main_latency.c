#include <stdio.h>
#include "get_request.h"


int main(int argc, char **argv) {

	int catch_error =  test_connectivity(argc,argv);
	
	if(catch_error)
		printf("SKTEST;FAILED\n");
	switch(catch_error) {
		case(0): 
			break;
		case(1): 
			printf("Unknown argument. The only acceptable argument types are -n and -H. \n");
			break;
		case(2): 
			printf("Environment initialization error. Try again. \n");
			break;
		case(3): 
			printf("The new header cannot be added to the HTTP request. \n");
			break;
		case(4): 
			printf("The header values passed as arguments cannot be set simultaneously. \n");
			break;
		case(5): 
			printf("Internal initialization error. Try again. \n");
			break;
		case(6): 
			printf("The URL should be correctly formatted as a string. \n");
			break;
		case(7):
			printf("The URL does not exist \n ");
			break;
		case(8):
			printf("HTTP request responce code cannot be read. \n ");
			break;
		case(9):
			printf("The IP address of the server cannot be read.  \n ");
			break;		
		case(10):
			printf("HTTP request latency cannot be read  \n ");
			break;

	}
   

} 
