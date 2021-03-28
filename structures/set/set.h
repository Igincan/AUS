#pragma once

#include <cmath>
#include <stdexcept>
#include "../structure.h"

typedef unsigned char byte;

namespace structures
{

	class Set : public Structure
	{
	public:

		Set(size_t capacity);
		~Set();

		Structure& operator=(const Structure& other) override;
		Structure* clone() const override;
		size_t size() const override;

		Set& operator=(const Set& other);
		bool includes(int data);
		void insert(int data);
		void remove(int data);
		bool equals(Set& set);
		bool isSubsetOf(Set& other);
		Set* unite(Set& other);
		Set* intersect(Set& other);
		Set* substractsFrom(Set& other);
		size_t getCapacity();

	private:

		void* memory_;
		size_t capacity_;

	};

}