#include <iostream>
#include <string>

using namespace std;

// ���� ��������� ������.
struct CTreapNode {
	int Key; // ����.
	int Priority; // ��������� ����.
	CTreapNode* Left; // ����� �������� ����.
	CTreapNode* Right; // ������ �������� ����.

	CTreapNode(int _key, int _priority) : Key(_key), Priority(_priority),
		Left(0), Right(0) {}
};

// ����� ��������� ������.
class CTreap {
public:
	// ����������� ������� ������ ������.
	CTreap() : root(0) {}
	// ���������� ������� ��� �������� ������.
	~CTreap();

	// �������� ���� (key, priority) � ������.
	// key � priority ������ ���� ��������� �� ����������� ��������� ������.
	void Insert(int key, int priority);
	// ������� ������ � ������� ������� �����-�������.
	void ShowLeftToRight();
	// ������� ������ � �������, ������� ��� �� ���: �������� ��������� �����, "�����"
	// ������� ������������� ������ ������ �� ����, "������" ������� - ����� ������.
	void Show();

private:
	CTreapNode* root; // ������ ������.

	void deleteSubTree(CTreapNode* node);
	void split(CTreapNode* node, int key, CTreapNode*& leftTree, CTreapNode*& rightTree);
	CTreapNode* merge(CTreapNode* leftTree, CTreapNode* rightTree);
	void printLeftToRightWithLevel(CTreapNode* node, int currentLevel);
	void printAsTree(CTreapNode* node, int currentLevel);
};

CTreap::~CTreap()
{
	deleteSubTree(root);
}

// ��������� ���������, ������ �������� �������� node.
void CTreap::deleteSubTree(CTreapNode* node)
{
	if (node == 0) {
		// ����� �� ����� ������.
		return;
	}

	deleteSubTree(node->Left);
	node->Left = 0;
	deleteSubTree(node->Right);
	node->Right = 0;

	delete node;
}

// ��������� ���� �� ��� �����.
void CTreap::split(CTreapNode* node, int key, CTreapNode*& leftTree, CTreapNode*& rightTree)
{
	if (node == 0) {
		leftTree = 0;
		rightTree = 0;
		return;
	}

	if (node->Key <= key) {
		split(node->Right, key, node->Right, rightTree);
		leftTree = node;
	}
	else {
		split(node->Left, key, leftTree, node->Left);
		rightTree = node;
	}
}

// ������� ��� ��������� ������ � ����. �������� � leftTree ������ ���� ������ ��������� rightTree.
CTreapNode* CTreap::merge(CTreapNode* leftTree, CTreapNode* rightTree)
{
	if (leftTree == 0) {
		return rightTree;
	}
	if (rightTree == 0) {
		return leftTree;
	}

	if (rightTree->Priority > leftTree->Priority) {
		rightTree->Left = merge(leftTree, rightTree->Left);
		return rightTree;
	}
	else {
		leftTree->Right = merge(leftTree->Right, rightTree);
		return leftTree;
	}
}

// ����������� ������������� ������ �������.
void CTreap::Insert(int key, int priority)
{
	if (root == 0) {
		root = new CTreapNode(key, priority);
		return;
	}

	CTreapNode* leftTree;
	CTreapNode* rightTree;
	split(root, key, leftTree, rightTree);

	root = merge(leftTree, new CTreapNode(key, priority));
	root = merge(root, rightTree);
}

void CTreap::ShowLeftToRight()
{
	printLeftToRightWithLevel(root, 0);
	cout << endl;
}

// ������ ����� ������ �����-������� � �������� � ������� ������ (���� ����, ���������, ������� ����).
void CTreap::printLeftToRightWithLevel(CTreapNode* node, int currentLevel)
{
	if (node == 0) {
		return;
	}

	printLeftToRightWithLevel(node->Left, currentLevel + 1);

	cout << "(" << node->Key << " " << node->Priority << " " << currentLevel << ") ";

	printLeftToRightWithLevel(node->Right, currentLevel + 1);
}

void CTreap::Show()
{
	printAsTree(root, 0);
}

// ������ ����� ������ �����-������� � �������� � ������� ������, ���������� �� ���.
void CTreap::printAsTree(CTreapNode* node, int currentLevel)
{
	if (node == 0) {
		return;
	}

	printAsTree(node->Left, currentLevel + 1);

	cout << string(currentLevel, '\t') << "(" << node->Key << " " << node->Priority << ")" << endl;

	printAsTree(node->Right, currentLevel + 1);
}

int main(int argc, const char * argv[]) {
	// ������������ �������� ���������� ������.
	CTreap treap;
	treap.Insert(30, 20);
	treap.ShowLeftToRight();
	treap.Insert(20, 15);
	treap.ShowLeftToRight();
	treap.Insert(40, 10);
	treap.ShowLeftToRight();
	treap.Insert(50, 30);
	treap.ShowLeftToRight();
	treap.Insert(30, 20);
	treap.ShowLeftToRight();
	treap.Insert(35, 40);
	treap.ShowLeftToRight();
	treap.Insert(34, 17);
	treap.ShowLeftToRight();

	cout << endl << "��������� (������ ������ ������������� �����):" << endl;

	treap.Show();

	return 0;
}