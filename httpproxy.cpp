//
//  httpproxy.cpp
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "httpproxy.h"
#include "common.h"

httpproxy::httpproxy() {
    err_n_die(BADARGS);
}

httpproxy::httpproxy(int port, int cache, int cache_size) {
    this->port = port;
    this->cache_size = cache;
    this->max_cache_size = cache_size;
    
    this->cache.resize(this->cache_size);
}

void httpproxy::handle_connection() {
	this->setup_request();
}

void httpproxy::setup_request() {
	int n;
	while((n = read(connfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		//if end of message, break out of loop
		if(recvline[n - 1] == '\n') {
			break;
		}
	}
	if(n < 0) {
		err_n_die(READERR);
	}
	std::cout << recvline << std::endl;
	this->parse_request();
}

void httpproxy::parse_request() {
	int status_code;
	buffer = new char[MAXLINE];
	
	status_code = check_method();
	if(status_code == 405) {
		this->send_405();
	}
	
	status_code = create_request();
}

int httpproxy::check_method() {
	char *request = new char[strlen(recvline)];
	memcpy(request, recvline, strlen(recvline));
	char *destination;
	char *tok = strtok_r(request, "\r\n", &request);
	
	if(strncmp(tok, "GET", 3) == 0 || strncmp(tok, "HEAD", 4) == 0 || strncmp(tok, "POST", 4) == 0) {
		memcpy(buffer, tok, strlen(tok));
		strcat(buffer, "\r\n");
		tok = strtok_r(tok, " ", &destination);
		destination = strtok_r(NULL, " ", &destination);
		
		address = new char[strlen(destination)];
		if(strncmp(destination, "/", 1) == 0) {
			strcpy(address, destination + 1);
		} else {
			strcpy(address, destination);
		}
		
		return 200;
	}
	
	return 405;
}

int httpproxy::create_request() {
	char *request = new char[strlen(recvline)];
	memcpy(request, recvline, strlen(recvline));
	
	char *tok = strtok_r(request, "\r\n", &request);
	while(tok != NULL) {
		if(strncmp(tok, "Host:", 5) == 0) {
			strcat(buffer, tok);
			strcat(buffer, "\r\n");
		}
		if(strncmp(tok, "User-Agent:", 11) == 0) {
			strcat(buffer, tok);
			strcat(buffer, "\r\n");
		}
		if(strncmp(tok, "Accept", 6) == 0) {
			strcat(buffer, tok);
			strcat(buffer, "\r\n");
		}
		
		tok = strtok_r(NULL, "\r\n", &request);
	}
	
	//Add the via header
	strcat(buffer, "Via: 1.1 "); //ADD THE REST OF THE VIA HERE!

	//std::cout << buffer << std::endl;
	return 200;
}

void httpproxy::send_405() {
	
	exit(1);
}