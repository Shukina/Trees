#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Record.h"
#include "List.h"
//#include "HashTable.h"
//#include "BST_tree.h"
#include "AVLTree.h"
#include "Treap.h"

#include <iterator>
#include <algorithm>

using namespace std;

struct myclass {
	bool operator() (int i, int j) { return (i<j); }
} myobject;

typedef double Key;

typedef pair< Key,int> Key_Pair;

void show(pair< Key,int> p)
{
	cout << p.first << " = " << p.second << endl;
}


 int main()
{
	 int num = 0;
	setlocale(LC_ALL, "Russian");
	/*HashTable HTable;
	BST BSTree;*/
	AVL AVLTr;
	std::map<Key,int> RBTr;
	vector<Key> Bin;
	Treap TreapTr;

	ifstream fin;
	int i = 0;


	double buff;
	Record w;
	fin.open("text.txt");
	if (!fin)
	{
		cout << "Ошибка открытия файла" << endl;
		return 0;
	}
	while (!fin.eof())
	{
		fin >> buff;

		w.SetKey(buff);
		w.SetValue(1);
		/*	HTable.Insert(w);
		BSTree.Insert(BSTree.GetRoot(), w);*/
		AVLTr.Insert(AVLTr.GetRoot(), w);
		//_______//
		if (RBTr.count(w.GetKey()) == 1) //элемент существует
		{
			num = (RBTr.find(w.GetKey())->second) ;
		}
		RBTr.erase(w.GetKey());
		RBTr.insert(Key_Pair(w.GetKey(),num+ 1));
		num = 0;
		//_______//
		Bin.push_back(w.GetKey());
		TreapTr.insert(w);
	}
	cout << "Файл считался" << endl;
	int n = 10;
	//создаем списки для каждого вида длинной 10
	/*List resultForAVL(n);*/
	/*AVLTr.FindMax(AVLTr.GetRoot(), resultForAVL);*/

	cout << "AVL:" << endl;
	/*cout << resultForAVL;
	cout << endl;*/

	AVLTr.Show(AVLTr.GetRoot());

	cout << "Красно-белое дерево(ключ=кол-во повторений) : " << endl;
	for_each(RBTr.begin(), RBTr.end(), show);

	cout << endl;
	std::sort(Bin.begin(), Bin.end());
	cout << "Отсортированный массив : " << endl;
	for (std::vector<Key>::iterator it = Bin.begin(); it != Bin.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	cout << "Treap:" << endl;
	/*cout << resultForAVL;
	cout << endl;*/

	TreapTr.Show(TreapTr.GetRoot());
		
		
		
		return 0;
}


