#pragma once

#include "../structure.h"

namespace structures
{

	template<typename T>
	class Matrix : public Structure
	{
	public:

		virtual const T operator()(int columnIndex, int rowIndex) const = 0;
		virtual T& operator()(int columnIndex, int rowIndex) = 0;
		virtual size_t numberOfRows() const = 0;
		virtual size_t numberOfColumns() const = 0;

		virtual Structure* clone() const = 0;
		virtual size_t size() const = 0;
		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;

		Structure& operator=(const Structure& other) override;


	};

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

}