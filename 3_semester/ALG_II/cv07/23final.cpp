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
#include <queue>
using namespace std;

enum{
	UNCHECKED = 0,
	PROCESSING = 1,
	CHECKED = 2,

	NOT_EXISTS = -1,
};

struct Node {
	int min;
	int max;
	Node* left;
	Node* mid;
	Node* right;
	Node* parent;
	
	bool is_leaf;
	int status = UNCHECKED;


	Node() : min(-1), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(nullptr), is_leaf(true) {}
	Node(int key) : min(key), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(nullptr), is_leaf(true) {}
	Node(int key, Node* p) : min(key), max(-1), left(nullptr), mid(nullptr), right(nullptr), parent(p), is_leaf(true) {}
	Node(int k2, Node* l, Node* r) : min(k2), max(-1), left(l), mid(nullptr), right(r), parent(nullptr), is_leaf(false) {}
	Node(int k2, Node* l, Node* m, Node* r) : min(k2), left(l), mid(m), parent(nullptr), right(r) {}
	Node(int k2, Node* l, Node* r, Node* p, bool leaf) : min(k2), max(-1), left(l), mid(nullptr), right(r), parent(p), is_leaf(leaf) {}

	void MinMax(int inp){
		if(max == -1){
			if(inp < min){
				max = min;
				min = inp;
			}
			else{
				max = inp;
			}
		}
		else{
			throw logic_error("Node already has max");
		}
	}
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
					int tmp = tree->max;
					tree->max = -1;

					tree->left = new Node(inp, tree);
					tree->right = new Node(tmp, tree);
				}
				//input == middle
				else if (inp > tree->min && inp < tree->max){
					int tmp_min = tree->min;
					int tmp_max = tree->max;
					tree->min = inp;
					tree->max = -1;

					tree->left = new Node(tmp_min, tree);
					tree->right = new Node(tmp_max, tree);
				}
				//max == middle
				else{
					int tmp = tree->min;
					tree->min = tree->max;
					tree->max = -1;

					tree->left = new Node(tmp, tree);
					tree->right = new Node(inp, tree);
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
		//Parent node has only one number
			//left = inp < min
			if (inp < tree->min){
				this->Insert(inp, tree->left);
			}
			//right = inp > min
			else if (inp > tree->min){
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
					int tmp = n_inp->max;
					n_inp->max = -1;
					n_inp->parent->mid = new Node(tmp, n_inp->parent);
				}
				//input == middle
				else if (inp > n_inp->min && inp < n_inp->max){
					n_inp->parent->MinMax(inp);

					int tmp = n_inp->min;
					n_inp->min = n_inp->max;
					n_inp->max = -1;
					n_inp->parent->mid = new Node(tmp, n_inp->parent);					
				}
				//max == middle
				else{
					n_inp->parent->MinMax(n_inp->max);

					int tmp = n_inp->min;
					n_inp->min = inp;
					n_inp->max = -1;
					if (n_inp->parent->mid != nullptr){
						n_inp->parent->left = n_inp->parent->mid;
					}
					n_inp->parent->mid = new Node(tmp, n_inp->parent);				
				}

				if (n_inp->left != nullptr || n_inp->right != nullptr){
					n_inp->is_leaf = false;
				}
			}
			else{ 
				//There is no max
				if(inp < n_inp->min && n_inp->max == -1){
					n_inp->max = n_inp->min;
					n_inp->min = inp;		
				}
				else if(inp > n_inp->min && n_inp->max == -1){
					if(n_inp->right != nullptr ){
						this->Insert(inp, n_inp->right);
					}
					else{
						n_inp->max = inp;
					}
				}
				//There is max
				else if(inp < n_inp->min){
					int tmp = n_inp->max;
					n_inp->max = -1;

					n_inp->left = new Node(inp, n_inp);
					n_inp->right = new Node(tmp, n_inp);

					this->Insert(n_inp->min, n_inp->parent);
				}
				else if(inp > n_inp->min && inp < n_inp->max){
					int tmp_min = n_inp->min;
					int tmp_max = n_inp->max;
					n_inp->min = inp;
					n_inp->max = -1;

					n_inp->left = new Node(tmp_min, n_inp);
					n_inp->right = new Node(tmp_max, n_inp);

					this->Insert(inp, n_inp->parent);
				}
				else if(inp > n_inp->max){
					int tmp = n_inp->min;
					n_inp->min = n_inp->max;
					n_inp->max = -1;

					n_inp->left = new Node(tmp, n_inp);
					n_inp->right = new Node(inp, n_inp);

					this->Insert(n_inp->min, n_inp->parent);
				}
			}
		}
		//When inp (child key) should shift into parent, but there is no space for it
		else if (n_inp->max != -1){
			//min is middle value
			//-------------------------------------------------------------------MISTAKE HERE - cannot create new node, insertion needed
			if(inp < n_inp->min){
				int tmp = n_inp->max;
				n_inp->max = -1;
				Node* new_left = new Node(n_inp->mid->min);
				Node* new_right = new Node(n_inp->right->min);

				n_inp->mid = nullptr;
				n_inp->right = nullptr;

				n_inp->right = new Node(tmp, n_inp);
				n_inp->right->left = new_left;
				n_inp->right->left->parent = n_inp->right;

				n_inp->right->right = new_right;
				n_inp->right->right->parent = n_inp->right;

			}
			//input is middle value
			else if(inp > n_inp->min && inp < n_inp->max){

				Node* tmp_node_left = new Node(n_inp->min, n_inp->left);
				Node* tmp_node_right = new Node(n_inp->max, n_inp->right);

				n_inp->parent = new Node(inp, tmp_node_left, tmp_node_right);
				n_inp = n_inp->parent;
				this->tree = n_inp;
            }
			//max is middle value
			else if(inp > n_inp->max){
				int tmp = n_inp->max;
				n_inp->max = -1;
				Node* new_left = new Node(n_inp->mid->min);
				Node* new_right = new Node(n_inp->left->min);

				n_inp->mid = nullptr;
				n_inp->left = nullptr;

				n_inp->left = new Node(tmp, n_inp);
				n_inp->left->right = new_left;
				n_inp->left->right->parent = n_inp->left;

				n_inp->left->left = new_left;
				n_inp->left->left->parent = n_inp->left;
            }
		}
		else{
			//fill child (if empty)
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

	void Search(int inp){
		queue<int> q;

		q.push(this->tree->min);
		if(this->tree->max != NOT_EXISTS){
			q.push(this->tree->max);
		}

		while(!q.empty()){
			
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

    return 0;
}