#pragma once
#include<functional>
#include<random>
#include<vector>
#include"..\Hasher.h"
#include"..\constants.h"
using std::size_t;
using std::vector;
namespace MINE_STL {

	template<class K>
	class FunctionSet {
		typedef unsigned int uint;
		typedef std::function<size_t (const K&)> funcType;
		std::mt19937 gen;
		std::uniform_int_distribution<int> dis;
		vector<int> primes2;

		void _Init_Primes(int first, int last);
	public:
		FunctionSet();
		funcType GenerateRandomHashFunc(const int& m);
	};
}