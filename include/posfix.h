#include <iostream>
#include <vector>
#include <stack>


class Posfix{
public:
	Posfix();
	int op_value(std::string op);
	std::string space_it(std::string str);
	std::vector<std::string> to_posfix(std::string infix);
	std::vector<std::string> operators;
};

