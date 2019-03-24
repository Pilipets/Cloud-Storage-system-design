#pragma once
#include<ostream>
#include<fstream>

class Branch;
class Product
{
public:
	enum class ProductCondition : int {
		Used, New, Refurbished
	};
private:
	static int amount;
	friend class Branch;
	Branch* department;

	const char *name;
	const char *brand;
	double price; //in USD
	const char *desription;
	ProductCondition condition;
	size_t id;

	int quantity;
	double rating;
public:
	size_t getId() const { return id; }
	Product();
	Product(size_t id);
	Product(const char* brand, const char* name, int condition, double price,
		const char *description);
	Product(const Product& obj);
	friend std::ostream& operator <<(std::ostream& os, const Product& obj);
	friend std::ofstream& operator <<(std::ofstream& fout, const Product& obj);
	bool operator ==(const Product& obj);
	~Product();
};

