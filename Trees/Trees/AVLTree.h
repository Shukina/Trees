
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

	unsigned char height(AVLNode* p)//��������� ������ �������
	{
		if (p)
			return p->height;
		else
			return 0; //������� ������ ��������� �������� : ���� ������� ���, ����� 0 ����� ������ ��������� ���� �������
	}

	int bFactor(AVLNode* p)//�������� ����� ����� ���������
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(AVLNode* p) // ������� ������, ���� ������������������ ��������
	{
		unsigned int hl = height(p->left); // ������ ������ ����
		unsigned int hr = height(p->right); // ������ ������� ����
		if (hl > hr)
			p->height=hl + 1;
		else//hr>=hl
			p->height=hr + 1; // ������ ������� - ��� ������ ���� � ���� ������� ���� 1
	}

	AVLNode* RightRotate(AVLNode* p) // ������ ������� ������ p
	{
		AVLNode* q = p->left;//���������� ������ ���� � 
		p->left = q->right;//�������� ������ ���� � ����, ������� ���� p � q
		q->right = p;//����������� ������� ���� q ��������� �
		if (root == p)
			root = q;
		fixheight(p);//������� ������
		fixheight(q);
		return q;
	}

	AVLNode* LeftRotate(AVLNode* q) // ����� ������� ������ q
	{
		AVLNode* p = q->right;//���������� ������� ���� q
		q->right = p->left;//�������� ������� ���� q ����, ������� ���� q � p
		p->left = q;//����������� ������ ���� p ��������� q
		if (root == q)
			root = p;
		fixheight(q);//������� ������
		fixheight(p);
		return p;
	}
								 
	AVLNode* Balance(AVLNode* p) // ������������ ���� p
	{
		fixheight(p);
		if (bFactor(p) == 2)//���� ����� ��� ������ ������ ������� ������� ������ �������
		{
			if (bFactor(p->right) < 0)
				p->right = RightRotate(p->right);
			return LeftRotate(p);
		}
		if (bFactor(p) == -2)// ���� ������ ��� ����� ������ ������ ������� ����� �������
		{
			if (bFactor(p->left) > 0)
				p->left = LeftRotate(p->left);
			return RightRotate(p);
		}
		return p; // ������������ �� �����
	}
		

	AVLNode* Insert(AVLNode* r, Record w)
	{
		if (root == NULL)//���� ������ ������, �� ������ ������� ����� ���� 
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
			if (w.GetKey() < r->x.GetKey())//���� �������� ������������ ������ ����������, ���� �����
			{
				r->left = Insert(r->left, w);
				r = Balance(r);
			}
			else
				if (w.GetKey() > r->x.GetKey())//���� �������� ������������ ������ ����������, ���� ������
				{
					r->right = Insert(r->right, w);
					r = Balance(r);
				}
				else r->x++;//���� �������� ����������� == ������������, �� ����������� ���������� ���������� �����

				return r;
	}

	void Show(AVLNode *node)//����� � ������� �����������
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


	AVLNode* findmin(AVLNode* p) // ����� ���� � ����������� ������ � ������ p 
	{
		return p->left ? findmin(p->left) : p;
	}

	AVLNode* removemin(AVLNode* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return Balance(p);
	}

	AVLNode* remove(AVLNode* p, int k) // �������� ����� k �� ������ p
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

	//Search??? ��� ����������
	AVLNode* Search(AVLNode* p, int k)
	{
		if (!p)
		{
			cout << "��� ���� � ����� ��������� �����" << endl;
			return 0;
		}
		if (k < p->x.GetKey())
			p->left = Search(p->left, k);
		else if (k > p->x.GetKey())
			p->right = Search(p->right, k);
		else //  k == p->key 
		{
			cout << "���������� ���������� ������� ����� "<<k<<" = "<<p->x.GetValue() << endl;
		}
	}

};
#endif
