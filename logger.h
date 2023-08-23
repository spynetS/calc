#include <iostream>

class Logger{

public:
	Logger();
	Logger(const std::string filename);
	~Logger();
	
	void log(std::string value);
	void log(float value);
	void logl(std::string value);
	void logl(float value);
	void log_error();
	FILE *file;
};
