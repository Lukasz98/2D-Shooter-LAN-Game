#pragma once
#include <iostream>

#define LOG(x) std::cout << x << std::endl

inline void LOGG(const char * _text)
{
	std::cout << _text << std::endl;
}