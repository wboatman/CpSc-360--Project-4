//
//  startup.cpp
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "startup.h"

void startup::initialize(){
	this->setup_socket();
}

//Sets and opens the socket to receive a connection
void startup::setup_socket() {
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_n_die(SOCKERR);
	}
	int optval = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(this->port);
	
	if((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
		err_n_die(BINDERR);
	}
	
	if((listen(listenfd, MAX_CONNECTIONS)) < 0) {
		err_n_die(LISTERR);
	}
	
	this->wait_for_connection();
}

//Waits for a connection to the startup. 
void startup::wait_for_connection() {
	while(true) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		disperse_connection();
	}
}

//Forks the connection, and waits for more connections
void startup::disperse_connection() {
	int pid = fork();
		if(pid == 0) {  	// If it's a child, parse connection
			handle_connection();
		}
		else {				// Otherwise, wait for another connection
			wait_for_connection();
		}
}


int main(int argc, char **argv) {
    
    int port = 4567;
    int cache_size = 10;
    int max_cache_size = 32000;
    
    int c;
    while((c = getopt(argc, argv, "p:n:s:")) != -1) {
        switch (c) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'n':
                cache_size = atoi(optarg);
                break;
            case 's':
                max_cache_size = atoi(optarg);
                break;
        }
    }

    startup *server = new startup(port, cache_size, max_cache_size);
    server->initialize();
    
    return 0;
}