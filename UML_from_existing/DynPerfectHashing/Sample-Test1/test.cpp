#include "pch.h"

TEST(HashMap, mapping_integers_insertion)
{
	std::uniform_int_distribution<unsigned int> getAmount(10, 40);
	std::uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

	MINE_STL2::Map<int, int> mp1;
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