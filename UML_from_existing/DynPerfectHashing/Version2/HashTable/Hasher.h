#ifndef Hash_Functor_H
#define Hash_Functor_H

#include<string>
using std::string;

namespace MINE_STL
{
	typedef unsigned int uint;
	extern size_t _FNV_prime;
	extern size_t _FNV_offset_basis;

	inline size_t _Fnv1a_append_bytes(size_t _Val,
		const unsigned char * const _First, const size_t _Count)
	{	// accumulate range [_First, _First + _Count) into partial FNV-1a hash _Val
		for (size_t _Idx = 0; _Idx < _Count; ++_Idx)
		{
			_Val ^= static_cast<size_t>(_First[_Idx]);
			_Val *= _FNV_prime;
		}

		return (_Val);
	}


	template<class _Kty>
	inline size_t _Fnv1a_append_value(const size_t _Val, const _Kty& _Keyval)
	{	// accumulate _Keyval into partial FNV-1a hash _Val
		static_assert(std::is_trivial_v<_Kty>, "Only trivial types can be directly hashed.");
		return (_Fnv1a_append_bytes(_Val,
			&reinterpret_cast<const unsigned char&>(_Keyval), sizeof(_Kty)));
	}

	template<class _Kty>
	inline size_t _Hash_representation(const _Kty& _Keyval)
	{	// bitwise hashes the representation of a key
		return (_Fnv1a_append_value(_FNV_offset_basis, _Keyval));
	}

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

	//template<>
	//class Hasher<const char*>
	//{
	//public:
	//	size_t operator()(const char *_Str) const
	//	{	// hash _Keyval to size_t value by pseudorandomizing transform
	//		return (_Hash_array_representation(_Str, strlen(_Str)));
	//	}
	//};
};
#endif