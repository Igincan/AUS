#include "set.h"

namespace structures
{

	Set::Set(size_t capacity)
	{
		int numberOfBytes = static_cast<size_t>(ceil(static_cast<double>(capacity) / 8));
		this->memory_ = calloc(numberOfBytes, 1);
		this->capacity_ = numberOfBytes * 8;
	}

	Set::~Set()
	{
		free(this->memory_);
		this->memory_ = nullptr;
		this->capacity_ = 0;
	}

	Structure& Set::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Set&>(other);
		}
		return *this;
	}

	Structure* Set::clone() const
	{
		return new Set(*this);
	}

	size_t Set::size() const
	{
		int size = 0;
		byte* B = reinterpret_cast<byte*>(memory_);
		for (size_t i = 0; i < capacity_ / 8; i++)
		{
			for (int i = 0; i < 8; i++)
			{
				byte bit = (1 << i);
				if ((*B & bit) > 0)
				{
					size++;
				}
			}

			B++;
		}
		return size;
	}

	Set& Set::operator=(const Set& other)
	{
		if (this != &other)
		{
			byte* B = reinterpret_cast<byte*>(memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				*B = *otherB;

				B++;
				otherB++;
			}
			capacity_ = other.capacity_;
		}
		return *this;
	}

	bool Set::includes(int data)
	{
		int byteIndex = data / 8;
		int bitIndex = data % 8;
		byte* B = reinterpret_cast<byte*>(memory_) + byteIndex;
		return *B & (1 << bitIndex);
	}

	void Set::insert(int data)
	{
		int byteIndex = data / 8;
		int bitIndex = data % 8;
		byte* B = reinterpret_cast<byte*>(memory_) + byteIndex;
		*B = *B | (1 << bitIndex);
	}

	void Set::remove(int data)
	{
		int byteIndex = data / 8;
		int bitIndex = data % 8;
		byte* B = reinterpret_cast<byte*>(memory_) + byteIndex;
		*B = *B & ~(1 << bitIndex);
	}

	bool Set::equals(Set& other)
	{
		if (capacity_ == other.capacity_)
		{
			byte* B = reinterpret_cast<byte*>(memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				if (*B != *otherB)
				{
					return false;
				}
				B += 1;
				otherB += 1;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Set::isSubsetOf(Set& other)
	{
		if (capacity_ == other.capacity_)
		{
			byte* B = reinterpret_cast<byte*>(this->memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				for (int i = 0; i < 8; i++)
				{
					byte bit = (1 << i);
					if ((*otherB & bit) > 0 && (*B & bit) == 0)
					{
						return false;
					}
				}

				B++;
				otherB++;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	Set* Set::unite(Set& other)
	{
		if (capacity_ == other.capacity_)
		{
			Set* newSet = new Set(this->capacity_);

			byte* newB = reinterpret_cast<byte*>(newSet->memory_);
			byte* B = reinterpret_cast<byte*>(this->memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				*newB = *B | *otherB;

				newB++;
				B++;
				otherB++;
			}
			return newSet;
		}
		else
		{
			return nullptr;
		}
	}

	Set* Set::intersect(Set& other)
	{
		if (capacity_ == other.capacity_)
		{
			Set* newSet = new Set(this->capacity_);

			byte* newB = reinterpret_cast<byte*>(newSet->memory_);
			byte* B = reinterpret_cast<byte*>(this->memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				*newB = *B & *otherB;

				newB++;
				B++;
				otherB++;
			}
			return newSet;
		}
		else
		{
			return nullptr;
		}
	}

	Set* Set::substractsFrom(Set& other)
	{
		if (capacity_ == other.capacity_)
		{
			Set* newSet = new Set(this->capacity_);

			byte* newB = reinterpret_cast<byte*>(newSet->memory_);
			byte* B = reinterpret_cast<byte*>(this->memory_);
			byte* otherB = reinterpret_cast<byte*>(other.memory_);
			for (size_t i = 0; i < capacity_ / 8; i++)
			{
				for (int i = 0; i < 8; i++)
				{
					byte bit = (1 << i);
					if ((*otherB & bit) > 0)
					{
						if ((*B & bit) == 0)
						{
							*newB = *newB | bit;
						}
					}
				}

				newB++;
				B++;
				otherB++;
			}
			return newSet;
		}
		else
		{
			return nullptr;
		}
	}

	size_t Set::getCapacity()
	{
		return capacity_;
	}

}

