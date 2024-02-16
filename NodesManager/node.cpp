#include <iostream>
#include <fstream>
#include "node.h"
#include "my_mess.h"
using namespace std;

node::node(int nb, char* st, double xx, double yy)
	: mcoord(xx, yy)
{
	numb = nb;
	strcpy_s(str, sizeof(str), st);
}

node::node() : mcoord()
{
	numb = 0;
	strcpy_s(str, sizeof(str), "");
}

node & node::operator = (const node& ob)
{
	x = ob.x;
	y = ob.y;

	numb = ob.numb;
	strcpy_s(str, sizeof(str), ob.str);

	return *this;
}

node::node(const node& ob)
{
	x = ob.x;
	y = ob.y;

	numb = ob.numb;
	strcpy_s(str, sizeof(str), ob.str);
}

int node::operator == (const char* str_comp) const
{
	return !strcmp(str, str_comp);
}

int node::operator == (const node& ob) const
{
	return (fabs(x - ob.x) < 1e-10 && fabs(y - ob.y) < 1e-10 && numb == ob.numb && !strcmp(str, ob.str));
}

ostream& operator << (ostream& strm, const node& ob)
{
	strm << "numb = " << ob.numb << " str = " << ob.str << " x = " << ob.x << " y = " << ob.y;

	return strm;
}

istream& operator >> (istream& strm, node& ob)
{
	cout << "Input numb: ";
	strm >> ob.numb;
	cout << "Input str: ";
	strm.ignore();
	strm.getline(&ob.str[0], 512, '\n');
	cout << "Input x, y: ";
	strm >> ob.x >> ob.y;

	return strm;
}

fstream& operator << (fstream& strm, const node* ob)
{
	__int64 pos = strm.tellp();
	streamsize numbytestowrite = static_cast<streamsize>(sizeof(node));
	strm.write(reinterpret_cast<const char*>(ob), numbytestowrite);

	if (strm.bad() || strm.fail())
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_WRITE_FILE);
	}

	__int64 offset = strm.tellp() - pos;

	if(numbytestowrite != offset)
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_WRITE_FILE);
	}

	return strm;
}

fstream& operator >> (fstream& strm, node* ob)
{
	streamsize numbytestoread = static_cast<streamsize>(sizeof(node));
	strm.read(reinterpret_cast<char*>(ob), numbytestoread);

	return strm;
}
