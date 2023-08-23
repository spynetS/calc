#include <iostream>
#include <vector>

class Calculator{
public:
	Calculator();
	float calculate(std::vector<std::string> splited);
	float calculate(std::string expretion);
	std::vector<std::string> operators;
};
