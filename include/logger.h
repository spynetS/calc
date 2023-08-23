#include <stack>
#include <vector>
#include <iostream>

class Logger{

public:
	Logger();
	Logger(const std::string filename);
	~Logger();
	
	static void log(std::string value);
	static void log(float value);
	static void logl(std::string value);
	static void logl(float value);
	void log_error();
	static FILE *file;
};
void log_vector(std::vector<std::string> bec);
void log_stack(std::stack<std::string> stack);
