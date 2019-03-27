#pragma once
#include<list>
#include<iostream>
#include<functional>
#include"FunctionSet\FuncGenerator.h"
using std::list;
using std::cout;

namespace MINE_STL
{
	typedef unsigned int uint;

	template<class K, class V>
	class Map
	{
		template<class K, class V>
		class HashNode
		{
		private:
			K key;
			V value;

			friend class Map<K, V>;
		public:
			// Constructor 
			HashNode(const K &key, const V &value) : key(key), value(value) {}

			bool operator==(const HashNode& obj)
			{
				return this->key == obj.key;
			}
		};

		typedef std::function<size_t(const K&)> funcType;
		struct RowContainer
		{
			int bj, mj, sj;
			HashNode<K, V>** Tj;
			funcType hj;
			//bj <= mj <=2*bj
			RowContainer() : bj(0), mj(0), sj(0), Tj(nullptr) {}
		};
		int sum_sj; //takes part in SpaceCondition(**) - sum of all sj
		size_t count; //updates made in HashMap
		int M;
		int s_M;
		//int n; //number of elemets currently stored in HashMap
		RowContainer* T;

		FunctionSet<K> FuncGenerator;
		funcType h;
		inline bool SpaceConditionSatisfied(); /*Condition (**)*/

		bool isInjective(const funcType& hj, const list<HashNode<K, V>*>& l);

		void RehashAll(HashNode<K, V>* item);

		void Rehash(int j, HashNode<K, V>* item, bool reallocate = false);

		inline void Initialize();
	public:

		Map();

		void show();

		void Insert(const K& key, const V& val);

		void Delete(const K& key);

		V Get(const K& key);
	};
}