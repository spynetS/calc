#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include <stack>
#include <regex>
#include "../include/Canvas.h"

#include "../include/logger.h"
#include "../include/calculate.h"
#include "../include/msc.h"



Calculator::Calculator(){
	this->operators = math_operators;
}

void Calculator::graph(){
	const char* bg = "##";
	const char* c  = "";
	Canvas *canvas = newCanvas(10,10,bg,c,c);
	draw(canvas);

}

void Calculator::parse(){
	// regex for function "name(arg1,...)"
    std::regex pattern("^([a-zA-Z_][a-zA-Z0-9_]*)\\(([^)]*)\\)$");
    std::smatch matches;

	while(1){
		std::cout<< "q to exit \n>" ;
		
		std::string expresion;
		std::getline(std::cin,expresion);
		expresion = removeSpaces(expresion);
			
		if(expresion == "q" || expresion == "exit") exit(0);
		
		// function defintion
		if (std::regex_match(split(expresion,'=')[0], matches, pattern) && expresion.find("=") != std::string::npos ) {

			// get the functin args
			std::string argsStr = split(split(expresion, '(')[1],')')[0];
			std::vector<std::string> args = split(argsStr,',');

			//create a new function
			Function f;
			f.variables = args;
			f.expression = to_posfix(split(expresion,'=')[1]);

			std::string fname = split(expresion,'(')[0];
			//save function to calculator list
			this->functions[fname] = f;
		}
		//function call
		else if (std::regex_match(split(expresion,'=')[0], matches, pattern)) {

			
			std::string fname = split(expresion,'(')[0];
			Function f = this->functions[fname];

			//get the arguments for the functions
			std::string argsStr = split(expresion, '(')[1];
			argsStr.pop_back();//remove last char it is )
			std::vector<std::string> args = split(argsStr,',');
			// create a variable map
			std::map<std::string, float> variables;
			// set name to value 
			for(int i = 0; i < args.size(); i ++){
				std::cout<< calculate(args[i]);
				variables[f.variables[i]] = calculate(args[i]);
			}


			std::cout<< calculate_posfix(replace_variable(f.expression, variables)) <<std::endl;
		}
		// set variable
		else if (expresion.find("=") != std::string::npos) {
			std::vector<std::string> m = split(expresion,'=');
			Logger::logl("Set variable "+m[1]);

			variables[m[0]] = calculate(m[1]);

			std::cout<< m[0] + " was set to ";
			std::cout << variables[m[0]] << std::endl;


		}
		//calcualate expresion
		else{
			Logger::log("Calculate expresion");
			std::cout << "=";
			std::cout<< calculate_posfix(this->to_posfix(expresion)) << std::endl;
		}
	}
}
std::vector<std::string> Calculator::replace_variable(std::vector<std::string> splited, std::map<std::string,float> variables){
	for(int i = 0; i < splited.size(); i ++){
		std::map<std::string, float>::iterator it;

		if (variables.find((splited)[i]) != variables.end()){
			Logger::log("replace variable " +(splited)[i]);
			(splited)[i] = std::to_string(variables[(splited)[i]]);
			Logger::logl(" to " + (splited)[i]);
		}
	}
	return splited;
}

float Calculator::calculate_posfix(std::vector<std::string> splited){
	log_vector(splited);
	std::stack<float> stack;
	
	splited = replace_variable(splited, variables);

	log_vector(splited);

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
float Calculator::calculate_posfix(std::string expretion){
	std::vector<std::string> splited = split(expretion, ' ');
	log_vector(splited);
	return this->calculate_posfix(splited);
}
int Calculator::op_value(std::string op){
	if(op == "+") return 0;
	if(op == "-") return 0;
	if(op == "*") return 1;
	if(op == "/") return 1;

	return -1;
}

std::string Calculator::space_it(std::string str){
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



std::vector<std::string> Calculator::to_posfix(std::string infix){

	std::vector<std::string> splited = split(space_it(infix),' ');
	std::stack<std::string> output_stack;
	std::stack<std::string> operator_stack;

	for(int i = 0; i < splited.size(); i++){
		std::string read = splited[i];
		//if closing breaket pop all till (
		if(read == ")"){
			Logger::logl("read ) pop all untill ( ");	
			while(operator_stack.size() > 0 && operator_stack.top() != "("){
				Logger::logl("pop "+ operator_stack.top()+"\n");
				output_stack.push(operator_stack.top());
				operator_stack.pop();
			}
			operator_stack.pop();
			continue;
		}

		if(contains(this->operators, read)){
			if(operator_stack.size() > 0 && op_value(read) <= op_value(operator_stack.top())){
				Logger::logl("read '"+read+"' has heigher so pop them");
			}
			else{
				Logger::logl("read '"+read+"' push top operator");
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
			Logger::logl("read '"+read+"' push to operators");
			operator_stack.push(read);
		}
		else{
			Logger::logl("read '"+read+"' push to output");
			output_stack.push(read);
		}

		Logger::log("Output:");
		log_stack(output_stack);
		Logger::log("Operator:");
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

float Calculator::calculate(std::string expretion){
	return calculate_posfix(to_posfix(expretion));
}

