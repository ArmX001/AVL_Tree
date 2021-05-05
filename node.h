#pragma once

template <class T>
struct Node
{
	Node(const T& d, Node<T>* l = nullptr, Node<T>* r = nullptr)
		: left(l),
		right(r),
		data(d),
		height(1)
	{}

	Node<T>* left;
	Node<T>* right;
	T data;
	int height;
};