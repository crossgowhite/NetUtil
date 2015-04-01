#include "arch/ArchConsoleStd.h"
#include <iostream>

void ArchConsoleStd::writeConsole(ELevel level,const char* str)
{
	if ((level >= kFATAL) && (level <= kWARNING))
		std::cerr << str << std::endl;
	else
		std::cout << str << std::endl;

	std::cout.flush();
}