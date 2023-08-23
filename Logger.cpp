#include "logger.h"
#include <string>
#include <stdio.h>

Logger::Logger(){
    this->file = stdout;
}
Logger::Logger(const std::string filename){
    this->file = fopen(filename.c_str(), "w");
}

Logger::~Logger() {
    fclose(file);
}

void Logger::log(std::string value){
    fprintf(this->file,"%s",value.c_str());
}
void Logger::log(float value){
    fprintf(this->file,"%f",value);
}
void Logger::logl(float value){
    fprintf(this->file,"%f\n",value);
}
void Logger::logl(std::string value){
    fprintf(this->file,"%s\n",value.c_str());
}
