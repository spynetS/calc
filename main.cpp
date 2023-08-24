/**
*	TODO
*	modes
*		* calculate (continusly calculating)
*		* calculate with commnad
*
*
*/


#include <cstring>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>
#include <stdio.h>

#include "include/logger.h"
#include "include/calculate.h"

const char SPLITCHAR = ' ';

int main(int argc, char** argv){

	
	Logger::file = fopen("test.txt", "w");
	Calculator c;
	c.graph();

	return 0;
}
