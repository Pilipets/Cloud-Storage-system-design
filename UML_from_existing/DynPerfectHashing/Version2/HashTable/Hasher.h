#ifndef Hash_Functor_H
#define Hash_Functor_H
#include"constants.h"
#include<string>
using std::string;

namespace MINE_STL
{
	typedef unsigned int uint;

	inline size_t _Fnv1a_append_bytes(size_t _Val,
		const unsigned char * const _First, const size_t _Count);


	template<class _Kty>
	inline size_t _Fnv1a_append_value(const size_t _Val, const _Kty& _Keyval);

	template<class _Kty>
	inline size_t _Hash_representation(const _Kty& _Keyval);

	template<class _Kty>
	inline size_t _Hash_array_representation(
		const _Kty * const _First, const size_t _Count)
	{	// bitwise hashes the representation of an array
		return (_Fnv1a_append_bytes(_FNV_offset_basis,
			reinterpret_cast<const unsigned char *>(_First), _Count * sizeof(_Kty)));
	}
	
	template<class K>
	class Hasher
	{
	public:
		size_t operator()(const K& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_representation(_Keyval));
		}
	};

	template<>
	class Hasher<string>
	{
	public:
		size_t operator()(const string& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_array_representation(_Keyval.c_str(), _Keyval.size()));
		}
	};
};

#include"Hasher.tpp"
#endif