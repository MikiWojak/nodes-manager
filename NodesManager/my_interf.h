#pragma once

#include "my_vect.h"
#include "node.h"
#include "my_mess.h"

namespace ENUM_MY_INTERF
{
	enum MY_INTERF
	{
		MY_INTERF_PUSH,
		MY_INTERF_POP,
		MY_INTERF_ERASE,
		MY_INTERF_CLEAR_ALL,
		MY_INTERF_EDIT,
		MY_INTERF_FIND_ALL,
		MY_INTERF_SAVE_BIN,
		MY_INTERF_READ_BIN,
		MY_INTERF_DISPLAY,
		MY_INTERF_FINISH,
		MY_INTERF_TOTAL
	};
}

class my_interf
{
private:
	my_vect<node> vect;
	static char* str_interf[ENUM_MY_INTERF::MY_INTERF_TOTAL];
public:
	bool run;
	my_interf(size_t dim, char* f_name_bin);
	void menu();
	void push();
	void pop();
	void erase();
	void clear_all();
	void edit();
	void find_all();
	void save_bin();
	void read_bin();
	void display();
	void finish();
	void defaul();
};
