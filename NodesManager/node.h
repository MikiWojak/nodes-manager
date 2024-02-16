#pragma once

#include "mcoord.h"

class node : public mcoord
{
	int numb;
	char str[512];
public:
	node(int nb, char* st, double xx, double yy);
	node();
	~node() { };
	node& operator = (const node& ob);
	node(const node& ob);
	int operator == (const char* str_comp) const;
	int operator == (const node& ob) const;
	friend std::ostream& operator << (std::ostream& strm, const node& ob);
	friend std::istream& operator >> (std::istream& strm, node& ob);
	friend std::fstream& operator << (std::fstream& strm, const node* ob);
	friend std::fstream& operator >> (std::fstream& strm, node* ob);
};
