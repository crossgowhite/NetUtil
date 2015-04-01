#pragma once

//! ArchNetWork.h
/*!
Target to Split the WIN32/UNIX socket implement
*/


#include <string>
typedef std::string String;

#include "net/INetWork.h"

#ifdef WIN32 

//if WIN32 Platform
#include "platform/win32/NetWorkWin.h"
#include "platform/win32/NetAddressImpl.h"



//elif UNIX Platform
#elif UNIX

#endif




