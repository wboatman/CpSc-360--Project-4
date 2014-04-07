//
//  proxy.h
//  Project 4
//
//  Created by William Boatman on 4/1/14.
//  Copyright (c) 2014 William Boatman. All rights reserved.
//

#include "httpproxy.h"

class proxy: public httpproxy {
  private:
  	
  	
  public:
    proxy() : httpproxy() {   }
	proxy(int p, int n, int s) : httpproxy(p, n, s) {   }
	~proxy() {    }
	
	//void initialize();
	
};