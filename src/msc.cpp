#include "../include/msc.h"
#include <algorithm>
#include <vector>

std::vector<std::string> math_operators = {
	"+",
	"-",
	"*",
	"/",
};
bool contains(std::vector<std::string> v, std::string x){
	return(std::find(v.begin(), v.end(), x) != v.end());
}

std::vector<std::string> stack_to_vector(std::stack<std::string> stack){
	std::vector<std::string> vec;
	while(stack.size() > 0){
		vec.insert(vec.begin(), stack.top());
		stack.pop();
	}
	return vec;
}

float pop_return(std::stack<float> *stack){
	float r = stack->top();
	stack->pop();

	return r;
}
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
