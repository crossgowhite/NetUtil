#include "arch/Arch.h"


Arch * Arch::__instance = NULL;

Arch * Arch::getInstance()
{
	if(__instance == NULL){
		__instance = new Arch();
		__instance->init();
	}
	return __instance;
}

