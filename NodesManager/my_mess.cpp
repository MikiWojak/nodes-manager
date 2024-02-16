#include <iostream>
#include "my_mess.h"

using namespace std;
using namespace ENUM_MY_MESSAGE;

char* my_mess::strtab[] =
{
	"E Memory allocation error",				//ERR_ALLOC_MEM
	"E Access data error",						//ERR_ACCESS_DATA
	"E Open file error",						//ERR_OPEN_FILE
	"E Read file error",						//ERR_READ_FILE
	"E Write file error",						//ERR_WRITE_FILE
	"W Array is full",							//WARN_ARR_FULL
	"W Array is empty",							//WARN_ARR_EMPT
	"W Invalid operation",						//WARN_ARR_UNKN
	"W Not implemented in current version",		//WARN_NOT_IMPLEMENTED
	"M Start program",							//MESS_START_PROGRAM
	"M Finish program",							//MESS_FINISH_PROGRAM
	"M All records are cleared",				//MESS_CLEAR_ALL
	"M Record pushed",							//MESS_PUSH
	"M Record erased",							//MESS_ERASE
	"M Record edited",							//MESS_EDIT
	"M Refords saved to binary file",			//MESS_SAVE_BIN
	"M Refords read from binary file"			//MESS_READ_BIN
};

my_mess::my_mess(enum ENUM_MY_MESSAGE::MY_MESSAGE ms) 
{
	pos = ms;

	if (strtab[ms][0] == 'E')
		throw* this;
	else
		mess();
}

void my_mess::mess()
{
	if (strtab[pos][0] == 'E')
	{
		cout << "ERROR: " << &strtab[pos][1] << "\n";
	}
	else if (strtab[pos][0] == 'W')
	{
		cout << "WARNING: " << &strtab[pos][1] << "\n";
	}
	else if (strtab[pos][0] == 'M')
	{
		cout << "MESSAGE: " << &strtab[pos][1] << "\n";
	}
}
