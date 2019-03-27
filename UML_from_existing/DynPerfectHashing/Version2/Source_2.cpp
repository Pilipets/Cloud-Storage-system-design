#include<iostream>
#include<ctime>
#include"HashTable\HashMap.h"
#include<random>
#include<string>
using std::cout;
using std::endl;

int main()
{
	MINE_STL::Map<int, int> mp;
	for (int i = 0; i < 150; i++)
		mp.Insert(rand(), i);
	mp.show();
	for (int i = 1; i < 55; i++)
		cout << mp.Get(i) << "\n";
	for (int i = 1; i < 55; i++)
		mp.Delete(i);
	mp.show();

	system("pause");
	return 0;
}
