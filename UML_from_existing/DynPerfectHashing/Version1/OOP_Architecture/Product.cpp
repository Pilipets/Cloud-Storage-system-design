#include "Product.h"
#include<cstdlib>
#include <string>
using std::memcpy;
int Product::amount = 0;
Product::Product()
{
	++amount;
	this->name = "Default name";
	this->id = rand() % static_cast<int>(1e5) + 1e4;
	this->quantity = rand() % 20;
	this->rating = (1 + rand() % 500) / 100.0;
}

Product::Product(size_t id)
{
	this->id = id;
	this->rating = 0;
	this->quantity = 0;
	this->name = "";
}

Product::Product(const char* brand, const char * name, int condition, double price,
	const char * description) : Product()
{
	this->brand = brand;
	this->name = name;
	this->condition = ProductCondition(condition);
	this->price = price;
	this->desription = description;
}

Product::Product(const Product & obj)
{
	this->brand = obj.brand;
	this->name = obj.name;
	this->condition = obj.condition;
	this->price = obj.price;
	this->desription = obj.desription;
	this->id = obj.id;
	this->quantity = obj.quantity;
	this->rating = obj.rating;
}

std::ostream & operator<<(std::ostream& os, const Product & obj)
{
	os << "{Name=" << obj.name << ":id=" << obj.id << "}";
	return os;
}

//std::ofstream & operator<<(std::ofstream &fout, const Product & obj)
//{
//	fout << "<p>" << &obj << "|<name>" << obj.name << "|<id>";
//	fout << obj.id << "\"";
//	return fout;
//}


bool Product::operator==(const Product & obj)
{
	return (this->name == obj.name && this->id == obj.id);
}

Product::~Product()
{
}
