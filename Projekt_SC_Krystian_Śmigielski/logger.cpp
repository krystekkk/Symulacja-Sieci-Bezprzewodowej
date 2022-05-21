#include "logger.h"

#include <iostream>
#include <fstream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Info(std::string message)
{
	if(level_ != Level::Error)
	{
		std::ofstream foutput;
		std::ifstream finput;
		finput.open("logger.txt");
		foutput.open("logger.txt", std::ios::app);
		std::string log = "[Info] " + message + "\n";
		if (finput.is_open())
			foutput << log;

		finput.close();
		foutput.close();

		std::cout << "[Info] " << message << std::endl;
	}
}

void Logger::Debug(std::string message)
{
	
}

void Logger::Error(std::string message)
{
	std::ofstream foutput;
	std::ifstream finput;
	finput.open("logger.txt");
	foutput.open("logger.txt", std::ios::app);
	std::string log = "[Error] " + message + "\n";
	if (finput.is_open())
		foutput << log;

	finput.close();
	foutput.close();

	std::cout << "[Error] " << message << std::endl;
}
