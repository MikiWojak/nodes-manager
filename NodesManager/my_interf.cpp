#include <iostream>
#include "my_interf.h"
#include "find.h"

using namespace std;
using namespace ENUM_MY_INTERF;
using namespace ENUM_MY_MESSAGE;

char* my_interf::str_interf[] = 
{
	"0 - Push",
	"1 - Pop",
	"2 - Erase",
	"3 - Clear all",
	"4 - Edit",
	"5 - Find all",
	"6 - Save",
	"7 - Read",
	"8 - Display",
	"9 - Finish"
};

my_interf::my_interf(size_t dim, char* f_name_bin)
{
	my_mess msg(MESS_START_PROGRAM);

	vect.init(dim, f_name_bin);
	run = true;
}

void my_interf::menu()
{
	cout << "Menu:\n";
	for (int i = 0; i < MY_INTERF_TOTAL; i++)
	{
		cout << str_interf[i] << "\n";
	}
}

void my_interf::push()
{
	node ob;
	cin >> ob;
	vect.push(ob);

	my_mess msg(MESS_PUSH);
}

void my_interf::pop()
{
	node* ptr_ob = vect.pop();

	if (ptr_ob)
	{
		cout << "Popped record:\n";
		cout << *ptr_ob << "\n";
	}
}

void my_interf::erase()
{
	display();

	size_t index;
	cout << "Input it of node to erase: ";
	cin >> index;

	vect.erase(&vect[index]);
}

void my_interf::clear_all()
{
	vect.clear_all();

	my_mess msg(MESS_CLEAR_ALL);
}

void my_interf::edit()
{
	display();

	size_t index;
	cout << "Input it of node to edit: ";
	cin >> index;

	node ob;
	cin >> ob;

	vect[index] = ob;

	my_mess msg(MESS_EDIT);
}

void my_interf::find_all()
{
	char str[512];

	cout << "Enter node str: ";
	cin.ignore();
	cin.getline(&str[0], 512, '\n');

	node* ptr = vect.get_begin();
	node* ptr_end = vect.get_end();

	cout << "Found nodes:\n";
	while (ptr)
	{
		ptr = ::find(ptr, ptr_end, &str[0]);

		if (ptr)
		{
			cout << *ptr << "\n";
			ptr++;
		}
	}
}

void my_interf::save_bin()
{
	vect.get_file() << vect;
	
	my_mess msg(MESS_SAVE_BIN);
}

void my_interf::read_bin()
{
	vect.get_file() >> vect;
	
	my_mess msg(MESS_READ_BIN);
}

void my_interf::display()
{
	cout << "Nodes:\n";
	cout << vect;
}

void my_interf::finish()
{
	run = false;

	my_mess msg(MESS_FINISH);
}

void my_interf::defaul()
{
	my_mess msg(WARN_ARR_UNKN);
}
