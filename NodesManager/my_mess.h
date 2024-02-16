#pragma once

namespace ENUM_MY_MESSAGE
{
	enum MY_MESSAGE
	{
		ERR_ALLOC_MEM,			//memory allocation error
		ERR_ACCESS_DATA,		//invalid index, etc
		ERR_OPEN_FILE,			
		ERR_READ_FILE,
		ERR_WRITE_FILE,
		WARN_ARR_FULL,			//array is full (last > ndim)
		WARN_ARR_EMPT,			//array is empty (last = 0)
		WARN_ARR_UNKN,			//invalid operation (interface)
		WARN_NOT_IMPLEMENTED,	//invalid operation (interface)
		MESS_START_PROGRAM,		//finishing program
		MESS_FINISH,			//finishing program
		MESS_CLEAR_ALL,			//clear all
		MESS_PUSH,
		MESS_ERASE,
		MESS_EDIT,
		MESS_SAVE_BIN,
		MESS_READ_BIN,
		TOT_NUMB				//total number of messages
	};
};

class my_mess
{
	ENUM_MY_MESSAGE::MY_MESSAGE pos;
	static char* strtab[ENUM_MY_MESSAGE::TOT_NUMB];
public:
	my_mess(enum ENUM_MY_MESSAGE::MY_MESSAGE ms);
	void mess();
};
