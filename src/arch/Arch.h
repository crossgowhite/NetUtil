#pragma once

#include "arch/ArchNetWork.h"
#include "arch/ArchConsoleStd.h"

#define ARCH (Arch::getInstance())

class Arch : public ArchNetWork,
			 public ArchConsoleStd
{
private:
	Arch(){}
	virtual ~Arch(){}

public:
	static Arch * getInstance();

private:
	static Arch * __instance;
};