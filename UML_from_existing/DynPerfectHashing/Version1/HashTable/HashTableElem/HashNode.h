#pragma once

namespace MINE_STL2 {
	template<class K, class V>
	class HashNode
	{
	private:
		K key;
		V value;

		template<class K, class V>
		friend class Map;
	public:
		// Constructor 
		HashNode(const K &key, const V &value)
		{
			this->key = key;
			this->value = value;
		}
		bool operator==(const HashNode& obj)
		{
			return this->key == obj.key;
		}
	};
}
