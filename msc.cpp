#include <iostream>

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
