
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
};
#endif
