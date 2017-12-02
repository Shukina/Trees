#ifndef _TREAP_H 
#define _TREAP_H

#include "Record.h"
#include <iostream>

using namespace std;

struct TreapNode
{
	Record x;
	int depth;//глубина(рандом)
	TreapNode *left;
	TreapNode *right;
	
	TreapNode(Key key, int value)
	{
		x.SetKey(key);
		x.SetValue(value);
		depth = rand() % 10;
		left = NULL;
		right = NULL;
	}
};

class Treap
{
private:
	TreapNode* root;

public:
	Treap()
	{
		root = NULL;
	}

	TreapNode* GetRoot()
	{
		return root;
	}

	TreapNode *merge(TreapNode *a, TreapNode *b) 
	{
		if (!a || !b)
		{
			if (a)
				return a;
			else if (b)
				return b;
		}
		if (a->depth > b->depth) 
		{
			a->right = merge(a->right, b);
			return a;
		}
		else {
			b->left = merge(a, b->left);
			return b;
		}
	}

	TreapNode* Search(TreapNode* r, Key key) //like BST
	{
		if (r == NULL || r->x.GetValue() == NULL) return NULL;

		if (key == r->x.GetKey())
		{
			return r;
		}
		if (key < r->x.GetKey())
		{
			return Search(r->left, key);
		}
		return Search(r->right, key);
	}

	void split(TreapNode *t, Key k, TreapNode *&a, TreapNode *&b) 
	{
		if (!t)
			a = b = NULL;
		else if (t->x.GetKey() < k) 
		{
			split(t->right, k, t->right, b);
			a = t;
		}
		else {
			split(t->left, k, a, t->left);
			b = t;
		}
	}

	void insert(Record w) 
	{
		TreapNode *tn = new TreapNode(w.GetKey(), w.GetValue());
		TreapNode *t1, *t2;
		TreapNode *t = this->GetRoot();
		split(t, w.GetKey(), t1, t2);
		t = merge(t1, tn);
		t = merge(t, t2);
	}

	void remove(Key key) //удаление всех элементов с ключом key
	{
		TreapNode *t1, *t2, *t3;
		TreapNode *t = this->GetRoot();
		split(t, key, t1, t2);
		split(t2, key + 1, t2, t3);
		t = merge(t1, t3);
		dispose(t2);
	}

	void dispose(TreapNode *n) //освобождение памяти от узла n
	{
		if (n == NULL)
			return;
		dispose(n->left);
		dispose(n->right);
		delete n;
	}

	void Show(TreapNode *node)//вывод в порядке возрастания
	{
		if (node == NULL)
		{
			return;
		}
		Show(node->left);
		cout << node->x << endl;
		Show(node->right);
	}
};

#endif
