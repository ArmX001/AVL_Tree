#include <iostream>

#include "avlTree.h"

int main() {
	AVLTree<int> tree;

	tree.insert(2);
	tree.insert(8);
	tree.insert(10);
	tree.insert(1);
	tree.insert(15);
	tree.insert(17);
	tree.insert(9);
	tree.insert(12);
	tree.insert(11);
	tree.insert(13);
	tree.insert(14);
	tree.insert(5);
	tree.insert(7);

	std::cout << std::endl;
	tree.preorderTraverse();

	tree.remove(8);
	tree.remove(12);
	tree.remove(7);
	tree.remove(10);
	tree.remove(9);

	std::cout << std::endl;
	tree.preorderTraverse();


	system("pause > bin");
	return 0;
}