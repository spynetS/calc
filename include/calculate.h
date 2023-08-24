#include <iostream>
#include <vector>

class Calculator{
public:
	Calculator();
	float calculate(std::vector<std::string> splited);
	float calculate(std::string expretion);
	std::vector<std::string> operators;
	
	//posfix part
	int op_value(std::string op);
	std::string space_it(std::string str);
	std::vector<std::string> to_posfix(std::string infix);
};
