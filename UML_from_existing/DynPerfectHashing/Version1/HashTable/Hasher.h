#ifndef Hash_Functor_H
#define Hash_Functor_H
#include<functional>
#include"..\OOP_Architecture\Product.h"

class Product;

namespace MINE_STL2 {
	typedef unsigned int uint;
	size_t _FNV_prime = 16777619U;
	size_t _FNV_offset_basis = 2166136261U;

	template<class _Kty>
	size_t _Hash_representation(const _Kty& _Keyval, size_t prime_a, const int& m)
	{	// bitwise hashes the representation of a key
		const unsigned char* const _First = &reinterpret_cast<const unsigned char&>(_Keyval);
		const size_t _Count = sizeof(_Kty);
		size_t _Val = 0;
		for (size_t i = 0; i < _Count; ++i)
		{
			if (_First[i]) {
				_Val = _Val * prime_a + _FNV_prime;
				_Val = _Val ^ static_cast<size_t>(_First[i]);
			}
		}
		return _Val % m;
	}
	size_t primes[12] = { 51683, 51691, 51713, 51719, 51721, 51749, 51767, 51769, 51787, 51797, 51803, 51817 };
	template<class K>
	class Hasher
	{

		typedef std::function<size_t(const K&)> funcType;
	public:
		funcType GenerateRandomHashFunc2(const int& m)
		{
			uint a = rand() % _FNV_prime;
			uint b = 1 + rand() % (_FNV_prime - 1);
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
	public:
		size_t operator()(const K& _Keyval, size_t prime_a, const int& m) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_representation(_Keyval, prime_a) % m);
		}
	};

	template<>
	std::function<size_t(const Product&)> Hasher<Product>::GenerateRandomHashFunc(const int& m)
	{
		int index = rand() % 12;
		size_t a = primes[index];
		return ([a, m](const Product& obj)
		{
			size_t id = obj.getId();
			return _Hash_representation(id, a, m);
		});
	}
}
#endif