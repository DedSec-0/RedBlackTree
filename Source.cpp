#include <iostream>
using namespace std;

struct Node
{
	int data;
	string color;
	Node *left;
	Node *right;
	Node *parent;

	Node() {
		data = 0;
		color = "Red";
		left = right = parent = nullptr;
	}
};

class RBT
{
	Node *root;

	void rotateLeft(Node* Parent, Node* Child) {
		if (Child->left != nullptr)
			Parent->right = Child->left;
		else
			Parent->right = nullptr;
		Child->left = Parent;

		if (Parent != root) {
			if (Parent->parent->left == Parent)
				Parent->parent->left = Child;
			else
				Parent->parent->right = Child;
			Child->parent = Parent->parent;
			Parent->parent = Child;
		}
		else {
			Child->parent = nullptr;
			root = Child;
		}
		Parent->color = "Red";
		Child->color = "Black";
	}

	void rotateRight(Node* Parent, Node* Child) {
		if (Child->right != nullptr)
			Parent->left = Child->right;
		else
			Parent->right = nullptr;
		Child->right = Parent;

		if (Parent != root) {
			if (Parent->parent->left == Parent)
				Parent->parent->left = Child;
			else
				Parent->parent->right = Child;
			Child->parent = Parent->parent;
			Parent->parent = Child;
		}
		else {
			Child->parent = nullptr;
			root = Child;
		}
		Parent->color = "Red";
		Child->color = "Black";
	}

	int insert(Node* &N, int val, Node* Parent) {
		if (N == nullptr) {
			N = new Node;
			N->data = val;
			N->parent = Parent;
			if (Parent->color == "Black")
				return true;
			else
				return false;
		}
		if (val < N->data) {
			int flag = insert(N->left, val, N);
			if (flag == 1)
				return true;

			if (Parent->left == N) {
				if (Parent->right != nullptr && Parent->right->color == "Red") {			//Re-Colored
					N->color = "Black";
					Parent->right->color = "Black";
					Parent->color = "Red";
					return 2;
				}
				else if (Parent->color == "Red" && N->color == "Red") {
					if ((Parent->parent->right == Parent && Parent->parent->left->color != "Red") || (Parent->parent->left == Parent && Parent->parent->right->color != "Red")) {
						rotateRight(Parent->parent, Parent);
						return true;
					}
				}
				else if (flag != 2)
					rotateRight(Parent, N);		//LL->R Rotation
				return true;
			}
			else if (Parent->right == N) {
				if (Parent->left != nullptr  && Parent->left->color == "Red") {			//Re-Colored
					N->color = "Black";
					Parent->left->color = "Black";
					Parent->color = "Red";
					return 2;
				}
				else if (Parent->color == "Red" && N->color == "Red") {
					if ((Parent->parent->right == Parent && Parent->parent->left->color != "Red") || (Parent->parent->left == Parent && Parent->parent->right->color != "Red")) {
						rotateRight(Parent, N);
						rotateLeft(Parent->parent, Parent);
						return true;
					}
				}
				else if (flag != 2) {
					rotateRight(N, N->left);
					rotateLeft(Parent, N);		//LR->RL Rotation
					return true;
				}
			}
		}
		else {
			int flag = insert(N->right, val, N);
			if (flag == 1)
				return true;

			if (Parent->left == N) {
				if (Parent->right != nullptr && Parent->right->color == "Red") {			//Re-Colored
					N->color = "Black";
					Parent->right->color = "Black";
					if(Parent != root)
						Parent->color = "Red";
				}
				else if (Parent->color == "Red" && N->color == "Red") {
					if ((Parent->parent->right == Parent && Parent->parent->left->color != "Red") || (Parent->parent->left == Parent && Parent->parent->right->color != "Red")) {
						rotateLeft(Parent, N);
						rotateRight(Parent->parent, Parent);
						return true;
					}
				}
				else if (flag != 2) {
					rotateLeft(N, N->right);
					rotateRight(Parent, N);		//RL->LR Rotation
					return true;
				}

				return 2;
			}
			else if (Parent->right == N) {
				if (Parent->left != nullptr  && Parent->left->color == "Red") {			//Re-Colored
					N->color = "Black";
					Parent->left->color = "Black";
					if (Parent != root)
						Parent->color = "Red";
				}
				else if (Parent->color == "Red" && N->color == "Red") {
					if ((Parent->parent->right == Parent && Parent->parent->left->color != "Red") || (Parent->parent->left == Parent && Parent->parent->right->color != "Red")) {
						rotateLeft(Parent->parent, Parent);
						return true;
					}
				}
				else if (flag != 2) {
					rotateLeft(Parent, N);		//RR->L Rotation
					return true;
				}

				return 2;
			}
		}
	}

public:

	RBT(){
		root = nullptr;
	}

	void insert(int val) {

		if (root == nullptr)
		{
			root = new Node;
			root->data = val;
			root->color = "Black";
		}
		else {
			insert(root, val, root);
		}
	}
};

void main()
{
	RBT t;

	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(8);
	t.insert(9);
	t.insert(10);
	t.insert(11);
	t.insert(12);
	t.insert(13);
	t.insert(14);

	system("pause");
}