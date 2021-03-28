#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class DoublyLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DoublyLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DoublyLinkedListItem(const DoublyLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DoublyLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		DoublyLinkedListItem<T>* getNext();

		/// <summary> Getter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Predchadzajuci prvok zretazeneho zoznamu. </returns>
		DoublyLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name�= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(DoublyLinkedListItem<T>* next);

		/// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <param name�= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setPrevious(DoublyLinkedListItem<T>* previous);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		DoublyLinkedListItem<T>* next_;
		DoublyLinkedListItem<T>* previous_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoublyLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoublyLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> DoublyLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		DoublyLinkedList(const DoublyLinkedList<T>& other);

		DoublyLinkedList(DoublyLinkedList<T>&& other);

		/// <summary> Destruktor. </summary>
		~DoublyLinkedList();

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

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

		DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);

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
		DoublyLinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		DoublyLinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		DoublyLinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre DoublyLinkedList. </summary>
		class LinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			LinkedListIterator(DoublyLinkedListItem<T>* position);

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
			DoublyLinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline DoublyLinkedListItem<T>::DoublyLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline DoublyLinkedListItem<T>::DoublyLinkedListItem(const DoublyLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline DoublyLinkedListItem<T>::~DoublyLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline DoublyLinkedListItem<T>* DoublyLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline DoublyLinkedListItem<T>* DoublyLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void DoublyLinkedListItem<T>::setNext(DoublyLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void DoublyLinkedListItem<T>::setPrevious(DoublyLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	template<typename T>
	inline DoublyLinkedList<T>::DoublyLinkedList() :
		List<T>(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) :
		DoublyLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) :
		size_(other.size_),
		first_(other.first_),
		last_(other.last_)
	{
		other.size_ = 0;
		other.first_ = nullptr;
		other.last_ = nullptr;
	}

	template<typename T>
	inline DoublyLinkedList<T>::~DoublyLinkedList()
	{
		this->clear();
	}

	template<typename T>
	inline Structure* DoublyLinkedList<T>::clone() const
	{
		return new DoublyLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t DoublyLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& DoublyLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const DoublyLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
	{
		if (this != &other)
		{
			this->clear();
			DoublyLinkedListItem<T>* item = other.first_;
			while (item != nullptr)
			{
				this->add(item->accessData());
				item = item->getNext();
			}
		}
		return *this;
	}

	template<typename T>
	inline DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other)
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
	inline T& DoublyLinkedList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index.");
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T DoublyLinkedList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index.");
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void DoublyLinkedList<T>::add(const T& data)
	{
		DoublyLinkedListItem<T>* item = new DoublyLinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = item;
		}
		else
		{
			last_->setNext(item);
			item->setPrevious(last_);
		}
		last_ = item;
		size_++;
	}

	template<typename T>
	inline void DoublyLinkedList<T>::insert(const T& data, const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_ + 1, "DoubleLinkedList<T>::insert: Invalid index.");
		DoublyLinkedListItem<T>* item = new DoublyLinkedListItem<T>(data);
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
				first_->setPrevious(item);
				first_ = item;
			}
			else if (index == size_)
			{
				last_->setNext(item);
				item->setPrevious(last_);
				last_ = item;
			}
			else
			{
				DoublyLinkedListItem<T>* beforeItem;
				DoublyLinkedListItem<T>* afterItem;
				if (index < static_cast<int>(size_) / 2)
				{
					beforeItem = this->getItemAtIndex(index - 1);
					afterItem = beforeItem->getNext();
				}
				else
				{
					afterItem = this->getItemAtIndex(index);
					beforeItem = afterItem->getPrevious();
				}
				beforeItem->setNext(item);
				item->setNext(afterItem);
				afterItem->setPrevious(item);
				item->setPrevious(beforeItem);
			}
		}
		size_++;
	}

	template<typename T>
	inline bool DoublyLinkedList<T>::tryRemove(const T& data)
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
	inline T DoublyLinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::removeAt: Invalid index.");
		DoublyLinkedListItem<T>* item;
		if (size_ > 1)
		{
			if (index == 0)
			{
				item = first_;
				first_ = item->getNext();
				first_->setPrevious(nullptr);
			}
			else if (index == size_ - 1)
			{
				item = last_;
				last_ = item->getPrevious();
				last_->setNext(nullptr);
			}
			else
			{
				DoublyLinkedListItem<T>* beforeItem;
				DoublyLinkedListItem<T>* afterItem;
				if (index < static_cast<int>(size_) / 2)
				{
					beforeItem = this->getItemAtIndex(index - 1);
					item = beforeItem->getNext();
					afterItem = item->getNext();
				}
				else
				{
					afterItem = this->getItemAtIndex(index + 1);
					item = afterItem->getPrevious();
					beforeItem = item->getPrevious();
				}
				beforeItem->setNext(afterItem);
				afterItem->setPrevious(beforeItem);
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
	inline int DoublyLinkedList<T>::getIndexOf(const T& data)
	{
		DoublyLinkedListItem<T>* item = first_;
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
	inline void DoublyLinkedList<T>::clear()
	{
		DoublyLinkedListItem<T>* current = first_;
		DoublyLinkedListItem<T>* successor = nullptr;
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
	inline Iterator<T>* DoublyLinkedList<T>::getBeginIterator() const
	{
		return new LinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* DoublyLinkedList<T>::getEndIterator() const
	{
		return new LinkedListIterator(nullptr);
	}

	template<typename T>
	inline DoublyLinkedListItem<T>* DoublyLinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::getItemAtIndex: Invalid index.");
		
		if (index < static_cast<int>(size_) / 2)
		{
			DoublyLinkedListItem<T>* item = first_;
			for (int i = 0; i < index; i++)
			{
				item = item->getNext();
			}
			return item;
		}
		else
		{
			DoublyLinkedListItem<T>* item = last_;
			for (size_t i = 0; i < size_ - 1 - index; i++)
			{
				item = item->getPrevious();
			}
			return item;
		}
	}

	template<typename T>
	inline DoublyLinkedList<T>::LinkedListIterator::LinkedListIterator(DoublyLinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline DoublyLinkedList<T>::LinkedListIterator::~LinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoublyLinkedList<T>::LinkedListIterator::operator=(const Iterator<T>& other)
	{
		if (this != &other)
		{
			this->position_ = dynamic_cast<const DoublyLinkedList<T>::LinkedListIterator&>(other).position_;
		}
		return *this;
	}

	template<typename T>
	inline bool DoublyLinkedList<T>::LinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return this->position_ != dynamic_cast<const DoublyLinkedList<T>::LinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline const T DoublyLinkedList<T>::LinkedListIterator::operator*()
	{
		return this->position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoublyLinkedList<T>::LinkedListIterator::operator++()
	{
		this->position_ = this->position_->getNext();
		return *this;
	}
}