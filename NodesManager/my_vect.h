#pragma once
#include <fstream>
#include "my_mess.h"
#include "find.h"
#include "windows.h"
using namespace std;

template <class T> class my_vect
{
	T* dat;
	size_t ndim;
	size_t last;

	fstream flbin;
	char filenamebin[MAX_PATH];

public:
	my_vect() { dat = NULL; ndim = last = 0; }
	my_vect(size_t dim, char* f_name_bin);
	~my_vect();
	void init(size_t dm, char* f_name_bin);

	T* get_begin() { return dat; }
	T* get_end();

	void push(const T& ob);
	T* pop();
	void erase(const T* ob);

	void clear_all();
	T & operator [] (size_t it);
	fstream& get_file() { return flbin; }
	friend ostream& operator << <>(ostream& strm, const my_vect<T>& ob);
	friend fstream& operator << <>(fstream& flbin, const my_vect<T>& ob);
	friend fstream& operator >> <>(fstream& flbin, my_vect<T>& ob);

private:
	void realloc();
	void open_file(char* file_name_bin);
};

template <class T>
my_vect<T>::my_vect(size_t dim, char* f_name_bin)
{
	ndim = dim;

	try
	{
		dat = new T[ndim];
	}
	catch (std::bad_alloc)
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_ALLOC_MEM);
	}

	last = 0;

	open_file(f_name_bin);
}

template <class T>
my_vect<T>::~my_vect()
{
	if (dat) 
	{
		delete[] dat;
	}

	if (flbin.is_open())
	{
		flbin.close();
	}
}

template <class T>
void my_vect<T>::init(size_t dm, char* f_name_bin)
{
	if (dat) return;

	ndim = dm;

	try
	{
		dat = new T[ndim];
	}
	catch (std::bad_alloc)
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_ALLOC_MEM);
	}

	open_file(f_name_bin);
}

template <class T>
T* my_vect<T>::get_end()
{
	if (dat)
	{
		return &dat[last];
	}
	else
	{
		return NULL;
	}
}

template <class T>
void my_vect<T>::push(const T& ob)
{
	realloc();
	dat[last] = ob;
	last++;
}

template <class T>
T* my_vect<T>::pop()
{
	if (last > 0)
	{
		last--;

		return &dat[last];
	}
	else
	{
		my_mess warning(ENUM_MY_MESSAGE::WARN_ARR_EMPT);

		return NULL;
	}
}

template <class T>
void my_vect<T>::erase(const T* ob)
{
	size_t dist;
	node* ptr = get_begin();
	node* ptr_end = get_end();

	ptr = ::find(ptr, ptr_end, *ob);
	if (ptr)
	{
		dist = ptr - get_begin();
	}
	else
	{
		return;
	}

	for (size_t i = dist; i < last - 1; i++)
	{
		dat[i] = dat[i + 1];
	}

	last--;

	my_mess msg(ENUM_MY_MESSAGE::MESS_ERASE);
}

template <class T>
void my_vect<T>::clear_all()
{
	last = 0;
}

template <class T>
T& my_vect<T>::operator [] (size_t it)
{
#ifdef _DEBUG
	if (!dat || it < 0 || it >= last)
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_ACCESS_DATA);
	}
#endif

	return dat[it];
}

template <class T>
void my_vect<T>::realloc()
{
	try
	{
		if (last >= ndim)
		{
			T* new_dat = new T[2 * ndim];
			std::copy(get_begin(), get_end(), new_dat);

			delete[] dat;
			dat = new_dat;
			ndim *= 2;
		}
	}
	catch (std::bad_alloc)
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_ALLOC_MEM);
	}
}

template <class T>
void my_vect<T>::open_file(char* file_name_bin)
{
	//Open file
	sprintf_s(filenamebin, sizeof(filenamebin), file_name_bin);

	char pathbuffer[_MAX_PATH];
	_searchenv(filenamebin, "PATH", pathbuffer);

	if (pathbuffer[0] == '\0')
	{
		// File does not exist
		ofstream tmpfl(filenamebin);
		tmpfl.close();
	}

	// File must be opened
	flbin.open(filenamebin, ios_base::in | ios_base::out | ios_base::binary);

	if (!flbin.is_open())
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_OPEN_FILE);
	}
}

template <class T>
ostream& operator << <>(ostream& strm, const my_vect<T>& ob)
{
	for (size_t i = 0; i < ob.last; i++)
	{
		strm << "it = " << i << " " << ob.dat[i] << "\n";
	}

	return strm;
}

template <class T>
fstream& operator << <>(fstream& flbin, const my_vect<T>& ob)
{
	size_t it;
	flbin.clear();
	flbin.close();
	flbin.open(ob.filenamebin, ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary);
	if (!flbin.is_open())
	{
		my_mess exc(ENUM_MY_MESSAGE::ERR_OPEN_FILE);
	}

	for (it = 0; it < ob.last; it++)
	{
		flbin << &ob.dat[it];

		if (flbin.bad() || flbin.fail())
		{
			my_mess exc(ENUM_MY_MESSAGE::ERR_WRITE_FILE);
		}
	}

	return flbin;
}

template <class T>
fstream& operator >> <>(fstream& flbin, my_vect<T>& ob)
{
	ob.last = 0;
	T tmp;

	flbin.clear();
	flbin.seekg(0);

	while (!flbin.eof())
	{
		flbin >> &tmp;

		if (flbin.bad())
		{
			my_mess exc(ENUM_MY_MESSAGE::ERR_READ_FILE);
		}

		if (flbin.eof())
		{
			break;
		}

		ob.push(tmp);
	}

	return flbin;
}
