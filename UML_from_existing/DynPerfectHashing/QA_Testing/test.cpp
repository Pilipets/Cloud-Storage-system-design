#include "pch.h"

std::random_device rd;
std::mt19937 gen(rd());

TEST(LinkError, extern)
{
	MINE_STL::Hasher<int> getHashMINE;
	std::hash<int> getHashSTD;
	

	//MINE_STL2::Hasher<int> getHash2;
	//here come errors
	EXPECT_EQ(getHashMINE(0), getHashSTD(0));
}
TEST(Hasher, hashing_integers) {
	std::uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

	MINE_STL::Hasher<int> getHashMINE;
	std::hash<int> getHashSTD;
	for (int i = 0; i < 1000; ++i)
	{
		int tmp = dis(gen);
		EXPECT_EQ(getHashMINE(tmp), getHashSTD(tmp));
	}
}
TEST(Hasher, hashing_strings) {
	std::uniform_int_distribution<int> length(5, 15);
	std::uniform_int_distribution<int> dis(-128, 127);

	MINE_STL::Hasher<string> getHashMINE;
	std::hash<string> getHashSTD;
	for (int i = 0; i < 1000; ++i)
	{
		int l = length(gen);
		std::string tmp = "";
		for (int j = 0; j < l; ++j)
			tmp += char(dis(gen));

		EXPECT_EQ(getHashMINE(tmp), getHashSTD(tmp));
	}
}
TEST(Hasher, template_hash_specialization) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> length(0, 15);

	int l = length(gen);
	A* arr = new A[l];
	MINE_STL::Hasher<A> getHashMINE;
	std::hash<A> getHashSTD;
	for (int i = 0; i < l; ++i)
	{
		EXPECT_EQ(getHashMINE(arr[i]), getHashSTD(arr[i]));
	}
}

TEST(HashMap, default_creation)
{
	MINE_STL::Map<int, int> mp1;
}
TEST(HashMap, mapping_integers_insertion)
{
	std::uniform_int_distribution<unsigned int> getAmount(10, 40);
	std::uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

	MINE_STL::Map<int, int> mp1;
	std::unordered_map<int, int> mp2;
	int amount = getAmount(gen);
	for (int i = 0; i < amount; i++) {
		int val = dis(gen);
		mp1.Insert(i, val);
		mp2[i] = val;
	}

	for (int i = 0; i < amount; ++i)
		EXPECT_EQ(mp1.Get(i), mp2[i]);
}
TEST(HashMap, mapping_integers_deletion)
{
	std::uniform_int_distribution<unsigned int> getAmount(10, 40);
	std::uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

	MINE_STL::Map<int, int> mp1;
	std::unordered_map<int, int> mp2;
	int amount = getAmount(gen);
	for (int i = 0; i < amount; i++) {
		int val = dis(gen);
		mp1.Insert(i, val);
		mp2[i] = val;
	}

	int del_amount = std::uniform_int_distribution<int>(0, amount)(gen);
	for (int i = 0; i < del_amount; i++)
	{
		mp1.Delete(i);
		mp2.erase(i);
	}

	for (int i = 0; i < amount; ++i)
	{
		EXPECT_EQ(mp1.Get(i), mp2[i]);
	}
}