
#ifndef _LIST_H_
#define _LIST_H_
#include "Record.h"

struct Node
{
	Record data;
	Node *pNext;
};

class List
{
	Node*pHead;
	int maxSize;
	int current;
public:
	List() 
	{
		pHead = NULL;
		current = 0; 
		maxSize = 0; 
	}

	List(int max) 
	{ 
		pHead = NULL; 
		current = 0;  
		maxSize = max; 
	}

	List(List &l)
	{
		Node *p = l.pHead;
		while (p != NULL)
		{
			PushBack(p->data);
			p = p->pNext;
		}
		maxSize = l.maxSize;
	}
	
	bool isEmpty() const 
	{
		return (pHead == 0); 
	}

	Node* GetHead() 
	{
		return pHead;
	}

	void SetMax(int max)
	{
		maxSize = max;
	}

	int GetLength() 
	{
		return current; 
	}

	void PushBack(Record w)//добавление узла с записью w в конец списка
	{
		Node *p = pHead;
		Node *newNode = new Node;
		newNode->data = w;
		newNode->pNext = NULL;
		
		if (isEmpty())// если список пуст
		{
			pHead = newNode;
		}
		else 
		{
			while (p->pNext != NULL) 
			{
				p = p->pNext;
			}
			p->pNext = newNode;
		}
		current++;
	}

	void PushFront(Record w)//добавление  узла с записью w в начало списка
	{
		Node *newNode = new Node;
		newNode->data = w;
		newNode->pNext = pHead;
		pHead = newNode;
		current++;;
	}


	void SortInsert(Record w)//вставка в список по колличеству повторений(value):по убыванию
	{
		if (isEmpty())
		{
			PushBack(w);
			return;
		}
		Node *p = pHead;
		Node *prev = NULL;
		while (p != NULL)
		{
			if (p->data.GetKey() <w.GetKey())
			{
				Node *newNode = new Node;
				newNode->data = w;
				newNode->pNext = p;

				if (prev != NULL)
					prev->pNext = newNode;
				else
					pHead = newNode;

				current++;
				if (current > maxSize) 
					deleteLast();
				return;
			}
			prev = p;
			p = p->pNext;
		}
		//если p->data.GetValue() > w.GetValue()
		if (current<maxSize)
			PushBack(w);
	}

	void deleteLast()//удаление последнего узла в списке
	{
		int i = 0;
		Node *p, *prev;
		p = pHead;
		prev = NULL;
		while (i != maxSize)//дошли до конца
		{
			prev = p;
			p = p->pNext;
			i++;
		}
		delete p;
		prev->pNext = NULL;
	}

	~List()
	{
		Node  *p;
		while (!isEmpty())
		{
			p = pHead;
			pHead = pHead->pNext;
			delete p;
		}
	}

	List& operator = (/*const*/ List &l)
	{
		if (this == &l)
			return *this;

		Node *tmp;
		while (!isEmpty())//удаление старого списка
		{
			tmp = pHead;
			pHead = pHead->pNext;
			delete tmp;
		}

		tmp = l.pHead;//присваивание нового
		while (tmp != NULL)
		{
			PushBack(tmp->data);
			tmp = tmp->pNext;
		}
		maxSize = l.maxSize;
		return *this;
	}


	friend bool operator ==(const List &l1, const List &l2)
	{
		Node* p1 = l1.pHead;
		Node* p2 = l2.pHead;
		while (p1 && p2)
		{
			if (p1->data.GetKey() != p2->data.GetKey() /*|| p1->data.GetValue() != p2->data.GetValue()*/)
				return false;
			p1 = p1->pNext;
			p2 = p2->pNext;
		}
		return (p1 == NULL && p2 == NULL);
	}

	friend bool operator !=(const List &l1, const List &l2)
	{
		return(!(l1 == l2));
	}

	friend ostream& operator << (ostream &os, List &l)
	{
		Node*p = l.pHead;
		while (p != NULL)
		{
			os << p->data << endl;
			p = p->pNext;
		}

		return os;
	}
};
#endif;
