#include<iostream>
#include<ctime>
#include"HashTable\Hasher.h"
#include"HashTable\HashMap.h"

#include"OOP_Architecture\Product.h"
using std::cout;
using std::endl;

void Test1();
void Test2();
int main()
{
	srand(time(0));
	//Test1();
	Test2();

	system("pause");
	return 0;
}

void Test1()
{
	Product p9, p10, p11, p12, p13;
	Map<Product, int> mp;
	mp.Insert(p9, 9);
	mp.Insert(p10, 10);
	mp.Insert(p11, 11);
	mp.Insert(p12, 12);
	mp.Insert(p13, 13);
	cout << mp.Get(p9) << endl;
	cout << mp.Get(p10) << endl;
	cout << mp.Get(p11) << endl;
	cout << mp.Get(p12) << endl;
	cout << mp.Get(p13) << endl;
}

void Test2()
{
	Map<int,int> mp;
	for (int i = 0; i < 15; i++)
		mp.Insert(rand(), i);
	mp.show();
	for (int i = 1; i < 55; i++)
		cout << mp.Get(i) << "\n";
	for (int i = 1; i < 55; i++)
		mp.Delete(i);
	mp.show();
}