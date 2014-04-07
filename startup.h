//
//  startup.h
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "httpproxy.h"

class startup: public httpproxy {
  private:
	void setup_socket();
  	void wait_for_connection();
  	void disperse_connection();
  
  public:
	startup() : httpproxy() {   }
	startup(int p, int n, int s) : httpproxy(p, n, s) {   }
	~startup() {   }
	
	void initialize();
};