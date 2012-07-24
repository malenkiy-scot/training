// simpleBinTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>

#define NIL 0

template <typename T>
class BinTree {
public:
	class Node {
		friend class BinTree;

		Node* left;
		Node* right;
		Node* parent;
		Node() {}
	public:
		T key;
		Node(T key_): left(NIL),right(NIL),parent(NIL) {
			key = key_;
		}
	};

public:
	typedef Node* NODE;

private:
	NODE root;

	void insertNode(NODE root_, NODE node_) {
		NODE next = NIL;
		NODE* branch = NIL;
		do {
			if(node_->key >= root_->key) {
				next = root_->right;
				branch = &(root_->right);
			} else {
				next = root_->left;
				branch = &(root_->left);
			}
			if (next != NIL) {
				root_ = next;
			}
		} while (next != NIL);

		node_->parent = root_;
		*branch = node_;
		return;
	}
	
	void walkTree(NODE root_, std::ostream& out, int indent) {
		if(root_ == NIL) {
			return;
		}
		walkTree(root_->left, out, indent+1);
		for (int i = 0; i < indent; i++) {
			out << "  ";
		}
		out << root_->key << "-\n";
		walkTree(root_->right, out, indent+1);
	}

	NODE maxNode(NODE root_) {
		while (root_->right != NIL) {
			root_ = root_->right;
		}
		return root_;
	}

	NODE minNode(NODE root_) {
		while (root_->left != NIL) {
			root_ = root_->left;
		}
		return root_;
	}

public:
	BinTree(): root(NIL) {
	}

	NODE insert(T key_) {
		NODE node = new Node(key_);
		if(root == NIL) {
			root = node;
			return root;
		}
		insertNode(root, node);
		return node;
	}

	void walk(std::ostream& out) {
		walkTree(root, out, 0);
		out << "\n\n";
	}

	NODE max() {
		if (root == NIL) {
			return NIL;
		}
		return maxNode(root);
	}

	NODE pred(NODE node_) {
		if (node_->left != NIL) {
			return maxNode(node_->left);
		}
		NODE parent = node_->parent;
		while (parent != NIL && parent->right != node_) {
			node_ = parent;
			parent = parent->parent;
		}
		return parent;
	}

	void remove(NODE node_) {
		if (node_->left == NIL) {
			if (node_->parent->left == node_) {
				node_->parent->left = node_->right;
			} else {
				node_->parent->right = node_->right;
			}
		} else if (node_->right == NIL) {
			if (node_->parent->left == node_) {
				node_->parent->left = node_->left;
			} else {
				node_->parent->right = node_->left;
			}
		} else {
			NODE prev = pred(node_);
			node_->key = prev->key;
			remove(prev);
			return;
		}
		delete node_;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	BinTree<int> myTree;

	myTree.insert(5);
	BinTree<int>::NODE n8 = myTree.insert(8);
	myTree.insert(9);
	myTree.insert(1);
	myTree.insert(6);
	myTree.insert(3);
	myTree.insert(12);
	myTree.insert(10);
	myTree.insert(2);
	myTree.insert(4);
	myTree.insert(11);
	myTree.insert(13);
	myTree.insert(7);

	myTree.walk(std::cout);

	BinTree<int>::NODE max = myTree.max();
	assert(max->key == 13);

	for (int j = 0; j < 4; j++) {
		max = myTree.pred(max);
	}
	assert(max->key == 9);

	myTree.remove(n8);
	myTree.walk(std::cout);

	return 0;
}
