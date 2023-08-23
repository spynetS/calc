#include <iostream>
#include <vector>
#include <stack>

bool contains(std::vector<std::string> v, std::string x);

float pop_return(std::stack<float> *stack);
std::vector<std::string> stack_to_vector(std::stack<std::string> stack);
std::vector<std::string> split(std::string str,char ch);
void log_stack(std::stack<std::string> stack);

extern std::vector<std::string> math_operators;
