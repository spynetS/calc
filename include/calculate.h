#include <iostream>
#include <vector>
#include <map>

class Function{
public:
	std::vector<std::string> variables; // the arguments for the function
	std::vector<std::string> expression; // the defintion of the function

};

class Calculator{
public:
	Calculator();

	float calculate_posfix(std::vector<std::string> splited);
	float calculate_posfix(std::string expretion);

	float calculate(std::string expretion);

	// function that 
	void parse();
	
	//posfix part
	int op_value(std::string op);
	std::string space_it(std::string str);
	std::vector<std::string> to_posfix(std::string infix);
	void graph();
private:
	std::vector<std::string> replace_variable(std::vector<std::string> splited, std::map<std::string,float> variables);
	std::map<std::string, float> variables;
	std::map<std::string, Function> functions;
	std::vector<std::string> operators;
};





