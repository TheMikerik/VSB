#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#define N "no"
#define C "checking"
#define Y "yes"

using namespace std;


/**
 * Reprezentace vrcholu grafu
 */
struct Node {
    vector<Node *> neighbors;  ///< Vektor ukazetelu na sousedni vrcholy
    int id; ///< Identifikacni cislo vrcholu
    
	// Muzete si pridat dalsi polozky, ktere se budou hodit pro reseni ulohy
	// Pokud je chcete mit inicializovane na stejnou hodnotu, staci inicializovat zde, napr.:
	// int tmp = -1;
    string isChecked = N;
    int distance = 0;
};

/**
 * Reprezentace grafu
 */
struct Graph {
    Node* nodes;  ///< Pole vrcholu grafu
    int count;    ///< Pocet vrcholu grafu
};

/**
 * Nacte graf ze souboru
 *
 * @param fileName Jmeno souboru, ze ktereho bude graf nacten
 * @return Nacteny graf ve forme struktury Graph
 */

Graph readGraph(string fileName) {
    int count;
    int from, to;
    ifstream infile; 
    infile.open(fileName); 

    if(!infile.is_open()){
        cerr << "File could not be opened" << endl;
        exit(-1);
    }
	
    infile >> count;
    Node* nodes = new Node[count];
    Graph graph = {nodes, count};

    for (int i = 0; i < count; i++) {
        nodes[i].id = i;
    }
    while (!infile.eof()) {
        infile >> from >> to;
        if (!infile.fail()) {
            nodes[from].neighbors.push_back(nodes + to);
            nodes[to].neighbors.push_back(nodes + from);
        }
    }
    infile.close();	
    return graph;
}

/**
 * Pomocna funkce, ktera nesmi byt volana ve finalni verzi (neprosly by testy v Kelvinu).
 * Vypise graf v nasledujicim formatu:
 *   - pro kazdy vrchol bude jeden radek
 *   - radek zacina id toho vrcholu a za dvojteckou nasleduje mezerami oddeleny 
 *     seznam id vsech jeho sousedu
 *
 * @param graph Graf, ktery bude vypsan
 */
void printGraph(Graph graph){
	for (int i=0; i<graph.count; i++){
		cout << graph.nodes[i].id << ": ";
		for (Node *x:graph.nodes[i].neighbors){
			cout<< x->id << " ";
		}
		cout << endl;
	}
}

/**
 * Vypise na standardni vystup vsechny hodnoty z vektoru oddelene mezerami a odradkuje.
 *
 * @param v Vektor, jehoz hodnoty se vypisuji
 */
void printVector(vector<int> v){
	for(int i: v){
		cout << i << " ";
	}
	cout << endl;
}

/**
  * Najde vsechny komponenty v grafu. Pro kazdou komponentu secte hodnoty id vrcholu teto 
  * komponenty. Vsechny takto ziskane soucty vraci ve forme vektoru.
  *
  * @param graph Graf, ve kterem funkce hleda komponenty
  * @return Vektor, ktery pro kazdou komponentu grafu obsahuje soucet hodnot vrcholu te komponenty
  *
  */
vector<int> findComponents(Graph graph) {
  
  //Doplnte telo teto funkce


  vector<int> components;

  for (int i=0; i < graph.count; i++){

    if ( graph.nodes[i].isChecked == N ){       // Nova (necheckla) cast grafu
        int component_size = 0;                 
        stack<Node *> stack;            

        Node* current = &graph.nodes[i];        // init node

        current->isChecked = C;             
        stack.push(current);                    // stack != null
        //component_size += current->id;

        while ( !stack.empty() ){               // dokud existuje necheckly soused
            Node* next = stack.top();                   // nahraju init node (nebo sousedy pri dalsim pruchodu)
            stack.pop();                
            component_size += next->id;     

            for (int i = 0; i<next->neighbors.size(); i++){     // Dle poctu sousedu udelam pruchody grafem
                    
                if ( next->neighbors[i]->isChecked == N ){      // Pokud soused neni checkly, hodim ho do stacku

                    stack.push(next->neighbors[i]);
                    //component_size += next->neighbors[i]->id;
                    next->neighbors[i]->isChecked = C;          // Zmena z N na C 
                }                               
            }
            next->isChecked = Y;
        }

        components.push_back(component_size);
    }
  }
  return components;
}

/**
  * V grafu najde vsechny vrcholy, ktere jsou od zadaneho vrcholu presne v zadane vzdalenosti. 
  * Vrchol v2 je ve vzdalenosti x od vrcholu v1, jestlize se z v1 da pres x hran dojit k v2 
  * a pres mensi pocet hran to nejde.
  *
  * @param graph Graf, ve kterem funkce hleda vrcholy
  * @param node id vrcholu, od ktereho se hleda
  * @param dist Vzdalenost, ve ktere se maji nachazet hledane vrcholy
  * @return Vektor, ktery obsahuje id vsech nalezenych vrcholu 
  *
  */
vector<int> findNeighbours(Graph graph, int node, int dist){
  
  //Doplnte telo teto funkce

    vector<int> destination;
    queue<Node*> queue;

    queue.push(&graph.nodes[node]);         // Init node
    graph.nodes[node].isChecked = C;

    while ( !queue.empty() ){
        Node* next = queue.front();         // Nastavim si checkovanou node
        queue.pop();                        // a nasledne ji vyhodim z queue

        if ( next->distance != dist){           // dokud ne, tak prochazim jeji sousedy
            for (int i = 0; i<next->neighbors.size(); i++){
                if ( next->neighbors[i]->isChecked == N ){      // Jakykoliv soused
                    next->neighbors[i]->isChecked = C;          // Nastavim checking
                    queue.push(next->neighbors[i]);             // Nahraju do queue
                    next->neighbors[i]->distance = next->distance + 1;      // nynejsi vzdalenost + 1
                }
            }
        }
        else{ destination.push_back(next->id);  }    // pridam k vysledkum

        next->isChecked = Y;
    }
    return destination;  
}

		


int main(int argc, char** argv)
{
    if(argc < 4){
        return -1;
    }
	
    Graph graph;
    vector<int> vect;
    graph = readGraph(argv[1]);
    vect = findComponents(graph);
    sort(vect.begin(), vect.end());
    cout << "Komponenty: ";
    printVector(vect);
    delete [] graph.nodes;

    /* Pro jistotu pred volanim druhe pozadovane funkce se 
    cely graf nacte znovu, aby pripadne zmeny, pomocne hodnoty
    atd. provedene/nastavene v grafu volanim prvni funkce nemohly
    ovlivnit vysledek provedeni druhe funkce. */


    graph = readGraph(argv[1]);
    vect = findNeighbours(graph, stoi(argv[2]), stoi(argv[3]));
    sort(vect.begin(), vect.end());
    cout << "Sousede vrcholu " << argv[2] << " ve vzdalenosti " << argv[3]<< ": ";
    printVector(vect);
    delete [] graph.nodes;
    return 1;
}