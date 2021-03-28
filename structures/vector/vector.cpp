#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(this->memory_, other.memory_, this->size_);
	}

	Vector::~Vector()
	{
		free(this->memory_);
		this->memory_ = nullptr;
		this->size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure& Vector::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			this->size_ = other.size_;
			this->memory_ = realloc(this->memory_, this->size_);
			memcpy(this->memory_, other.memory_, this->size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return this->size_ == other.size_ && memcmp(other.memory_, this->memory_, this->size_) == 0;
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::getBytePointer: invalid index.");
		return *(reinterpret_cast<byte*>(this->memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::getBytePointer: invalid index.");
		return *(reinterpret_cast<byte*>(this->memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		if (count > 0)
		{
			DSRoutines::rangeCheckExcept(index, this->size_, "Vector::readBytes: invalid index.");
			DSRoutines::rangeCheckExcept(index + count, this->size_ + 1, "Vector::readBytes: invalid index.");
			if ((&dest <= this->getBytePointer(index + count - 1) && this->getBytePointer(index + count - 1) <= &dest + count - 1) ||
				(this->getBytePointer(index) <= &dest + count - 1 && &dest + count - 1 <= this->getBytePointer(index + count - 1)))
			{
				memmove(&dest, this->getBytePointer(index), count);
			}
			else
			{
				memcpy(&dest, this->getBytePointer(index), count);
			}
		}
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length > 0)
		{
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Vector::copy: invalid srcStartIndex.");
			DSRoutines::rangeCheckExcept(srcStartIndex + length - 1, src.size_, "Vector::copy: src out of bounds.");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Vector::copy: invalid srcStartIndex.");
			DSRoutines::rangeCheckExcept(destStartIndex + length - 1, dest.size_, "Vector::copy: dest out of bounds.");
			if (src.memory_ == dest.memory_ &&
				(srcStartIndex >= destStartIndex && srcStartIndex < destStartIndex + length ||
				destStartIndex >= srcStartIndex && destStartIndex < srcStartIndex + length))
			{
				memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
			else
			{
				memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::getBytePointer: invalid index.");
		return reinterpret_cast<byte*>(this->memory_) + index;
	}

}