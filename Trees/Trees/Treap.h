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
	
	TreapNode(Record w)
	{
		x.SetKey(w.GetKey());
		x.SetValue(w.GetValue());
		unsigned rand_value = 11;
		srand(rand_value);
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

	TreapNode *merge(TreapNode *l, TreapNode *r) 
	{
		if (!l || !r)
		{
			if (l)
				return l;
			else if (r)
				return r;
		}
		if (l->x.GetKey() == r->x.GetKey())
		{
			l->x.SetValue(l->x.GetValue() + 1);
			return l;
		}
		if (l->depth >= r->depth) 
		{
			l->right = merge(l->right, r);
			return l;
		}
		else {
			r->left = merge(l, r->left);
			return r;
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

	void split(TreapNode *t, Key k, TreapNode *&l, TreapNode *&r) //разделяет дерево T на два дерева L и R
	{
		if (!t)
			l = r = NULL;
		else if (t->x.GetKey() <= k) 
		{
			split(t->right, k, t->right, r);
		l = t;
		}
		else {
			split(t->left, k, l, t->left);
			r = t;
		}
	}

	void insert(TreapNode *t, TreapNode*tn) 
	{
		if (!root)
		{
			root = tn;
			return;
		}
		/*TreapNode *tn = new TreapNode(w.GetKey(), w.GetValue());*/
		//TreapNode *t1, *t2;
		///*TreapNode *t = this->GetRoot();*/
		//split(t, tn->x.GetKey(), t1, t2);
		//t = merge(t1, tn);
		//t = merge(t, t2);
		//
		if (!t)
			t = tn;
		else if (tn->x.GetKey() > t->x.GetKey())
		{
			split(t, tn->x.GetKey(), tn->left, tn->right);
			t = tn;
		}
		else
		{
			insert(tn->x.GetKey() < t->x.GetKey() ? t->left : t->right, tn);
		}
	}

	void insert(Record tn)
	{
		if (!root)
		{
			root = new TreapNode(tn);
			//root = tn;
			return;
		}
		/*TreapNode *tn = new TreapNode(w.GetKey(), w.GetValue());*/
		TreapNode *t1, *t2;
		
		split(root, tn.GetKey(), t1, t2);

		root = merge(t1, new TreapNode(tn));
		root = merge(root, t2);
		
		
	}

	void remove(Key key) //удаление всех элементов с ключом key
	{
		TreapNode *t1, *t2, *t3;
		TreapNode *t = this->GetRoot();
		split(t, key-1, t1, t2);
		split(t2, key , t2, t3);
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

	

	
	

	// Делает обход дерева слева-направо и печатает в консоль тройки (ключ узла, приоритет, глубина узла).
	void Show(TreapNode* node, int currentLevel)
	{
		if (node == 0) {
			return;
		}

		Show(node->left, currentLevel + 1);

		cout << "(" << node->x.GetKey() << " " << node->x.GetValue() <<  ") ";

		Show(node->right, currentLevel + 1);
	}
};

#endif
