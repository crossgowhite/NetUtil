#pragma once

enum ELevel {
	kPRINT = -1,	//!< For print only (no file or time)
	kFATAL,			//!< For fatal errors
	kERROR,			//!< For serious errors
	kWARNING,		//!< For minor errors and warnings
	kNOTE,			//!< For messages about notable events
	kINFO,			//!< For informational messages
	kDEBUG,			//!< For important debugging messages
	kDEBUG1,		//!< For verbosity +1 debugging messages
	kDEBUG2,		//!< For verbosity +2 debugging messages
	kDEBUG3,		//!< For verbosity +3 debugging messages
	kDEBUG4,		//!< For verbosity +4 debugging messages
	kDEBUG5			//!< For verbosity +5 debugging messages
};


class ArchConsoleStd
{
public:
	ArchConsoleStd() { }
	virtual ~ArchConsoleStd() { }

	// IArchConsole overrides
	virtual void		openConsole(const char* title) { }
	virtual void		closeConsole() { }
	virtual void		showConsole(bool) { }
	virtual void		writeConsole(ELevel level, const char*);
};