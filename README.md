# SamKnows Task

## The Challenge
The given task was to get to know how good the connectivity to http://www.google.com/ is. The implementation was done uding  (really simple) https://curl.haxx.se/libcurl/c/ "easy" interface. I created a library that executes one or more HTTP GET requests to http://www.google.com/, read the responses, and extract statistics from the responses (e.g. the TCP connection establishment time). 

The program is accepting the following arguments:
* `-H "Header-name: Header-value"`: can be used multiple times, each time specifying an extra HTTP header to add to the request
* `-n <integer>`: number of HTTP requests to make  the number of samples to take the median of)

The output of the program is a semicolon delimited list of values in this format:

    SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>


## Git

First download the latest source from the Git server do this:

    git clone https://github.com/curl/curl.git

(you will get a directory named curl created, filled with the source code)


To build the source code run the following commands:

* ` cmake . `

* `make `
    
* `make install ( run it as a root ) `
    
* `autoreconf --install `
    
* ` ./configure `
    
* ` make `
    
* `make install ` 
    

