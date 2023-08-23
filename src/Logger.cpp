#include "../include/logger.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>

FILE *Logger::file = stdout;

void Logger::log(std::string value){
    fprintf(Logger::file,"%s",value.c_str());
}
void Logger::log(float value){
    fprintf(Logger::file,"%f",value);
}
void Logger::logl(float value){
    fprintf(Logger::file,"%f\n",value);
}
void Logger::logl(std::string value){
    fprintf(Logger::file,"%s\n",value.c_str());
}

void log_vector(std::vector<std::string> bec){
	for(int i = 0; i < bec.size(); i ++){
		Logger::log(bec[i]);
	}
	Logger::log("\n");
}
void log_stack(std::stack<std::string> stack){
	std::vector<std::string> s;
	
	while(stack.size() > 0){
		s.insert(s.begin(),stack.top());
		stack.pop();
	}
	log_vector(s);
	Logger::log("\n");
}
