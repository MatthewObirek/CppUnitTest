#pragma once
#include <iostream>
#include <stdlib.h>

#define DEBUG true

#ifdef DEBUG
#define Log(x) std::cout << x << std::endl 
#else
#define Log(x)
#endif