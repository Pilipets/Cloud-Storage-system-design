#include"FuncGenerator.h"

namespace MINE_STL {
	template FunctionSet<int>;

	template<class K>
	void FunctionSet<K>::_Init_Primes(int first, int last)
	{
		int n = last;

		vector<bool> a(n + 1, true);
		vector<int> res;
		for (int i = 2; i * i <= n; i++)
			if (a[i])
				for (int j = i * i; j <= n; j += i)
					a[j] = false;

		for (int i = first; i <= n; i++)
			if (a[i])
				res.push_back(i);
		primes2 = res;
	}

	template<class K>
	 FunctionSet<K>::FunctionSet()
	{
		std::random_device rd;
		gen = std::mt19937(rd());
		dis = std::uniform_int_distribution<int>(INT_MIN, INT_MAX);
		//_Init_Primes(450000,500000);
	}
	 template<class K>
	 typename FunctionSet<K>::funcType FunctionSet<K>::GenerateRandomHashFunc(const int & m)
	 {
		 uint a = dis(gen) % _FNV_prime;
		 uint b = 1 + dis(gen) % (_FNV_prime - 1);
		 //uint a = primes2[dis(gen) % primes2.size()];
		 //uint b = 1+primes2[dis(gen) % primes2.size()];
		 return ([a, b, m](const K& obj)
		 {
			 return (size_t)((a*obj + b) % _FNV_prime) % m;
		 });
	 }
}