#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class LinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		LinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		LinkedListItem(const LinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~LinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		LinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name�= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(LinkedListItem<T>* next);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		LinkedListItem<T>* next_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class LinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		LinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		LinkedList(const LinkedList<T>& other);

		LinkedList(LinkedList<T>&& other);

		/// <summary> Destruktor. </summary>
		~LinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		List<T>& operator=(List<T>&& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		LinkedList<T>& operator=(const LinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		LinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		LinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		LinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class LinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			LinkedListIterator(LinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~LinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			LinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(const LinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::~LinkedListItem()
	{
		next_ = nullptr;
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline LinkedList<T>::LinkedList() :
		List<T>(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(const LinkedList<T>& other) :
		LinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(LinkedList<T>&& other) :
		size_(std::exchange(other.size_, 0)),
		first_(std::exchange(other.first_, nullptr)),
		last_(std::exchange(other.last_, nullptr))
	{
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		this->clear();
	}

	template<typename T>
	inline Structure* LinkedList<T>::clone() const
	{
		return new LinkedList<T>(*this);
	}

	template<typename T>
	inline size_t LinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& LinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const LinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline List<T>& LinkedList<T>::operator=(List<T>&& other)
	{
		if (this != &other)
		{
			clear();
			size_ = std::exchange(other.size_, 0);
			first_ = std::exchange(other.first_, nullptr);
			last_ = std::exchange(other.last_, nullptr);
		}
	}

	template<typename T>
	inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
	{
		if (this != &other)
		{
			this->clear();
			LinkedListItem<T>* item = other.first_;
			while (item != nullptr)
			{
				this->add(item->accessData());
				item = item->getNext();
			}
		}
		return *this;
	}

	template<typename T>
	inline T& LinkedList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "LinkedList<T>::operator[]: Invalid index.");
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T LinkedList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "LinkedList<T>::operator[]: Invalid index.");
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void LinkedList<T>::add(const T& data)
	{
		LinkedListItem<T>* item = new LinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = item;
		}
		else
		{
			last_->setNext(item);
		}
		last_ = item;
		size_++;
	}

	template<typename T>
	inline void LinkedList<T>::insert(const T& data, const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_ + 1, "LinkedList<T>::insert: Invalid index.");
		LinkedListItem<T>* item = new LinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = item;
			last_ = item;
		}
		else
		{
			if (index == 0)
			{
				item->setNext(first_);
				first_ = item;
			}
			else if (index == size_)
			{
				last_->setNext(item);
				last_ = item;
			}
			else
			{
				LinkedListItem<T>* beforeItem = this->getItemAtIndex(index - 1);
				LinkedListItem<T>* afterItem = beforeItem->getNext();
				beforeItem->setNext(item);
				item->setNext(afterItem);
			}
		}
		size_++;
	}

	template<typename T>
	inline bool LinkedList<T>::tryRemove(const T& data)
	{
		int index = this->getIndexOf(data);
		if (index >= 0)
		{
			this->removeAt(index);
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	inline T LinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "LinkedList<T>::removeAt: Invalid index.");
		LinkedListItem<T>* item;
		if (size_ > 1)
		{
			if (index == 0)
			{
				item = first_;
				first_ = item->getNext();
			}
			else if (index == size_ - 1)
			{
				LinkedListItem<T>* beforeItem = this->getItemAtIndex(index - 1);
				item = last_;
				last_ = beforeItem;
				beforeItem->setNext(nullptr);
			}
			else
			{
				LinkedListItem<T>* beforeItem = this->getItemAtIndex(index - 1);
				item = beforeItem->getNext();
				LinkedListItem<T>* afterItem = item->getNext();
				beforeItem->setNext(afterItem);
			}
		}
		else
		{
			item = first_;
			first_ = nullptr;
			last_ = nullptr;
		}
		size_--;
		T data = item->accessData();
		delete item;
		return data;
	}

	template<typename T>
	inline int LinkedList<T>::getIndexOf(const T& data)
	{
		LinkedListItem<T>* item = first_;
		int index = 0;
		while (item != nullptr)
		{
			if (item->accessData() == data)
			{
				return index;
			}
			index++;
			item = item->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void LinkedList<T>::clear()
	{
		LinkedListItem<T>* current = first_;
		LinkedListItem<T>* successor = nullptr;
		if (current != nullptr)
		{
			successor = current->getNext();
		}
		while (current != nullptr)
		{
			delete current;
			current = successor;
			if (current != nullptr)
			{
				successor = current->getNext();
			}
		}
		first_ = nullptr;
		last_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getBeginIterator() const
	{
		return new LinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getEndIterator() const
	{
		return new LinkedListIterator(nullptr);
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "LinkedList<T>::getItemAtIndex: Invalid index.");
		LinkedListItem<T>* item = first_;
		for (int i = 0; i < index; i++)
		{
			item = item->getNext();
		}
		return item;
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(const Iterator<T>& other)
	{
		if (this != &other)
		{
			this->position_ = dynamic_cast<const LinkedList<T>::LinkedListIterator&>(other).position_;
		}
		return *this;
	}

	template<typename T>
	inline bool LinkedList<T>::LinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return this->position_ != dynamic_cast<const LinkedList<T>::LinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline const T LinkedList<T>::LinkedListIterator::operator*()
	{
		return this->position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
	{
		this->position_ = this->position_->getNext();
		return *this;
	}
}