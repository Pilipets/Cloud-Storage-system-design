#pragma once
#include<initializer_list>
using std::initializer_list;
class Product;
class Branch
{
	Product** items;
	int size;
	const char *name;
	size_t id;
public:
	bool operator ==(const Branch& obj);
	Branch();
	Branch(const char* name, const initializer_list<Product*>& items);

	~Branch();
};