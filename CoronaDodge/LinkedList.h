#pragma once
template <class T>
struct Node;

template <class T>
using CompareFunc = bool(Node<T>*);

template <class T>
using ForEachCallback = void(Node<T>*, void*);

template <class T>
struct Node
{
	Node* pPrev = nullptr;
	Node* pNext = nullptr;
	T* pElement = nullptr;
	Node(T* pElement)
	{
		this->pElement = pElement;
	}

	void add(T* pElement)
	{
		if (pNext)
			pNext->add(pElement);
		else
		{
			pNext = new Node<T>(pElement);
			pNext->pPrev = this;
		}
	}

	void remove_if(CompareFunc<T> cf)
	{
		if (!cf(this))
		{
			pNext->remove_if(cf);
		}
		else
		{
			pPrev = pNext;
			pNext = pPrev;
			delete pElement;
		}
	}

	void forEach(ForEachCallback<T> callBack, void* pExtra)
	{
		callBack(this, pExtra);
		if (pNext)
			pNext->forEach(callBack, pExtra);
	}
};


template <class T>
class LinkedList
{
	Node<T>* pHead = nullptr;
public:
	LinkedList() = default;
	LinkedList(T* pHead)
	{
		this->pHead = new Node(pHead);
	}

	void add(T* pElement)
	{
		if (!pHead)
		{
			pHead = new Node<T>(pElement);
			return;
		}

		pHead->add(pElement);
	}

	void remove_if(CompareFunc<T> cf)
	{
		pHead->remove_if(cf);
	}

	void forEach(ForEachCallback<T> callBack, void* pExtra = nullptr)
	{
		if (pHead)
		{
			pHead->forEach(callBack, pExtra);
		}
	}
};
