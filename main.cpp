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
#include <algorithm>
#include "logger.h"
#include <stdio.h>

const char SPLITCHAR = ' ';
Logger l;

std::vector<std::string> operators = {
	"+",
	"-",
	"*",
	"/",
};

std::vector<std::string> split(std::string str,char ch){
	std::vector<std::string> splits;
	std::string temp;
	for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if(*it == ch){
			splits.push_back(temp);
			temp = "";
		}
		else{
			temp += *it;
		}
	}
	splits.push_back(temp);
	return splits;
}

bool contains(std::vector<std::string> v, std::string x){
	return(std::find(v.begin(), v.end(), x) != v.end());
}

float pop_return(std::stack<float> *stack){
	float r = stack->top();
	stack->pop();

	return r;
}
void log_vector(std::vector<std::string> bec){
	for(int i = 0; i < bec.size(); i ++){
		l.log(bec[i]);
	}
	l.log("\n");
}

std::vector<std::string> stack_to_vector(std::stack<std::string> stack){
	std::vector<std::string> vec;
	while(stack.size() > 0){
		vec.insert(vec.begin(), stack.top());
		stack.pop();
	}
	return vec;
}


float calculate(std::vector<std::string> splited){
	log_vector(splited);
	std::stack<float> stack;
	for(int i = 0; i < splited.size();i++){
		std::string ch = splited[i];
		//it is operator
		if(contains(operators, ch)){

			float b = pop_return(&stack);
			float a = pop_return(&stack);

			l.log(a);
			l.log(ch);
			l.log(b);
			l.log("=");

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
float calculate(std::string expretion){
	std::vector<std::string> splited = split(expretion, SPLITCHAR);
	log_vector(splited);
	return calculate(splited);
}

int op_value(std::string op){
	if(op == "+") return 0;
	if(op == "-") return 0;
	if(op == "*") return 1;
	if(op == "/") return 1;

	return -1;
}

std::string space_it(std::string str){
	std::string newStr;
	for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
		std::string temp;
		temp += *it;
		// it is a operator (2+2)/(5/2)
		if(contains(operators, temp)){
			newStr += " ";
			newStr += *it;
			newStr += " ";
		}
		else if (temp == "("){
			newStr += *it;
			newStr += " ";
		}
		else if (temp == ")"){
			newStr += " ";
			newStr += *it;
		}
		else{
			newStr += *it;
		}
	}
	return newStr;
}

void log_stack(std::stack<std::string> stack){
	std::vector<std::string> s;
	
	while(stack.size() > 0){
		s.insert(s.begin(),stack.top());
		stack.pop();
	}
	log_vector(s);
	l.log("\n");
}


std::vector<std::string> to_posfix(std::string infix){

	std::vector<std::string> splited = split(space_it(infix),SPLITCHAR);
	std::stack<std::string> output_stack;
	std::stack<std::string> operator_stack;

	for(int i = 0; i < splited.size(); i++){
		std::string read = splited[i];
		//if closing breaket pop all till (
		if(read == ")"){
			l.logl("read ) pop all untill ( ");	
			while(operator_stack.size() > 0 && operator_stack.top() != "("){
				l.logl("pop "+ operator_stack.top()+"\n");
				output_stack.push(operator_stack.top());
				operator_stack.pop();
			}
			operator_stack.pop();
			continue;
		}

		if(contains(operators, read)){
			if(operator_stack.size() > 0 && op_value(read) <= op_value(operator_stack.top())){
				l.logl("read '"+read+"' has heigher so pop them");
			}
			else{
				l.logl("read '"+read+"' push top operator");
			}
			while(operator_stack.size() > 0 && 
				op_value(read) <= op_value(operator_stack.top()))
			{
				// we dont want to push the ( to the output
				if(operator_stack.top() != "("){
					output_stack.push(operator_stack.top());
					operator_stack.pop();
				}
			}
			operator_stack.push(read);
		}
		else if(read == "("){
			l.logl("read '"+read+"' push to operators");
			operator_stack.push(read);
		}
		else{
			l.logl("read '"+read+"' push to output");
			output_stack.push(read);
		}

		l.log("Output:");
		log_stack(output_stack);
		l.log("Operator:");
		log_stack(operator_stack);
	}

	//pop last operators 
	while(operator_stack.size() > 0){
		output_stack.push(operator_stack.top());
		operator_stack.pop();
	}
	log_stack(output_stack);

	std::vector<std::string> s = stack_to_vector(output_stack);

	return s;	
}
int main(int argc, char** argv){

	l.file = fopen("test.txt", "w");
	std::cout<<calculate(to_posfix(argv[1]));

	return 0;
}
