#include "../include/posfix.h"
#include "../include/logger.h"
#include "../include/msc.h"

Posfix::Posfix(){
	operators = math_operators;
}

int Posfix::op_value(std::string op){
	if(op == "+") return 0;
	if(op == "-") return 0;
	if(op == "*") return 1;
	if(op == "/") return 1;

	return -1;
}

std::string Posfix::space_it(std::string str){
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



std::vector<std::string> Posfix::to_posfix(std::string infix){

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