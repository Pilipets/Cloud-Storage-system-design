#pragma once
#include<functional>
#include<random>
using std::size_t;
namespace MINE_STL {
	extern size_t _FNV_prime;
	extern size_t _FNV_offset_basis;

	template<class K>
	class Generator {
		typedef unsigned int uint;
		typedef std::function<size_t (const K&)> funcType;
		std::mt19937 gen;
		std::uniform_int_distribution<int> dis;
		size_t primes[12] = { 51683, 51691, 51713, 51719, 51721, 51749, 51767, 51769, 51787, 51797, 51803, 51817 };
	public:
		Generator()
		{
			std::random_device rd;
			gen = std::mt19937(rd());
			dis = std::uniform_int_distribution<int>(INT_MIN, INT_MAX);
			//_Init_Primes();
		}
		funcType GenerateRandomHashFunc2(const int& m)
		{
			uint a = dis(gen) % _FNV_prime;
			uint b = 1 + dis(gen) % (_FNV_prime - 1);
			return ([a, b, m](const K& obj)
			{
				return (size_t)((a*obj + b) % _FNV_prime) % m;
			});
		}
		funcType GenerateRandomHashFunc(const int& m)
		{
			int index = rand() % 12;
			size_t a = primes[index];
			return ([a, m](const K& obj)
			{
				const unsigned char* const _First = &reinterpret_cast<const unsigned char&>(obj);
				const size_t _Count = sizeof(K);

				size_t _Val = 0;
				for (size_t i = 0; i < _Count; ++i)
				{
					if (_First[i]) {
						_Val = _Val * a + _FNV_prime;
						_Val = _Val ^ static_cast<size_t>(_First[i]);
					}
				}
				return _Val % m;
			});
		}
	};
}