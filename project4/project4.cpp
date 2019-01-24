#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct Node {
  	int data;
  	Node *left, *right;
};

class ListTree {
 	bool isTree;
  	Node *start; // either the root of tree or front of list
public:
	ListTree() {
    	isTree = true; // initially it is a tree
    	start = NULL;
	}

  	~ListTree() {
    		if (isTree)	treeDestory(start);
    		else 	listDestory(start);
  	}

  	void insert(int x) {
    		if (isTree)	treeInsert(x, start);
    		else listInsert(x, start);
  	}

  	void display() {
    		if (isTree)	treeDisplay(start);
    		else	listDisplay(start);
  	}

  	void toggle() {
    		if (isTree)	start = treeToList(start);
    		else	start = listToTree(start);
    		isTree = !isTree;
  	}

private:
  	void treeInsert(int x, struct Node *node) {
    		if (!node) { // if node is invalid
      		// create the start node
      		start = new struct Node;
      		start->data = x;
      		return;
    		}

    		if (x <= node->data) {
      		// if x is smaller than node
      			if (node->left) { // if node has left child
        		// insert x into left child
        		treeInsert(x, node->left);
     			} 
			else { // if node has no left child
        		// create left child with x
        		struct Node *tmp = new struct Node;
        		tmp->data = x;
        		node->left = tmp;
      			}
    		} 
		else if (x > node->data) {
      		// if x is greater than node
      			if (node->right) { // if node has right child
        			// insert x into right child
        			treeInsert(x, node->right);
      			} 
			else { // if node has no right child
        			// create right child with x
        			struct Node *tmp = new struct Node;
        			tmp->data = x;
        			node->right = tmp;
      			}
    		}
  	}

  	void listInsert(int x, struct Node *node, int isRight = -1) {
    		if (!node) { // if node is invalid
      		// create the start node
      		start = new struct Node;
      		start->data = x;
      		return;
    		}

    		if (x <= node->data) {
      			// if x is smaller than node
      			if (node->left) { // if node has left node
        			if (isRight == -1 || isRight == 0) {
          			// if iteration direction is consistent
          				// search insertion postion before node
          				listInsert(x, node->left, 0);
        			} 
				else {
          			// if iteration direction is reversed
          				// insert x right before node
          				struct Node *tmp = new struct Node;
          				tmp->data = x;
          				tmp->left = node->left;
          				tmp->right = node;
          				node->left->right = tmp;
          				node->left = tmp;
        			}
      			} 
			else { // if node has no left child
        			// create left node with x
        			// set this new node as start
        			struct Node *tmp = new struct Node;
        			tmp->data = x;
        			tmp->right = node;
        			node->left = tmp;
        			start = tmp;
      			}
    		} 
		else if (node->data < x) {
      		// if x is greater than node
      			if (node->right) { // if node has right node
        			if (isRight == -1 || isRight == 1) {
          				// if iteration direction is consistent
          				// search insertion postion after node
          				listInsert(x, node->right, 1);
        			} 
				else {
          			// if iteration direction is reversed
          				// insert x right after node
          				struct Node *tmp = new struct Node;
          				tmp->data = x;
          				tmp->left = node;
          				tmp->right = node->right;
          				node->right = tmp;
          				node->right->left = tmp;
        			}
      			} 
			else { // if node has no right child
        			// create right node with x
        			struct Node *tmp = new struct Node;
        			tmp->data = x;
        			tmp->left = node;
        			node->right = tmp;
      			}
    		}
  	}
  	void treeDisplay(struct Node *node) {
    		cout << "(";

    		if (node) {         // if node is valid
      			if (node->left) { // if node has left child
        			// print left child
        			treeDisplay(node->left);
        			cout << " ";
      			}
      		// print node
      			cout << node->data;
      			if (node->right) { // if node has right child
        			cout << " ";
        			// print right child
        			treeDisplay(node->right);
      			}
    		}

    		cout << ")";
    		if (node == start) { // if start node
      			// print new line
      			cout << "\n";
    		}
  	}

  	void listDisplay(struct Node *node) {
    		cout << "[";

    		struct Node *tmp = node;
    		while (tmp) { // iterate nodes
      			// print current node
      			cout << tmp->data;
      			tmp = tmp->right;
      			if (tmp) { // if current node is not the end node
        		// print comma
        			cout << ",";
      			}
    		}

    		cout << "]";
    		if (node == start) { // if start node
      		// print new line
      			cout << endl;
    		}
  	}

  	struct Node *treeToList(struct Node *node, int isRight = 1) {
    		if (node) { // if node is valid
      			struct Node *left;
      			if (node->left) { // if node has left child
        		// convert left child to list
        			left = treeToList(node->left, 0);
        			left->right = node;
        			node->left = left;
      			} 
			else { // if node has no left child
        			left = node;
      			}
      		struct Node *right;
      		if (node->right) { // if node has right child
        		// convert right child to list
        		right = treeToList(node->right, 1);
        		right->left = node;
        		node->right = right;
      		} 
		else { // if node has no right child
        		right = node;
      		}

      		if (isRight) { // if list converted from right child
        		// return the first node
        		while (left->left) {
          			left = left->left;
        		}
        		return left;
      		}
      			// if list converted from left child
      			// return the last node
      		while (right->right) {
        		right = right->right;
      		}
      			return right;
    		}

    		return NULL;
  	}

  	struct Node *listToTree(struct Node *node, int count = -1) {
    		if (node && count != 0) { // if node is valid and count != 0
      			if (count == -1) {      // count is uninitialized
        			// count the number of nodes in list
        			struct Node *tmp = node;
        			count = 0;
        			while (tmp) {
          				tmp = tmp->right;
          				count++;
        			}
      			}

      			if (count == 1) { // only one node in list
        				// return it
        			node->left = NULL;
        			node->right = NULL;
        			return node;
      			}
      				// calculate half of count
      			int half_count = count / 2;
      			struct Node *tmp = node;
      			// iterate up to middle node
      			for (int i = 0; i < half_count; ++i) {
        			tmp = tmp->right;
      			}
      			// convert left part of list to tree
      			struct Node *left = listToTree(node, half_count);
      			// convert right part of list to tree
      			struct Node *right =
          		listToTree(tmp->right, count % 2 ? half_count : half_count - 1);
      			// connect children to middle node
      			tmp->left = left;
      			tmp->right = right;
      			// return middle node
      			return tmp;
    		}

    		return NULL;
  	}

  	void listDestory(struct Node *node) {
    		if (node) { // if node is valid
      			struct Node *tmp;
      			while (node) { // iterate all nodes
        			tmp = node;
        			node = node->right;
        			// delete current node
        		delete tmp;
      			}
    		}
  	}

  	void treeDestory(struct Node *node) {
    		if (node) {         // if node is valid
      			if (node->left) { // if node has left child
        		// delete left child of node
        		treeDestory(node->left);
      		}
      		if (node->right) { // if node has right child
        		// delete right child of node
        		treeDestory(node->right);
      		}
      		// delete node
      		delete node;
    		}
  	}
};

int main(void) {
  	ListTree lt;

  	string cmd;
  	int param;

  	while (cin >> cmd) {
    		if (cmd == "insert") {
      		cin >> param;
      		lt.insert(param);
    		} 
		else if (cmd == "display") {
      			lt.display();
    		} 
		else if (cmd == "toggle") {
      			lt.toggle();
    		}
  	}

  // --------------------------------

  // lt.insert(1);
  // lt.display();

  // lt.insert(5);
  // lt.display();

  // lt.insert(0);
  // lt.display();

  // lt.insert(7);
  // lt.insert(3);
  // lt.display();

  // lt.insert(8);
  // lt.insert(2);
  // lt.display();

  // lt.insert(6);
  // lt.insert(4);
  // lt.display();
  // lt.toggle();
  // lt.display();
  // lt.toggle();
  // lt.display();

  // lt.insert(11);
  // lt.insert(9);
  // lt.insert(13);
  // lt.display();
  // lt.toggle();
  // lt.display();

  // lt.insert(10);
  // lt.insert(12);
  // lt.display();
  // lt.toggle();
  // lt.display();

  // -----------------------------------------------

  return 0;
}
