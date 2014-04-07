//
//  common.h
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CONNECTIONS 1024
#define MAXLINE 		4098

#define BADARGS -1
#define SOCKERR -2
#define BINDERR -3
#define LISTERR -4
#define RECVERR -5
#define READERR -6

void err_n_die(int error);

#endif
