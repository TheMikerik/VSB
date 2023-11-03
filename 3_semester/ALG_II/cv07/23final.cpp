/*
https://homel.vsb.cz/~rec0021/

2-3 strom insert

Vaším úkolem je implementovat třídu TwoThreeTree a dnes jen jednu metodu insert pro vložení prvku do B-stromu. 

class TwoThreeTree {
public:
	TwoThreeTree();
	void insert(int value);
};

Hotovou práci po kontrole zasílejte na adresu: radovan.recka.st@vsb.cz
Termín odevzdání: příští cvičení(6.11.2023)
Do předmětu zprávy uveďte: ALGC06_7
Odevzdávejte pouze zdrojové a hlavičkové kódy. Binárku(.exe) nebo celé projekty ne.
*/

#include <iostream>
using namespace std;

struct Node {
	int min;
	int max;
	Node* left;
	Node* mid;
	Node* right;

	Node* parent;
	
	bool is_leaf;

	Node() : min(-1), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(nullptr), is_leaf(true) {}
	Node(int key) : min(key), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(nullptr), is_leaf(true) {}
	Node(int key, Node* p) : min(key), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(p), is_leaf(true) {}

	void MinMax(int inp){
		if(inp < min){
			max = min;
			min = inp;
		}
		else{
			max = inp;
		}
	}
	//Node(int k2, int k3, Node* l, Node* m, Node* r) : min(k2), max(k3), left(l), mid(m), right(r), is_leaf(false) {}
};


class TwoTree{
private:
	Node* tree;

public:
	TwoTree(){
		this->tree = new Node();
	}

	void Insert(int inp){
		if(tree->is_leaf){
			if(tree->min == -1){
				tree->min = inp;
			}
			else if(tree->max != -1){
				//min == middle
				if(inp < tree->min){
					tree->left = new Node(inp, tree);
					tree->right = new Node(tree->max, tree);
					tree->max = -1;
				}
				//input == middle
				else if (inp > tree->min && inp < tree->max){
					tree->left = new Node(tree->min, tree);
					tree->right = new Node(tree->max, tree);
					tree->min = inp;
					tree->max = -1;
				}
				//max == middle
				else{
					tree->left = new Node(tree->min, tree);
					tree->right = new Node(inp, tree);
					tree->min = tree->max;
					tree->max = -1;
				}

				tree->is_leaf = false;
			}
			else{ //Theres no max
				if(inp < tree->min){
					tree->max = tree->min;
					tree->min = inp;		
				}
				else{
					tree->max = inp;
				}
			}
		}
		else{ //fill child
			//left = inp < min
			if (inp < tree->min && tree->max == -1){
				this->Insert(inp, tree->left);
			}
			//right = inp > min
			else if (inp > tree->min && tree->max == -1){
				this->Insert(inp, tree->right);
			}
		}
	}

	void Insert(int inp, Node* n_inp){
		if(n_inp->is_leaf){
			if(n_inp->min == -1){
				n_inp->min = inp;
			}
			//When input (child) is fully filled and parent is not
			else if(n_inp->max != -1 && n_inp->parent->max == -1){
				//min == middle
				if(inp < n_inp->min){
					n_inp->parent->MinMax(n_inp->min);
					n_inp->min = inp;
					
					//MID TO DO

					n_inp->max = -1;										
				}
				//input == middle
				else if (inp > n_inp->min && inp < n_inp->max){
					n_inp->parent->MinMax(inp);
					
				}
				//max == middle
				else{
					n_inp->parent->MinMax(n_inp->max);
					
				}

				n_inp->is_leaf = false;
			}
			else{ //There is no max
				if(inp < n_inp->min){
					n_inp->max = n_inp->min;
					n_inp->min = inp;		
				}
				else{
					n_inp->max = inp;
				}
			}
		}
		else{ //fill child
			//left = inp < min
			if (inp < n_inp->min && n_inp->max == -1){
				this->Insert(inp, n_inp->left);
			}
			//right = inp > min
			else if (inp > n_inp->min && n_inp->max == -1){
				this->Insert(inp, n_inp->right);
			}
		}
	}
};


int main(){
    TwoTree t;

	t.Insert(500);
	t.Insert(600);
	t.Insert(700);
	t.Insert(400);
	t.Insert(300);
	t.Insert(200);
	t.Insert(100);
	t.Insert(800);
	t.Insert(900);
	t.Insert(1000);

    return 0;
}