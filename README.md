# SamKnows Task

## The Challenge
For this task, I created a library that will check how good the connectivity to http://www.google.com/ is. 
The library sends one or more HTTP GET requests to http://www.google.com/, reads the responses, and prints a summary of the read response values.  The implementation of the library was done using https://curl.haxx.se/libcurl/c/ "easy" interface, but its usage will not be leaked to the user. This enables the libcurl to be easily replaced with another one.


The program accepts the following arguments:
* `-H "Header-name: Header-value"`: can be sent multiple times, each time specifying an additional HTTP header to add to the request
* `-n <integer>`: number of HTTP requests to make, that will be used to calculate the median of

If the program encounters an unknown argument, it will terminate with a responding error message. 


The output of the program is a list of the response values in this format:

    SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>
    
If an error arises in the process of getting the response, the output of the program is a list in this format:

    SKTEST;FAILED
    
Also, the program will print out the cause of the error. This is done for helping the user solve the issue and have a successful HTTP GET request.

## Requirements 

* CMake
* GCC Compiler
* Git shell

## CURL library

Download the latest source from the Git server and build the source code using the provided instructions on the repository itself:

    git clone https://github.com/curl/curl.git
    

## Program execution

First, clone this git repository to your machine and change the working directory to SamKnows using the command `cd SamKnows`.  Next, execute the Makefile by running the command `make`.  Finally, to test connectivity to http://www.google.com/, run the generated executable **samknows_lib** with the appropriate arguments.

    
## Explanation
The program accepts two types of arguments, the number of HTTP requests and HTTP header values.
Both argument types are optional. The program does not add any additional HTTP header values if none are specified as an argument. 
If the number of HTTP requests is not specified, it is predefined to send only one request and get the statistics only based on that request. If more than one request is sent to http://www.google.com/, I collect all the response times from the requests, sort them in ascending order and calculate the median. The median is not vulnerable to outliers, therefore it provides a representative/realistic response of the connectivity. The code however allows an easy modification for any other descriptive statistics, such as mean.

If the arguments are correctly set and no error has arisen, the output of the program is in the following format:

    SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>

The first element in the list is a constant string. The following two elements are the IP address of the server and the HTTP response code.  The returned response code and IP address are obtained from the last query. This is due to the assumption that all HTTP requests in that batch will get the same IP address and response code. The program has been tested on different HTTP status codes, using the specialized website http://httpstat.us/, as well as, on different URLs. 


The remaining four elements are the medians of the latencies in performing the HTTP GET requests. 


While performing an HTTP request, different types of errors may arise. I am taking into consideration ten different errors that may occur. For example, if the URL does not exist, the queries will fail, and the code will signal it with a flag. If any error arises, the test is not performed correctly, and the user must run the program again. Otherwise, the list of response values as mentioned above is expected to be printed in the terminal. 


The program is built using a provided Makefile. The Makefile, as well as the entire code base, is modular. The Makefile ensures the portability of the program to different platforms. The final result is the executable **samknows_lib** generated by the compiler, which can be run in a command line with acceptable arguments.  

