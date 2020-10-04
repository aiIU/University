#ifndef NODE_H
#define NODE_H

template <class T>
class Node{
	
public:
	Node(T *data, int index, Node<T> *parent, Node<T> *left, Node<T> *right);
	Node(const Node &);
	Node<T>& operator=(const Node &);
	~Node();

	//get
	Node<T> *parent(){
		return parent_ptr;
	}
	Node<T> *right(){
		return right_ptr;
	}
	Node<T> *left(){
		return left_ptr;
	}
	T *data(){
		return data_ptr;
	}
	int index(){
		return index_value;
	}

	//set
	void parent (Node<T> *ptr){
		parent_ptr = ptr;
	}
	void right (Node<T> *ptr){
		right_ptr = ptr;
	}
	void left (Node<T> *ptr){
		left_ptr = ptr;
	}
	void data (T *ptr){
		data_ptr = ptr;
	}
	void index (int value){
		index_value = value;
	}

private:
	T *data_ptr;
	int index_value;
	Node<T> *left_ptr, *right_ptr, *parent_ptr;
};



template <class T>
Node<T>::Node(T *data, int index, Node<T> *parent, Node<T> *left, Node<T> *right){
	data_ptr = data;
	index_value = index;
	left_ptr = left;
	right_ptr = right;
	parent_ptr = parent;
}


template <class T>
Node<T>::Node(const Node &other){
	 data_ptr = other.data_ptr;
	 index_value = other.index_value;
	 left_ptr = other.left_ptr;
	 right_ptr = other.right_ptr;
	 parent_ptr = other.parent_ptr;
}

template <class T>
Node<T>& Node<T>::operator=(const Node &other){
	if (this != &other) {
		delete this;
		this = new Node<T>(other);
	}
	return *this;
}

template <class T>
Node<T>::~Node(){
	delete data_ptr;
	delete left_ptr;
	delete right_ptr;
}

#endif