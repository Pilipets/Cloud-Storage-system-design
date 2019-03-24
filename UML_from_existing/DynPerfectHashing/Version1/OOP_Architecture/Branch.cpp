#include "Branch.h"
#include"Product.h"
bool Branch::operator==(const Branch & obj)
{
	return this->name == obj.name && this->id == obj.id;
}

Branch::Branch()
{
	size = 0;
	this->id = rand() % static_cast<int>(1e5) + 1e4;
}

Branch::Branch(const char*name, const initializer_list<Product*>& items) : Branch()
{
	this->name = name;

	this->items = new Product*[items.size()];
	for (Product* elem : items)
	{
		elem->department = this;
		this->items[size++] = elem;
	}
}


Branch::~Branch()
{
	if (items)
	{
		delete[] items;
	}
}
