#include "logger.hpp"


void Logger::log(const char* string)
{
    std::cout<<string;
}

void Logger::log(int digit)
{
    std::cout<<digit;
}
