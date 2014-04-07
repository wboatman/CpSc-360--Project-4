//
//  common.cpp
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "common.h"

void err_n_die(int error) {
    switch (error) {
        case BADARGS:
            std::cout << "Incorrect Server Usage." << std::endl;
            std::cout << "./httpproxy -p <port> -n <cache slots> -s <max cache size>" << std::endl;
            break;
        case SOCKERR:
        	std::cout << "Error setting up socket!" << std::endl;
        	std::cout << "Please try the request again." << std::endl;
        case BINDERR:
        	std::cout << "Error binding to socket!" << std::endl;
        	std::cout << "Please try the request again using a different port." << std::endl;
        case LISTERR:
        	std::cout << "Error listening for connections!" << std::endl;
        	std::cout << "Please try the request again, try using a different port." << std::endl;
        case RECVERR:
        	std::cout << "Error receiving response!" << std::endl;
        	std::cout << "Please try your request again." << std::endl;
        case READERR:
        	std::cout << "Error reading request/response!" << std::endl;
        	std::cout << "Please try the request again." << std::endl;
    }
    exit(1);
}