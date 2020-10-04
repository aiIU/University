#include <iostream>

using namespace std;

#include "tree.hpp"

template <class T>
void print(Tree<T> &tree) 
{
	Node<int> *temp_ptr;
	if (tree.size() == 0) {
		cout << "tree is empty.\n";
	}
	for (int i = 0; i < tree.size(); ++i) {
		temp_ptr = tree.get(i);
		if (temp_ptr) {
			cout << *(temp_ptr->data()) << endl;
		}
	}
}

int main() 
{}