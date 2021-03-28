#pragma once

#include "sequence_table.h"
#include "../list/array_list.h"
#include "../ds_routines.h"

namespace structures
{

	template<typename K, typename T>
	class DiamondTable : public SequenceTable<K, T>
	{
	public:

		DiamondTable();
		DiamondTable(const DiamondTable<K, T>& other);
		~DiamondTable();

		void insert(const K& key, const T& data) override;
		T& operator[](const K key) override;
		const T operator[](const K key) const override;
		T remove(const K& key) override;

		Structure* clone() const override;
		size_t size() const override;


	private:
		
		int getUpperLeftNeighborIndex(int index) const;
		int getLowerLeftNeighborIndex(int index) const;
		int getUpperRightNeighborIndex(int index) const;
		int getLowerRightNeighborIndex(int index) const;
		bool hasUpperLeftNeighbor(int index) const;
		bool hasLowerLeftNeighbor(int index) const;
		bool hasUpperRightNeighbor(int index) const;
		bool hasLowerRightNeighbor(int index) const;
		int getLevelByIndex(int index) const;
		bool isMostLeftInLevel(int index) const;
		bool isMostRightInLevel(int index) const;
		K getKeyByIndex(int index) const;
		T& accessDataByIndex(int index);
		const T accessDataByIndex(int index) const;
		int getIndexByKey(const K key) const;
		void moveToCorrectPosition(int index);
	};

	template<typename K, typename T>
	inline DiamondTable<K, T>::DiamondTable() :
	SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
		this->list_->add(nullptr);
	}

	template<typename K, typename T>
	inline DiamondTable<K, T>::DiamondTable(const DiamondTable<K, T>& other) :
	DiamondTable()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline DiamondTable<K, T>::~DiamondTable()
	{
		for (auto item : *this->list_)
		{
			delete item;
		}
		this->list_->clear();
	}

	template<typename K, typename T>
	inline void DiamondTable<K, T>::insert(const K& key, const T& data)
	{
		this->list_->add(new TableItem<K, T>(key, data));
		moveToCorrectPosition(this->list_->size() - 1);
	}

	template<typename K, typename T>
	inline T& DiamondTable<K, T>::operator[](const K key)
	{
		return accessDataByIndex(getIndexByKey(key));
	}

	template<typename K, typename T>
	inline const T DiamondTable<K, T>::operator[](const K key) const
	{
		return accessDataByIndex(getIndexByKey(key));
	}

	template<typename K, typename T>
	inline T DiamondTable<K, T>::remove(const K& key)
	{
		int index = getIndexByKey(key);
		int lastIndex = this->list_->size() - 1;
		DSRoutines::swap((*this->list_)[index], (*this->list_)[lastIndex]);
		TableItem<K, T>* item = this->list_->removeAt(lastIndex);
		T result = item->accessData();
		delete item;
		item = nullptr;
		if (index < static_cast<int>(this->list_->size()))
		{
			moveToCorrectPosition(index);
		}
		return result;
	}

	template<typename K, typename T>
	inline Structure* DiamondTable<K, T>::clone() const
	{
		return new DiamondTable(*this);
	}

	template<typename K, typename T>
	inline size_t DiamondTable<K, T>::size() const
	{
		return this->list_->size() - 1;
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getUpperLeftNeighborIndex(int index) const
	{
		return index - getLevelByIndex(index);
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getLowerLeftNeighborIndex(int index) const
	{
		return index + getLevelByIndex(index);
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getUpperRightNeighborIndex(int index) const
	{
		return index - getLevelByIndex(index) + 1;
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getLowerRightNeighborIndex(int index) const
	{
		return index + getLevelByIndex(index) + 1;
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::hasUpperLeftNeighbor(int index) const
	{
		return !isMostLeftInLevel(index);
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::hasLowerLeftNeighbor(int index) const
	{
		return getLowerLeftNeighborIndex(index) < static_cast<int>(this->list_->size());
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::hasUpperRightNeighbor(int index) const
	{
		return !isMostRightInLevel(index);
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::hasLowerRightNeighbor(int index) const
	{
		return getLowerRightNeighborIndex(index) < static_cast<int>(this->list_->size());
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getLevelByIndex(int index) const
	{
		int level = 1;
		int endIndex = 1;
		while (true)
		{
			if (index <= endIndex)
			{
				return level;
			}
			level++;
			endIndex += level;
		}
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::isMostLeftInLevel(int index) const
	{
		return index == 1 ? true : getLevelByIndex(index) != getLevelByIndex(index - 1);
	}

	template<typename K, typename T>
	inline bool DiamondTable<K, T>::isMostRightInLevel(int index) const
	{
		return index == 1 ? true : getLevelByIndex(index) != getLevelByIndex(index + 1);
	}

	template<typename K, typename T>
	inline K DiamondTable<K, T>::getKeyByIndex(int index) const
	{
		return (*this->list_)[index]->getKey();
	}

	template<typename K, typename T>
	inline T& DiamondTable<K, T>::accessDataByIndex(int index)
	{
		return (*this->list_)[index]->accessData();
	}

	template<typename K, typename T>
	inline const T DiamondTable<K, T>::accessDataByIndex(int index) const
	{
		return (*this->list_)[index]->accessData();
	}

	template<typename K, typename T>
	inline int DiamondTable<K, T>::getIndexByKey(const K key) const
	{
		int index = 1;
		while (true)
		{
			if (getKeyByIndex(index) > key)
			{
				if (hasLowerLeftNeighbor(index))
				{
					index = getLowerLeftNeighborIndex(index);
				}
				else
				{
					throw std::logic_error("DiamondTable::getItemByKey: Invalid key!");
				}
			}
			else if (getKeyByIndex(index) < key)
			{
				if (hasLowerRightNeighbor(index))
				{
					index = getLowerRightNeighborIndex(index);
				}
				else
				{
					throw std::logic_error("DiamondTable::getItemByKey: Invalid key!");
				}
			}
			else
			{
				return index;
			}
		}
	}

	template<typename K, typename T>
	inline void DiamondTable<K, T>::moveToCorrectPosition(int index)
	{
		bool isCorrectPosition = false;

		while (!isCorrectPosition)
		{
			int upperLeftNeigborIndex = getUpperLeftNeighborIndex(index);
			int lowerLeftNeigborIndex = getLowerLeftNeighborIndex(index);
			int upperRightNeigborIndex = getUpperRightNeighborIndex(index);
			int lowerRightNeigborIndex = getLowerRightNeighborIndex(index);
			bool upperLeftNeigborIsBad = hasUpperLeftNeighbor(index) && getKeyByIndex(index) < getKeyByIndex(upperLeftNeigborIndex);
			bool lowerLeftNeigborIsBad = hasLowerLeftNeighbor(index) && getKeyByIndex(index) < getKeyByIndex(lowerLeftNeigborIndex);
			bool upperRightNeigborIsBad = hasUpperRightNeighbor(index) && getKeyByIndex(index) > getKeyByIndex(upperRightNeigborIndex);
			bool lowerRightNeigborIsBad = hasLowerRightNeighbor(index) && getKeyByIndex(index) > getKeyByIndex(lowerRightNeigborIndex);

			if (upperLeftNeigborIsBad && lowerLeftNeigborIsBad)
			{
				if (getKeyByIndex(upperLeftNeigborIndex) > getKeyByIndex(lowerLeftNeigborIndex))
				{
					DSRoutines::swap((*this->list_)[index], (*this->list_)[upperLeftNeigborIndex]);
					index = upperLeftNeigborIndex;
				}
				else
				{
					DSRoutines::swap((*this->list_)[index], (*this->list_)[lowerLeftNeigborIndex]);
					index = lowerLeftNeigborIndex;
				}
			}
			else if (upperLeftNeigborIsBad)
			{
				DSRoutines::swap((*this->list_)[index], (*this->list_)[upperLeftNeigborIndex]);
				index = upperLeftNeigborIndex;
			}
			else if (lowerLeftNeigborIsBad)
			{
				DSRoutines::swap((*this->list_)[index], (*this->list_)[lowerLeftNeigborIndex]);
				index = lowerLeftNeigborIndex;
			}
			else if (upperRightNeigborIsBad && lowerRightNeigborIsBad)
			{
				if (getKeyByIndex(upperRightNeigborIndex) < getKeyByIndex(lowerRightNeigborIndex))
				{
					DSRoutines::swap((*this->list_)[index], (*this->list_)[upperRightNeigborIndex]);
					index = upperRightNeigborIndex;
				}
				else
				{
					DSRoutines::swap((*this->list_)[index], (*this->list_)[lowerRightNeigborIndex]);
					index = lowerRightNeigborIndex;
				}
			}
			else if (upperRightNeigborIsBad)
			{
				DSRoutines::swap((*this->list_)[index], (*this->list_)[upperRightNeigborIndex]);
				index = upperRightNeigborIndex;
			}
			else if (lowerRightNeigborIsBad)
			{
				DSRoutines::swap((*this->list_)[index], (*this->list_)[lowerRightNeigborIndex]);
				index = lowerRightNeigborIndex;
			}
			else
			{
				isCorrectPosition = true;
			}
		}
	}

}
