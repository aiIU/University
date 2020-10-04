#include <iostream>

using namespace std;

#include "tree.hpp"

template <class T>
void print(Tree<T> &tree) 
{
	Node<int> *temp_ptr;
	for (int i = 0; i < tree.size(); ++i) {
		temp_ptr = tree.get(i);
		if (temp_ptr) {
			cout << *(temp_ptr->data()) << endl;
		}
	}
}

int main() 
{
	Tree<int> tree;
	tree.add(100);
	tree.add(200);
	tree.add(150);
	tree.add(150);
	print(tree);

	// tree.remove(200);
	// print(tree);
}