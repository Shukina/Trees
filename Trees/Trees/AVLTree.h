
#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>

using namespace std;

struct AVLNode
{
	Record x;
	AVLNode* left;
	AVLNode* right;
	unsigned char height;

	AVLNode(Record w)
	{
		x = w;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

class AVL
{
private:
	AVLNode* root;

public:
	AVL()
	{
		root = NULL;
	}

	AVLNode* GetRoot()
	{
		return root;
	}

	unsigned char height(AVLNode* p)//получение высоты вершины
	{
		if (p)
			return p->height;
		else
			return 0; //получим высоту следующим способом : если вершины нет, ответ 0 иначе высота поддерева этой вершины
	}

	int bFactor(AVLNode* p)//разность высот между сыновьями
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(AVLNode* p) // обновим высоту, если сбалансированность нарушена
	{
		unsigned int hl = height(p->left); // высота левого сына
		unsigned int hr = height(p->right); // высота правого сына
		if (hl > hr)
			p->height=hl + 1;
		else//hr>=hl
			p->height=hr + 1; // высота вершины - это высота сына с макс высотой плюс 1
	}

	AVLNode* RightRotate(AVLNode* p) // правый поворот вокруг p
	{
		AVLNode* q = p->left;//запоминаем левого сына р 
		p->left = q->right;//присваем левому сыну р узлы, которые мжду p и q
		q->right = p;//присваиваем правому сыну q поддерево р
		if (root == p)
			root = q;
		fixheight(p);//починим дерево
		fixheight(q);
		return q;
	}

	AVLNode* LeftRotate(AVLNode* q) // левый поворот вокруг q
	{
		AVLNode* p = q->right;//запоминаем правого сына q
		q->right = p->left;//присваем правому сыну q узлы, которые мжду q и p
		p->left = q;//присваиваем левому сыну p поддерево q
		if (root == q)
			root = p;
		fixheight(q);//починим дерево
		fixheight(p);
		return p;
	}
								 
	AVLNode* Balance(AVLNode* p) // балансировка узла p
	{
		fixheight(p);
		if (bFactor(p) == 2)//если левый сын сильно больше правого сделаем правый поворот
		{
			if (bFactor(p->right) < 0)
				p->right = RightRotate(p->right);
			return LeftRotate(p);
		}
		if (bFactor(p) == -2)// если правый сын сибно больше левого сделаем левый поворот
		{
			if (bFactor(p->left) > 0)
				p->left = LeftRotate(p->left);
			return RightRotate(p);
		}
		return p; // балансировка не нужна
	}
		

	AVLNode* Insert(AVLNode* r, Record w)
	{
		if (root == NULL)//если дерево пустое, то просто создаем новый узел 
		{
			root = new AVLNode(w);
			return root;
		}
		if (r == NULL)
		{
			r = new AVLNode(w);
			return r;
		}
		else //r!=NULL
			if (w.GetKey() < r->x.GetKey())//если значение вставляемого меньше центрально, идем влево
			{
				r->left = Insert(r->left, w);
				r = Balance(r);
			}
			else
				if (w.GetKey() > r->x.GetKey())//если значение вставляемого больше центрально, идем вправо
				{
					r->right = Insert(r->right, w);
					r = Balance(r);
				}
				else r->x++;//если значение вставлемого == центральному, то увеличиваем количество повторений слова

				return r;
	}

	void Show(AVLNode *node)//вывод в порядке возрастания
	{
		if (node==NULL) 
		{
			return;
		}
		Show(node->left);
		cout << node->x << endl;
		Show(node->right);
	}


	/*void FindMax(AVLNode * node, List & l)
	{
		if (node != NULL)
		{
			FindMax(node->left, l);

			l.SortInsert(node->x);

			FindMax(node->right, l);
		}
	}*/


	AVLNode* findmin(AVLNode* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	AVLNode* removemin(AVLNode* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return Balance(p);
	}

	AVLNode* remove(AVLNode* p, int k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->x.GetKey() )
			p->left = remove(p->left, k);
		else if (k > p->x.GetKey())
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			AVLNode* q = p->left;
			AVLNode* r = p->right;
			delete p;
			if (!r) return q;
			AVLNode* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return Balance(min);
		}

		return Balance(p);
	}

	//Search??? что возвращать
	AVLNode* Search(AVLNode* p, int k)
	{
		if (!p)
		{
			cout << "Нет узла с таким значением ключа" << endl;
			return 0;
		}
		if (k < p->x.GetKey())
			p->left = Search(p->left, k);
		else if (k > p->x.GetKey())
			p->right = Search(p->right, k);
		else //  k == p->key 
		{
			cout << "Количество повторений данного ключа "<<k<<" = "<<p->x.GetValue() << endl;
		}
	}

};
#endif
