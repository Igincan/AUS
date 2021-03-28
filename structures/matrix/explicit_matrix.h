#pragma once

#include "matrix.h"
#include "../array/array.h"

namespace structures
{

	template<typename T>
	class ExplicitMatrix : public Matrix<T>
	{
	public:
	
		ExplicitMatrix(int columns, int rows);
		~ExplicitMatrix();

		const T operator()(int columnIndex, int rowIndex) const;
		T& operator()(int columnIndex, int rowIndex);
		size_t numberOfRows() const;
		size_t numberOfColumns() const;

		Structure* clone() const override;
		size_t size() const override;
		Matrix<T>& operator=(const Matrix<T>& other) override;
		ExplicitMatrix<T>& operator=(const ExplicitMatrix<T>& other);
		ExplicitMatrix(const ExplicitMatrix<T>& other);

	private:

		Array<Array<T>*>* matrix_;

	};

	template<typename T>
	inline ExplicitMatrix<T>::ExplicitMatrix(int columns, int rows) :
		matrix_(new Array<Array<T>*>(columns))
	{
		for (size_t i = 0; i < matrix_->size(); i++)
		{
			(*matrix_)[i] = new Array<T>(rows);
		}
	}

	template<typename T>
	inline ExplicitMatrix<T>::~ExplicitMatrix()
	{
		for (size_t i = 0; i < matrix_->size(); i++)
		{
			delete (*matrix_)[i];
		}
		delete matrix_;
		matrix_ = nullptr;
	}

	template<typename T>
	inline const T ExplicitMatrix<T>::operator()(int columnIndex, int rowIndex) const
	{
		DSRoutines::rangeCheckExcept(columnIndex, matrix_->size(), "ExplicitMatrix<T>::operator(): Invalid column index.");
		DSRoutines::rangeCheckExcept(rowIndex, (*matrix_)[0]->size(), "ExplicitMatrix<T>::operator(): Invalid row index.");
		return (*(*matrix_)[columnIndex])[rowIndex];
	}

	template<typename T>
	inline T& ExplicitMatrix<T>::operator()(int columnIndex, int rowIndex)
	{
		DSRoutines::rangeCheckExcept(columnIndex, matrix_->size(), "ExplicitMatrix<T>::operator(): Invalid column index.");
		DSRoutines::rangeCheckExcept(rowIndex, (*matrix_)[0]->size(), "ExplicitMatrix<T>::operator(): Invalid row index.");
		return (*(*matrix_)[columnIndex])[rowIndex];
	}

	template<typename T>
	inline size_t ExplicitMatrix<T>::numberOfRows() const
	{
		return (*matrix_)[0]->size();
	}

	template<typename T>
	inline size_t ExplicitMatrix<T>::numberOfColumns() const
	{
		return matrix_->size();
	}

	template<typename T>
	inline Structure* ExplicitMatrix<T>::clone() const
	{
		return new ExplicitMatrix<T>(*this);
	}

	template<typename T>
	inline size_t ExplicitMatrix<T>::size() const
	{
		return numberOfColumns() * numberOfRows();
	}

	template<typename T>
	inline Matrix<T>& ExplicitMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ExplicitMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitMatrix<T>& ExplicitMatrix<T>::operator=(const ExplicitMatrix<T>& other)
	{
		if (this != &other)
		{
			if (this->numberOfColumns() == other.numberOfColumns() && this->numberOfRows() == other.numberOfRows())
			{
				for (size_t i = 0; i < matrix_->size(); i++)
				{
					(*(*matrix_)[i]) = (*(*other.matrix_)[i]);
				}
			}
			else
			{
				throw std::logic_error("ExplicitMatrix<T>::operator=: sizes of matrices are different.");
			}
		}
		return *this;
	}

	template<typename T>
	inline ExplicitMatrix<T>::ExplicitMatrix(const ExplicitMatrix<T>& other) :
		matrix_(new Array<Array<T>*>(other.numberOfColumns()))
	{
		for (size_t i = 0; i < matrix_->size(); i++)
		{
			(*matrix_)[i] = new Array<T>(other.numberOfRows());
		}
		*this = other;
	}

}
