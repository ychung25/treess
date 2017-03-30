#pragma once
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;




template<typename T>
class AVLTree
{
public:
	void insert(const T& t)
	{
		_root = insert(t, _root);
	}
	bool find(const T& t)
	{
		return find(t, _root);
	}
	unsigned int size()
	{
		return _size;
	}
	void erase(const T& t)
	{
        _root = erase(t, _root);
	}

	vector<T> getData()
	{
		vector<T> toReturn;
		inorder(toReturn, _root);
		return toReturn;
	}


private:

	template<typename T>
	struct Node
	{
		T data;
		int level = 0;
		Node<T>* left = nullptr;
		Node<T>* right = nullptr;
	};

	bool find(const T& t, Node<T>* node)
	{
		if (node == nullptr)
		{
			return false;
		}
		else if (node->data == t)
		{
			return true;
		}
		else
		{
			if (t < node->data)
			{
				return find(t, node->left);
			}
			else
			{
				return find(t, node->right);
			}
		}
	}

    Node<T>* erase(const T& t, Node<T>* node)
    {
        if (node == nullptr) { return node; }
        if (t < node->data)
        {
			node->left = erase(t, node->left);
			int leftNodeLevel = getLevel(node->left);
			int rightNodeLevel = getLevel(node->right);
			if(std::abs(leftNodeLevel - rightNodeLevel) > 1)
			{
				return balance(node);
			}
			else
			{
				node->level = adjustLevel(node);
			}
			return node;
        }
        else if (t > node->data)
        {
			node->right = erase(t, node->right);
			int leftNodeLevel = getLevel(node->left);
			int rightNodeLevel = getLevel(node->right);
			if(std::abs(leftNodeLevel - rightNodeLevel) > 1)
			{
				return balance(node);
			}
			else
			{
				node->level = adjustLevel(node);
			}
			return node;
        }
        else // t == node->data
        {
            _size--;
			if(node->left == nullptr && node->right == nullptr)
			{
				delete node;
				return nullptr;
			}
			else if(node->left != nullptr && node->right == nullptr)
			{
				Node<T>* temp = node->left;
				delete node;
				return temp;
			}
			else if(node->left == nullptr && node->right != nullptr)
			{
				Node<T>* temp = node->right;
				delete node;
				return temp;
			}
			else // t->left != nullptr && t->right != nullptr
			{
				Node<T>* nextNode = findNextNode(node);
				return erase(nextNode->data, node);
			}
        }
    }

	Node<T>* insert(const T& t, Node<T>* node)
	{
		if (node == nullptr)
		{
			_size++;
			Node<T>* newNode = new Node<T>();
			newNode->data = t;
			newNode->level = 1;
			return newNode;
		}
		else
		{
			if (t < node->data)
			{
				node->left = insert(t, node->left);
			}
			else if (t > node->data)
			{
				node->right = insert(t, node->right);
			}

			int leftNodeLevel = getLevel(node->left);
			int rightNodeLevel = getLevel(node->right);
			if (abs(leftNodeLevel - rightNodeLevel) > 1)
			{
				return balance(node);
			}
			else
			{
				node->level = adjustLevel(node);
				return node;
			}
		}
	}



	Node<T>* balance(Node<T>* x)
	{
		Node<T>* y = nullptr;
		Node<T>* z = nullptr;

		if (getLevel(x->left) > getLevel(x->right))
		{
			y = x->left;
			if (getLevel(y->left) > getLevel(y->right))
			{
				z = y->left; //LL
				return LLbalance(x, y, z);
			}
			else
			{
				z = y->right; //LR
				return LRbalance(x, y, z);
			}
		}
		else // x->left->level < x->right->level
		{
			y = x->right;
			if (getLevel(y->left) > getLevel(y->right))
			{
				z = y->left; //RL
				return RLbalance(x, y, z);
			}
			else
			{
				z = y->right; //RR
				return RRbalance(x, y, z);
			}
		}
	}

	Node<T>* LLbalance(Node<T>* x, Node<T>* y, Node<T>* z)
	{
		x->left = y->right;
		y->right = x;

		z->level = adjustLevel(z);
		x->level = adjustLevel(x);
		y->level = adjustLevel(y);
		return y;
	}
	Node<T>* LRbalance(Node<T>* x, Node<T>* y, Node<T>* z)
	{
		y->right = z->left;
		z->left = y;

		x->left = z->right;
		z->right = x;

		x->level = adjustLevel(x);
		y->level = adjustLevel(y);
		z->level = adjustLevel(z);
		return z;
	}
	Node<T>* RLbalance(Node<T>* x, Node<T>* y, Node<T>* z)
	{
		x->right = z->left;
		z->left = x;

		y->left = z->right;
		z->right = y;

		x->level = adjustLevel(x);
		y->level = adjustLevel(y);
		z->level = adjustLevel(z);
		return z;
	}
	Node<T>* RRbalance(Node<T>* x, Node<T>* y, Node<T>* z)
	{
		x->right = y->left;
		y->left = x;

		z->level = adjustLevel(z);
		x->level = adjustLevel(x);
		y->level = adjustLevel(y);
		return y;
	}

	int adjustLevel(Node<T>* node)
	{
		int leftNodeLevel = getLevel(node->left);
		int rightNodeLevel = getLevel(node->right);
		return std::max(leftNodeLevel, rightNodeLevel) + 1;
	}

	unsigned int getLevel(Node<T>* node)
	{
		if (node)
			return node->level;
		return 0;
	}

	void inorder(vector<T>& vec, Node<T>* node)
	{
		if (!node) { return; }
		inorder(vec, node->left);
		vec.push_back(node->data);
		inorder(vec, node->right);
	}
	
	Node<T>* findNextNode(Node<T>* node)
	{
		Node<T>* next = node->right;
		while(next->left)
		{
			next = next->left;
		}
		return next;
	}

	Node<T>* _root = nullptr;
	unsigned int _size = 0;
};