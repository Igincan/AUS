#pragma once

#include "matrix.h"

namespace structures
{

	template<typename T>
	class ImplicitMatrix : public Matrix<T>
	{
	public:

		ImplicitMatrix(int columns, int rows);
		ImplicitMatrix(const ImplicitMatrix<T>& other);
		ImplicitMatrix(ImplicitMatrix<T>&& other);
		~ImplicitMatrix();

		const T operator()(int columnIndex, int rowIndex) const;
		T& operator()(int columnIndex, int rowIndex);
		size_t numberOfRows() const;
		size_t numberOfColumns() const;

		Structure* clone() const override;
		size_t size() const override;
		Matrix<T>& operator=(const Matrix<T>& other) override;
		ImplicitMatrix<T>& operator=(const ImplicitMatrix<T>& other);
		ImplicitMatrix<T>& operator=(ImplicitMatrix<T>&& other);
		

	private:

		const int mapFunction(int columnIndex, int rowIndex) const;

		Array<T>* matrix_;
		size_t numberOfColumns_;
		size_t numberOfRows_;

	};

	template<typename T>
	inline ImplicitMatrix<T>::ImplicitMatrix(int columns, int rows) :
		matrix_(new Array<T>(columns* rows)),
		numberOfColumns_(columns),
		numberOfRows_(rows)
	{
	}

	template<typename T>
	inline ImplicitMatrix<T>::ImplicitMatrix(const ImplicitMatrix<T>& other) :
		matrix_(new Array<T>(other.numberOfColumns()* other.numberOfRows())),
		numberOfColumns_(other.numberOfColumns()),
		numberOfRows_(other.numberOfRows())
	{
		*this = other;
	}

	template<typename T>
	inline ImplicitMatrix<T>::ImplicitMatrix(ImplicitMatrix<T>&& other) :
		matrix_(std::exchange(other.matrix_, nullptr)),
		numberOfColumns_(std::exchange(other.numberOfColumns_, 0)),
		numberOfRows_(std::exchange(other.numberOfRows_, 0))
	{
	}

	template<typename T>
	inline ImplicitMatrix<T>::~ImplicitMatrix()
	{
		delete matrix_;
		matrix_ = nullptr;
	}

	template<typename T>
	inline const T ImplicitMatrix<T>::operator()(int columnIndex, int rowIndex) const
	{
		return (*matrix_)[mapFunction(columnIndex, rowIndex)];
	}

	template<typename T>
	inline T& ImplicitMatrix<T>::operator()(int columnIndex, int rowIndex)
	{
		return (*matrix_)[mapFunction(columnIndex, rowIndex)];
	}

	template<typename T>
	inline size_t ImplicitMatrix<T>::numberOfRows() const
	{
		return numberOfRows_;
	}

	template<typename T>
	inline size_t ImplicitMatrix<T>::numberOfColumns() const
	{
		return numberOfColumns_;
	}

	template<typename T>
	inline Structure* ImplicitMatrix<T>::clone() const
	{
		return new ImplicitMatrix<T>(*this);
	}

	template<typename T>
	inline size_t ImplicitMatrix<T>::size() const
	{
		return matrix_->size();
	}

	template<typename T>
	inline Matrix<T>& ImplicitMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ImplicitMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitMatrix<T>& ImplicitMatrix<T>::operator=(const ImplicitMatrix<T>& other)
	{
		if (this != &other)
		{
			if (this->numberOfColumns() == other.numberOfColumns() && this->numberOfRows() == other.numberOfRows())
			{
				(*matrix_) = (*other.matrix_);
			}
			else
			{
				throw std::logic_error("ImplicitMatrix<T>::operator=: sizes of matrices are different.");
			}
		}
		return *this;
	}

	template<typename T>
	inline ImplicitMatrix<T>& ImplicitMatrix<T>::operator=(ImplicitMatrix<T>&& other)
	{
		if (this != &other)
		{
			delete matrix_;
			matrix_ = std::exchange(other.matrix_, nullptr);
			numberOfColumns_ = std::exchange(other.numberOfColumns_, 0);
			numberOfRows_ = std::exchange(other.numberOfRows_, 0);
		}
	}

	template<typename T>
	inline const int ImplicitMatrix<T>::mapFunction(int columnIndex, int rowIndex) const
	{
		return rowIndex * numberOfColumns_ + columnIndex;
	}

}

