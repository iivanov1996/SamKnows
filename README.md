# SamKnows Task

## The Challenge
For this task I created a library that will check how good the connectivity to http://www.google.com/ is. 
The library executes one or more HTTP GET requests to http://www.google.com/, read the responses, and prints the list of read responce values.  The implementation of the libraty was done using https://curl.haxx.se/libcurl/c/ "easy" interface, but the user wont be aware of it.


The program is accepting the following arguments:
* `-H "Header-name: Header-value"`: can be send multiple times, each time specifying additional HTTP header to add to the request
* `-n <integer>`: number of HTTP requests to make, that will be used to calculate the median of

The output of the program is a list of the response values in this format:

    SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>
    
If some error occur in the process of getting the response, the output of the program is a list in this format:

    SKTEST;FAILED
    
Also, the program will print out the cause of the error. This is done for debigging and helping the user solving the issue and having successful HTTP GET request.

## Requirements 

* CMake
* GCC Compiler
* Git shell

## CURL library

First download the latest source from the Git server and build the source code:

    git clone https://github.com/curl/curl.git
    
    
## Explanation
The program accepts two types of arguments, number of HTTP requests and HTTP header values.
Both argument types are optional. The program does not add any additional HTTP header values, if none are specified as an argument. 

If the number of HTTP requests is not specified, it is predefined to send only one request and get the statistics only based on that request. If more than one request is sent to the http://www.google.com/ , I collect all the response time from the requests, sort it in ascending order and get the median. The meadian is not vulnerable to outlieres. Therefore it provides a representative/realistic reponse of the conectivity. The code however allows an easy modfication for any other descriprtive statistics, such as mean. 

 The third element in the return list is HTTP responce code.  The program has been tested on different HTTP status codes, using the specialized website http://httpstat.us/. I must mention that the response code is the return from the last query. It is assumed that all HTTP requests in that batch will get the same responce code.

Different types of error may arise while performing a HTTP request. I am taking into consideration 9 different error types that may occur. For example, if the URL does not exist, the queries will fail and the code will signal it with a flag. If any error arises, the test is not performed correctly and the user must run the program again. Otherwise, the list of response values as mentioned above is expected to be printed in the terminal. 





