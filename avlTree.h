#pragma once

#include "node.h"

#include <iostream>

template <class T>
class AVLTree
{
public:
	AVLTree(Node<T>* r = nullptr)
		: m_root(r)
	{}

	void insert(const T&);
	void remove(const T&);

	void inorderTraverse() const;
	void preorderTraverse() const;
	void postorderTraverse() const;

private:

	Node<T>* insertHelper(Node<T>*, const T&);
	Node<T>* deleteHelper(Node<T>*, const T&);
	Node<T>* leftRotation(Node<T>*);
	Node<T>* rightRotation(Node<T>*);

	Node<T>* getInorderSuccessor(Node<T>*) const;
	Node<T>* getInorderDecessor(Node<T>*) const;
	void inorderHelper(Node<T>*) const;
	void preorderHelper(Node<T>*) const;
	void postorderHelper(Node<T>*)const;
	int getBalanceFactor(Node<T>*) const;
	int height(Node<T>*) const;
	int max(int, int) const;

	Node<T>* m_root;
};

template <class T>
int AVLTree<T>::height(Node<T>* n) const
{
	if (n == nullptr)
		return 0;
	return n->height;
}

template <class T>
int AVLTree<T>::getBalanceFactor(Node<T>* n) const
{
	if (n == nullptr)
		return 0;
	return height(n->left) - height(n->right);
}

template <class T>
int AVLTree<T>::max(int x, int y) const
{
	return (x > y) ? x : y;
}

template <class T>
Node<T>* AVLTree<T>::getInorderSuccessor(Node<T>* n) const
{
	Node<T>* temp = n;

	while (temp->left != nullptr)
	{
		temp = temp->left;
	}

	return temp;
}

template <class T>
Node<T>* AVLTree<T>::getInorderDecessor(Node<T>* n) const
{
	Node<T>* temp = n;

	while (temp->right != nullptr)
	{
		temp = temp->right;
	}

	return temp;
}

template <class T>
Node<T>* AVLTree<T>::leftRotation(Node<T>* n)
{
	Node<T>* r = n->right;
	Node<T>* t = r->left;

	r->left = n;
	n->right = t;

	n->height = 1 + max(height(n->left), height(n->right));
	r->height = 1 + max(height(r->left), height(r->right));

	return r;
}

template <class T>
Node<T>* AVLTree<T>::rightRotation(Node<T>* n)
{
	Node<T>* l = n->left;
	Node<T>* t = l->right;

	l->right = n;
	n->left = t;

	n->height = 1 + max(height(n->left), height(n->right));
	l->height = 1 + max(height(l->left), height(l->right));

	return l;
}

template <class T>
void AVLTree<T>::insert(const T& key)
{
	m_root = insertHelper(m_root, key);
}

template <class T>
Node<T>* AVLTree<T>::insertHelper(Node<T>* t, const T& data)
{
	if (t == nullptr)
	{
		return new Node<T>(data);
	}

	if (data > t->data)
	{
		t->right = insertHelper(t->right, data);
	}
	else if (data < t->data)
	{
		t->left = insertHelper(t->left, data);
	}
	else
	{
		return t;
	}

	t->height = 1 + max(height(t->left), height(t->right));

	int bfact = getBalanceFactor(t);

	if (bfact > 1 && data < t->left->data)
	{
		return rightRotation(t);
	}

	if (bfact < -1 && data > t->right->data)
	{
		return leftRotation(t);
	}

	if (bfact > 1 && data > t->left->data)
	{
		t->left = leftRotation(t->left);
		return rightRotation(t);
	}

	if (bfact < -1 && data < t->right->data)
	{
		t->right = rightRotation(t->right);
		return leftRotation(t);
	}

	return t;
}

template <class T>
void AVLTree<T>::remove(const T& data)
{
	m_root = deleteHelper(m_root, data);
}

template <class T>
Node<T>* AVLTree<T>::deleteHelper(Node<T>* n, const T& data)
{
	if (n == nullptr)
		return n;

	if (data < n->data)
	{
		n->left = deleteHelper(n->left, data);
	}
	else if (data > n->data)
	{
		n->right = deleteHelper(n->right, data);
	}
	else
	{
		if (n->left == nullptr || n->right == nullptr)
		{
			Node<T>* temp = (n->left) ? n->left : n->right;

			if (temp == nullptr)
			{
				temp = n;
				n = nullptr;
			}
			else
			{
				*n = *temp;
			}
			delete temp;
		}
		else
		{
			Node<T>* temp = getInorderDecessor(n->left);
			n->data = temp->data;
			n->left = deleteHelper(n->left, temp->data);
		}
	}

	if (n == nullptr)
		return n;

	n->height = 1 + max(height(n->left), height(n->right));

	int bfact = getBalanceFactor(n);

	if (bfact > 1 && getBalanceFactor(n->left) >= 0)
	{
		return rightRotation(n);
	}

	if (bfact > 1 && getBalanceFactor(n->left) < 0)
	{
		n->left = leftRotation(n->left);
		return rightRotation(n);
	}

	if (bfact < -1 && getBalanceFactor(n->right) <= 0)
	{
		return leftRotation(n);
	}

	if (bfact < -1 && getBalanceFactor(n->right) > 0)
	{
		n->right = rightRotation(n->right);
		return leftRotation(n);
	}

	return n;
}

template <class T>
void AVLTree<T>::preorderTraverse() const
{
	preorderHelper(m_root);
}

template <class T>
void AVLTree<T>::postorderTraverse() const
{
	postorderHelper(m_root);
}

template <class T>
void AVLTree<T>::inorderTraverse() const
{
	inorderHelper(m_root);
}

template<class T>
void AVLTree<T>::preorderHelper(Node<T>* t) const
{
	if (t == nullptr)
		return;

	std::cout << t->data << " ";
	preorderHelper(t->left);
	preorderHelper(t->right);
}

template<class T>
void AVLTree<T>::postorderHelper(Node<T>* t) const
{
	if (t == nullptr)
		return;

	postorderHelper(t->left);
	postorderHelper(t->right);
	std::cout << t->data << " ";
}

template<class T>
void AVLTree<T>::inorderHelper(Node<T>* t) const
{
	if (t == nullptr)
		return;

	inorderHelper(t->left);
	std::cout << t->data << " ";
	inorderHelper(t->right);
}
