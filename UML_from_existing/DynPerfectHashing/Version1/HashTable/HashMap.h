#pragma once
#include"HashTableElem\HashNode.h"
#include<list>
#include<iostream>
using std::list;
using std::cout;

	typedef unsigned int uint;

	template<class K, class V>
	class Map
	{
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

		Hasher<K> FuncGenerator;
		funcType h;
		bool SpaceConditionSatisfied() /*Condition (**)*/
		{
			return sum_sj <= 32 * M*M / s_M + 4 * M;
		}

		bool isInjective(const funcType& hj, const list<HashNode<K, V>*>& l)
		{
			for (auto elem1 : l)
				for (auto elem2 : l)
					if (elem1 != elem2 && hj(elem1->key) == hj(elem2->key))
						return false;
			return true;
		}
		void RehashAll(HashNode<K, V>* item)
		{
#pragma region
			list<HashNode<K, V>*> l;
			for (int i = 0; i < s_M; i++)
			{
				for (int j = 0; j < T[i].sj; j++)
				{
					if (T[i].Tj[j] != nullptr)
					{
						l.push_back(T[i].Tj[j]);
						T[i].Tj[j] = nullptr;
					}
				}
			}
			if (item)
				l.push_back(item);
#pragma endregion Save all not null elements from hashTable t in List l

#pragma region
			//free memory for previous hashTable
			for (int j = 0; j < s_M; j++)
				if (T[j].Tj) delete[] T[j].Tj;
			delete[] T;

			count = l.size();
			const int c = 1;
			M = 2 * fmax(count, 4);
			s_M = (1.5)*M;
			T = new RowContainer[s_M];
#pragma endregion Set new size hashTable and allocate memory for new RowContainer

			//allocating temporary memory for subtables
			auto list_Lj = new list<HashNode<K, V>*>[s_M];

#pragma region
			do
			{
				sum_sj = 0;
				//get new outer hashFunction
				h = FuncGenerator.GenerateRandomHashFunc(s_M);

				//go through all not null elements of cur HashTable, which are stored in list l
				//and count amount of elements mapped into j cell in length_Lj[j]
				for (auto elem : l)
				{
					size_t index = h(elem->key);
					list_Lj[index].push_back(elem);
				}

				//update new sizes for subtables
				for (int j = 0; j < s_M; j++)
				{
					T[j].bj = list_Lj[j].size();
					T[j].mj = 2 * fmax(T[j].bj, 1);
					T[j].sj = T[j].mj*T[j].mj;

					sum_sj += T[j].sj;
				}

				//if we need to choose outer function again
				if (!SpaceConditionSatisfied())
				{
					//freeMemory
					for (int j = 0; j < s_M; ++j)
						list_Lj[j].clear();
				}
				else break;
			} while (true);
#pragma endregion Choosing appropriate main HashFunction

#pragma region

			for (int j = 0; j < s_M; j++)
			{
				int sj = T[j].sj;
				T[j].Tj = new HashNode<K, V> *[T[j].sj]{ nullptr };

				//repeat choosing inner function until hj is injective
				funcType &hj = T[j].hj;
				do
				{
					hj = FuncGenerator.GenerateRandomHashFunc(T[j].sj);
				} while (!isInjective(hj, list_Lj[j]));

				//move elements from list_Lj[j] to T[j].Tj with certain hash
				for (auto elem : list_Lj[j])
					T[j].Tj[hj(elem->key)] = elem;
			}
#pragma endregion  rewrite element from temporary list_Lj to M RowContainers in T

			delete[] list_Lj;
		}

		void Rehash(int j, HashNode<K, V>* item, bool reallocate = false)
		{
			int &sj = T[j].sj;
#pragma region
			list<HashNode<K, V>*> l;

			for (int i = 0; i < sj; i++)
			{
				if (T[j].Tj[i] != nullptr)
				{
					l.push_back(T[j].Tj[i]);
					T[j].Tj[i] = nullptr;
				}
			}

			l.push_back(item);

			if (reallocate)
			{
				delete[] T[j].Tj;
				int mj = T[j].mj;
				sj = mj * mj;
				T[j].Tj = new HashNode<K, V>*[sj] {nullptr};
			}
#pragma endregion Save all not Null elements from T[j] into List l
			funcType &hj = T[j].hj;
			do
			{
				hj = FuncGenerator.GenerateRandomHashFunc(sj);
			} while (!isInjective(hj, l));

			for (auto elem : l)
				T[j].Tj[hj(elem->key)] = elem;
		}
		void Initialize()
		{
			RehashAll(nullptr);
		}
	public:

		Map()
		{
			Initialize();
		}
		void show()
		{
			printf("Subtables size =%d <=> numBuckets=%d\n", sum_sj, s_M);
			for (int j = 0; j < s_M; ++j)
			{
				if (T[j].bj > 0)
				{
					cout << j << ": ";
					for (int i = 0; i < T[j].sj; ++i)
					{
						auto elem = T[j].Tj[i];
						if (elem != nullptr)
						{
							cout << elem->key << "->";
							cout << elem->value << ", ";
						}
					}
					cout << ";\n";
				}
				else
				{
					//
				}
			}
		}
		void Insert(const K& key, const V& val)
		{
			HashNode<K, V> *toInsert = new HashNode<K, V>(key, val);
			count = count + 1;
			if (count > M)
				RehashAll(toInsert);
			else
			{
				int j = h(key);
				int in_shift = T[j].hj(key);
				auto item = T[j].Tj[in_shift];
				if (item != nullptr && item->key == key)
					item->value = val;
				else
				{ //x is new for Tj
					int &bj = T[j].bj;
					int &mj = T[j].mj;

					bj = bj + 1;
					if (bj <= mj)
					{ //size of Tj is sufficient
						if (item == nullptr)
							T[j].Tj[in_shift] = toInsert;
						else
							Rehash(j, toInsert, false);
					}
					else
					{ //Tj is too small
						sum_sj -= T[j].sj;

						mj = 2 * fmax(1, mj);
						int sj = mj * mj;
						sum_sj += sj;
						if (SpaceConditionSatisfied()) //double capacity of Tj
							Rehash(j, toInsert, true);
						else //Level1 function is bad
							RehashAll(toInsert);
					}
				}

			}
		}

		void Delete(const K& key)
		{
			count = count + 1;
			int j = h(key);
			int in_shift = T[j].hj(key);
			auto elem = T[j].Tj[in_shift];
			if (elem != nullptr && elem->key == key)
			{
				T[j].bj -= 1;
				delete T[j].Tj[in_shift];
				T[j].Tj[in_shift] = nullptr;
			}

			if (count >= M)
				RehashAll(nullptr);
		}

		int Get(const K& key)
		{
			int j = h(key);
			int in_shift = T[j].hj(key);
			auto elem = T[j].Tj[in_shift];
			if (elem != nullptr && elem->key == key)
				return elem->value;
			return -9999999999;
		}
	};