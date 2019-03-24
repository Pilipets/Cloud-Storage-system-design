//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
#include<random>
#include<string>
#include"..\Version2\HashTable\Hasher.h"
#include"..\Version2\HashTable\HashMap.h"
#include<unordered_map>

class A {
public:
	int val;
	A() : val(rand())
	{}
};
namespace MINE_STL {
	template<>
	struct Hasher<A>
	{
		std::size_t operator()(const A& k) const {
			return MINE_STL::Hasher<int>()(k.val);
		}
	};
}
namespace std {
	template<>
	struct hash<A>
	{
		std::size_t operator()(const A& k) const {
			return std::hash<int>()(k.val);
		}
	};
}