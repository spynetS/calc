#include <iostream>
#include <vector>
#include <stack>

#include "../include/logger.h"
#include "../include/calculate.h"
#include "../include/msc.h"



Calculator::Calculator(){
	this->operators = math_operators;
}

float Calculator::calculate(std::vector<std::string> splited){
	log_vector(splited);
	std::stack<float> stack;
	for(int i = 0; i < splited.size();i++){
		std::string ch = splited[i]; //it is operatormain
		if(contains(this->operators, ch)){

			float b = pop_return(&stack);
			float a = pop_return(&stack);

			Logger::log(a);
			Logger::log(ch);
			Logger::log(b);
			Logger::log("=");

			if(ch == "+") stack.push(a+b);
			if(ch == "*") stack.push(a*b);
			if(ch == "/") stack.push(a/b);
			if(ch == "-") stack.push(a-b);
			

		}
		else {
			stack.push(::atof(ch.c_str()));
		}
	}

	return stack.top();
}
float Calculator::calculate(std::string expretion){
	std::vector<std::string> splited = split(expretion, ' ');
	log_vector(splited);
	return this->calculate(splited);
}
