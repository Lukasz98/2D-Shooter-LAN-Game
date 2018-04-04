#pragma once
#include <iostream>

//#define LOG(x) std::cout << __FILE__ << " line: " << __LINE__ << " " << x << std::endl;
#define LOG(x) std::cout << x << " [" << __FILE__ << " line: " << __LINE__ << "]" << std::endl;

//#define LOG(x) std::cout << x << std::endl
//#define LOG(x) std::cout << __FILE__ << " " << __FUNCTION__  << " " << __LINE__ << " " << x << std::endl;
