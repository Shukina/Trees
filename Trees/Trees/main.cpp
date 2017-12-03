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
	std::map<Key, int>::iterator RBTr_it;

	vector<Key> Bin;
	vector<Key>::iterator Bin_it;

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
		TreapNode* temp = TreapTr.GetRoot();
		TreapTr.insert(w);
	}
	cout << "Файл считался" << endl;

	cout << "AVL:" << endl;
	AVLTr.Show(AVLTr.GetRoot()); 
	cout << endl;
	AVLTr.remove(AVLTr.GetRoot(), 4);
	AVLTr.Show(AVLTr.GetRoot());
	cout << endl;
	AVLTr.Search(AVLTr.GetRoot(), 2);
	cout << endl;

	cout << "Красно-белое дерево(ключ=кол-во повторений) : " << endl;
	for_each(RBTr.begin(), RBTr.end(), show);
	cout << endl;
	//delete 3
	for (RBTr_it = RBTr.begin(); RBTr_it != RBTr.end(); )
	{
		if (RBTr_it->first == 3)
			RBTr.erase(RBTr_it++);
		else
			RBTr_it++;
	}
	for_each(RBTr.begin(), RBTr.end(), show);
	cout << endl;
	//search 5
	for (RBTr_it = RBTr.begin(); RBTr_it != RBTr.end(); )
	{
		if (RBTr_it->first == 5)
		{
			cout << "Количество повторений данного ключа " << 5 << " = " << RBTr_it->second << endl;
			RBTr_it++;
		}
		else
			RBTr_it++;
	}



	std::sort(Bin.begin(), Bin.end());
	cout << "Отсортированный массив : " << endl;
	for (Bin_it = Bin.begin(); Bin_it != Bin.end(); ++Bin_it)
		std::cout << ' ' << *Bin_it;
	std::cout << '\n';
	//delete 4
	for (Bin_it = Bin.begin(); Bin_it != Bin.end(); )
	{
		if (*Bin_it == 4)
		{
			Bin_it=Bin.erase(Bin_it);
		}
		else
			++Bin_it;
	}
	cout << endl;
	for (std::vector<Key>::iterator it = Bin.begin(); it != Bin.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	cout << "Treap:" << endl;
	TreapTr.Show(TreapTr.GetRoot(), 0);
	cout << endl;
	//delete 6
	TreapTr.remove(6);
	TreapTr.Show(TreapTr.GetRoot(), 0);
	cout << endl;
		
		
		return 0;
}


