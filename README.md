# SamKnows Task

## The Challenge
The given task was to get to know how good the connectivity to http://www.google.com/ is. The implementation was done uding  (really simple) https://curl.haxx.se/libcurl/c/ "easy" interface. I created a library that executes one or more HTTP GET requests to http://www.google.com/, read the responses, and extract statistics from the responses (e.g. the TCP connection establishment time). 

The program is accepting the following arguments:
* `-H "Header-name: Header-value"`: can be used multiple times, each time specifying an extra HTTP header to add to the request
* `-n <integer>`: number of HTTP requests to make  (the number of samples to take the median of)

The output of the program is a semicolon delimited list of values in this format:

    SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>

## Requirements 

* CMake
* GCC Compiler
* Git shell

## Git

First download the latest source from the Git server and build the source code:

    git clone https://github.com/curl/curl.git
    
    
## Explanation
The program accepts two types of arguments, number of HTTP requests and HTTP header values.
Both argument types are optional. If the number of HTTP requests is not specified, it is predefined to send only one request.
Similarly, the program does not add any additional HTTP header values, if none are specified as an argument. 

I am taking into consideration 10 different error types that may occur while performing a HTTP request. If any of them occurs, the TEST is not performed correctly and the user must run the program again. Otherwise, the list of values as mentioned above is expected to be printed in the terminal. 
The third element in the return list is HTTP responce code. I must mention that the response code is the return from the last query. It is assumed that all HTTP requests in that batch will get the same responce code.
