//
//  httpproxy.h
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "common.h"

class httpproxy {
  private:
    /*Private Variables*/
    std::vector< std::pair< std::string, char * > > cache; //Used for storing the path to the cached result
    
    /*Private Methods*/
    
  
  protected:
    /*Protected Variables*/
    int port;           //The port number to search for connection
    int cache_size;     //The number of results that can be cached
    int max_cache_size; //The maximum size, in bytes, of a cached result
    
    int listenfd;
    int connfd;
    struct sockaddr_in servaddr;
    
    char recvline[MAXLINE + 1];
    char *buffer;
    char *address; //the address of requested site
    
    
    /*Protected Methods*/
    void handle_connection();
    
  public:
    //Constructor/Destructor
    httpproxy();
    httpproxy(int port, int cache, int cache_size);
    ~httpproxy() {    }
    
    /*Public Methods*/
    void setup_request();
    void parse_request();
    int check_method();
    int create_request();
    void send_405();
};