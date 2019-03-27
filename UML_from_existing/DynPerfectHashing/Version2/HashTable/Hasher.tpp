namespace MINE_STL {

	size_t _Fnv1a_append_bytes(size_t _Val, const unsigned char * const _First, const size_t _Count)
	{	// accumulate range [_First, _First + _Count) into partial FNV-1a hash _Val
		for (size_t _Idx = 0; _Idx < _Count; ++_Idx)
		{
			_Val ^= static_cast<size_t>(_First[_Idx]);
			_Val *= _FNV_prime;
		}

		return (_Val);
	}

	template<class _Kty>
	size_t _Fnv1a_append_value(const size_t _Val, const _Kty & _Keyval)
	{	// accumulate _Keyval into partial FNV-1a hash _Val
		static_assert(std::is_trivial_v<_Kty>, "Only trivial types can be directly hashed.");
		return (_Fnv1a_append_bytes(_Val,
			&reinterpret_cast<const unsigned char&>(_Keyval), sizeof(_Kty)));
	}

	template<class _Kty>
	size_t _Hash_representation(const _Kty & _Keyval)
	{	// bitwise hashes the representation of a key
		return (_Fnv1a_append_value(_FNV_offset_basis, _Keyval));
	}

}