#ifndef TREE_H
#define TREE_H

#include "node.hpp"

template <class T>
class Tree{
public:
	Tree(); // конструктор по умолчанию
	Tree(Tree const &); // конструктор копирования
	Tree& operator=(Tree const &); // оператор присваивания
	~Tree(); // деструктор

	// добавление элемента
	void add (T const &);

	// удаление элемента (-ов)
	void remove (T const &);

	// взятие элемента по индексу:
	Node<T> *get(int);

	// поиск элементов и возврат позиции больше 0 в случае успеха
	int	find (T const &); 

	// количество узлов в дереве
	int size(){
		return node_amount; 
	} 

private:
	Node<T> *root_ptr;
	int node_amount;

	void update_indexes(); // переопределение индексов всех узлов

	/* 	Функции с именами recursive_*name - являются вспомогательными
		рекурсивными функциями для функций именами *name */
	void recursive_update_indexes(Node<T> *cur_node);
	void recursive_add(Node<T> *, T const &);
	Node<T> *recursive_get(Node<T> *cur_node, int index);
	int recursive_find(Node<T> *cur_node, T const &);

	/* 	При удалении узла существует три варианта развития событий,
		соответсвенно существует три вспомогательные функции: */
	void remove_case_1(Node<T> *);
	void remove_case_2(Node<T> *);
	void remove_case_3(Node<T> *);
};


template <class T>
Tree<T>::Tree(){
	 root_ptr = nullptr;
	 node_amount = 0;
}


template <class T>
Tree<T>::Tree(const Tree &other){
	 root_ptr = nullptr;
	 node_amount = 0;

	if (other.root_ptr != nullptr) {
		root_ptr = new Node<T>(*other.root_ptr);
	}
}


template <class T>
Tree<T>& Tree<T>::operator=(const Tree &other){
	if (this == &other) {
		return *this;
	}

	delete root_ptr;
	root_ptr = nullptr;
	if (other.root_ptr != nullptr) {
		root_ptr = new Node<T>(*other.root_ptr);
	}
	node_amount = other.node_amount;

	return *this;
}


template <class T>
Tree<T>::~Tree(){
	delete root_ptr;
}
/*	Добавление элемента в дерево.
	Требование для T:
		Перегрузка оператора < 

		Всё что меньше - налево,
		а что больше либо равно - направо. */
template <class T>
void Tree<T>::add(T const &data){ // добавление элемента
	if (root_ptr == nullptr) {
		root_ptr = new Node<T>(new T(data), 0, nullptr, nullptr, nullptr);
		node_amount = 1;
		return;
	}
	recursive_add(root_ptr, data);
	update_indexes();
}

template <class T>
void Tree<T>::recursive_add(Node<T> *node_ptr, T const &data){
	if (node_ptr == nullptr) {
		return;
	}
	T const &node_data = *(node_ptr->data());
	if (data < node_data) {
		if (node_ptr->left() != nullptr) {
			recursive_add(node_ptr->left(), data);
		} else {
			node_ptr->left(new Node<T>(new T(data), -1, node_ptr, nullptr, nullptr));
		}
	} else {
		if (node_ptr->right() != nullptr) {
			recursive_add(node_ptr->right(), data);
		} else {
			node_ptr->right(new Node<T>(new T(data), -1, node_ptr, nullptr, nullptr));
			
		}
	}
}


/*	Удаление всех узлов с указанным значением data.
	Требование для T:
		Перегрузка тех же операторов, что и для 
		метода find(), а также !=
	Описание:
		Каждый узел, в data_ptr которого будет
		содержаться data, будет удалён.
		По окончанию дерево будет видоизменено,
		а индексы узлов переписаны 

		Находим узел, который нужно будет удалить,
		определяем одну из трех возможных ситуаций
		и передаём управление соответсвуюей 
		вспомогательной функции, а после обновляем
		индексы. 
		*/
template <class T>
void Tree<T>::remove(T const &data){ // удаление элемента
	int index_to_remove = find(data);
	while (index_to_remove != -1) {
		Node<T> *node_to_remove = get(index_to_remove);
		if (node_to_remove->left() == nullptr && 
				node_to_remove->right() == nullptr) {
			remove_case_1(node_to_remove);
		} else if (node_to_remove->left() && node_to_remove->right()) {
			remove_case_3(node_to_remove);
		} else { // left == nullptr || right == nullptr
			remove_case_2(node_to_remove);
		}

		
		//  update_indexes каждый раз обходит всё дерево
		update_indexes();

		index_to_remove = find(data);
	}
}

/* 	И левый, и правый потомки отсутствуют, а потому 
	убираем связь родителя с потомком */
template <class T>
void Tree<T>::remove_case_1(Node<T> *node_ptr){
	if (root_ptr == node_ptr) { // частный случай при удалении корня
		delete root_ptr;
		root_ptr = nullptr;
        return;
	}

	Node<T> *parent_ptr = node_ptr->parent();

	// опредяем какой именно из потомков передан:
	if (parent_ptr->left() == node_ptr) {
		parent_ptr->left(nullptr);
	} else {
		parent_ptr->right(nullptr);
	}
	delete node_ptr;
}

/*	Один из потомков существует, а потому заменяем 
	потомка родителя на потомка переданного узла */
template <class T>
void Tree<T>::remove_case_2(Node<T> *node_ptr){
	Node<T> *parent_ptr = node_ptr->parent();
	Node<T> *child_ptr = // определяем существующего потомка:
		node_ptr->left() ? node_ptr->left() : node_ptr->right();

	// частный случай при удалении корня с одним потомком
	if (root_ptr == node_ptr) {
		root_ptr = child_ptr;
	} else 	if (parent_ptr->left() == node_ptr) {
        // опредяем какой именно из потомков передан
        // и изменяем соответствующего потомка
		parent_ptr->left(child_ptr);
	} else {
		parent_ptr->right(child_ptr);
	}
	// обнулим оба потомка, так как дольше разбираться
	// какой именно из них существует:
	node_ptr->left(nullptr);
	node_ptr->right(nullptr);
    child_ptr->parent(parent_ptr);
	// обнуление выше осуществленно для того, чтобы 
	// рекурсивнон удаление не срубило всё дерево под корень :)
	delete node_ptr;
}

/*	Существует оба потомка.
	Необходимо поменять data_ptr текущего узла,
	на data_ptr самого левого узла в правом поддереве. */
template <class T>
void Tree<T>::remove_case_3(Node<T> *node_ptr){
	Node<T> *leftmost_ptr = node_ptr->right();
	while (leftmost_ptr->left() != nullptr) {
		leftmost_ptr = leftmost_ptr->left();
	}

	// удаляем старую data и устанавливаем новую:
	delete node_ptr->data();
	node_ptr->data(leftmost_ptr->data());
	leftmost_ptr->data(nullptr);

    if (leftmost_ptr->parent()->left() == leftmost_ptr) {
        leftmost_ptr->parent()->left(leftmost_ptr->right());
    } else {
        leftmost_ptr->parent()->right(leftmost_ptr->right());
    }
	delete leftmost_ptr;
}

template <class T>
Node<T> *Tree<T>::get(int index){ // взятие элемента по индексу (не const)

	return recursive_get(root_ptr, index);
}

template <class T>
Node<T> *Tree<T>::recursive_get(Node<T> *node_ptr, int index){

	if (node_ptr != nullptr) {
		// для хранения и обработки возвращаемого значения:
		Node<T> *temp_ptr; 

		// алгоритм двоичного поиска:
		if (index < node_ptr->index()) {
			temp_ptr = recursive_get(node_ptr->left(), index);
			if (temp_ptr != nullptr) {
				return temp_ptr;
			}
		} else if (index > node_ptr->index()) {
			temp_ptr = recursive_get(node_ptr->right(), index);
			if (temp_ptr != nullptr) {
				return temp_ptr;
			}
		} else {
			return node_ptr;
		}
	}
	return nullptr;
}

/*	Поиск узла с указанным значением data.
	Требование для T:
		Перегрузка операторов <, >
	Возвращаем
		В случае успеха будет возвращен индекс искомого
		узла, иначе -1 */
template <class T>
int Tree<T>::find(T const &data){
	return recursive_find(root_ptr, data);
}

template <class T>
int Tree<T>::recursive_find(Node<T> *node_ptr, T const &data){
	if (node_ptr != nullptr) {
		// для хранения и обработки возвращаемого значения (return value):
		int retvalue = -1;
		// алгоритм двоичного поиска:
		T const &node_data = *(node_ptr->data());
		if (data < node_data) {
			retvalue = recursive_find(node_ptr->left(), data);
			if (retvalue != -1) {
				return retvalue;
			}
		} else if (data > node_data) {
			retvalue = recursive_find(node_ptr->right(), data);
			if (retvalue != -1) {
				return retvalue;
			}
		} else {
			return node_ptr->index();
		}
	}
	return -1;
}

template <class T>
void Tree<T>::update_indexes(){
	node_amount = 0;
	recursive_update_indexes(root_ptr);
}

template <class T>
void Tree<T>::recursive_update_indexes(Node<T> *node_ptr){
	if (node_ptr != nullptr) {
		recursive_update_indexes(node_ptr->left());
		node_ptr->index(node_amount);
		++node_amount;
		recursive_update_indexes(node_ptr->right());
	}
}

#endif