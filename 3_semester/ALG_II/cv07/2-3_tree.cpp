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

struct Node {
	int min;
	int max;
	Node* left;
	Node* mid;
	Node* right;
	
	bool is_leaf;

	Node(int key) : min(key), max(-1), left(nullptr), mid(nullptr), right(nullptr), is_leaf(true) {}

	Node(int k2, int k3, Node* l, Node* m, Node* r) : min(k2), max(k3), left(l), mid(m), right(r) {}
};


class TwoTree{
private:
	Node* tree;

public:
	TwoTree(int in){
		this->tree = new Node(in);
	}

	void Insert(int inp){

		if(tree->is_leaf){
			if(tree->max != -1){
				if(tree->min > inp){
					tree->max = tree->min;
					tree->min = inp;
				}
				else{
					tree->max = inp;
				}
			}
			else{
				
			}
		}
	}
};


int main(){

}