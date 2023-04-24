#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
///Konstanta s retezcem vypisovanym, pokud polozka nebyla v ciselniku
const string NOT_FOUND = "Neexistujici polozka";
/**
 * Reprezentace jedne polozky v ciselniku
 */
struct Item {
    int key; ///< Celociselna hodnota, klic polozky
    string value; ///< Nazev nebo jiny retezec popisujici polozku
    
    /**
     * Definice operatoru < pro struktury Item, vysledek porovnani zavisi
     * jen na porovnani jejich klicu.
     */
    bool operator<(const Item a) const{
        return (key<a.key);
    }
};
class Tree{
public:
    Item item;
    Tree* lower = NULL;
    Tree* higher = NULL;
    Tree(Item itm){
        this->item = itm;
    }
    void CreateLeafs(Item currentItem, Tree* tree){
        int intree = tree->item.key;
        if (currentItem.key > intree ){         // vetsi
            if (tree->higher == NULL){
                Tree* higher_child = new Tree( currentItem );
                tree->higher = higher_child;
            }
            else {
                this->higher->CreateLeafs(currentItem, tree->higher);
            }
        }
        else if( currentItem.key < intree ){    // mensi
            if (tree->lower == NULL){
                Tree* lower_child = new Tree( currentItem );
                tree->lower = lower_child;
            }
            else {
                this->lower->CreateLeafs(currentItem, tree->lower);
            }
        }
    }
    void CreateBinaryTree(vector<Item> &items){
        if ( items.empty() ){
            return;
        }
        long unsigned int i = 1;
        while (i < items.size() ){
            this->CreateLeafs(items[i], this);
            i++;
        }
    }
    string SearchItem(int index, Tree* tree){
        if (index == tree->item.key){
            return tree->item.value;
        }
        else if (index > tree->item.key ){         // vetsi
            if (tree->higher != NULL){
                Tree* hiTree = this->higher;
                return SearchItem(index, hiTree);
            }
            else {
                return NOT_FOUND;
            }
        }
        else if( index < tree->item.key ){    // mensi
            if (tree->lower != NULL){
                Tree* loTree = this->lower;
                return SearchItem(index, loTree);
            }
            else {
                return NOT_FOUND;
            }
        }
        return NOT_FOUND;
    }
};
/**
 * Nacteni vstupniho souboru ciselniku do vektoru polozek reprezentovanych
 * strukturami Item, kazda polozka ma celociselny klic (identifikator) 
 * a retezcovou hodnotu (nazev)
 * V souboru se ceka kazda polozka na samostatnem radku, na zacatku je 
 * klic mezerou oddeleny od hodnoty, ta je potom az do konce radku.
 *
 * @param name Jmeno souboru, ze ktereho se polozky budou nacitat
 * @return Vektor vsech polozek nactenych ze souboru
 */
vector<Item> read_items(string name){
    
    ifstream infile; 
    infile.open(name); 
    vector<Item> items;
    Item it;
    if(!infile.is_open()){
        cerr << "File could not be opened" << endl;
        exit(-1);
    }
    
    while (!infile.eof()) {
        infile >> it.key;
        infile.ignore(256, ' ');
        getline(infile,it.value);
        items.push_back(it);
    }
    infile.close();
    return items;
    
}    
/**
 * Nacteni seznamu klicu ze souboru do vektoru celociselnych hodnot.
 * V souboru mohou byt cisla oddelena libovolnymi bilymi znaky.
 *
 * @param name Jmeno souboru, ze ktereho se cisla budou nacitat
 * @return Vektor vsech cisel nactenych ze souboru
 */
vector<int> read_queries(string name){
    
    ifstream infile; 
    infile.open(name); 
    vector<int> queries;
    int i;
    if(!infile.is_open()){
        cerr << "File could not be opened" << endl;
        exit(-1);
    }
    
    while (!infile.eof()) {
        infile >> i;
        queries.push_back(i);
    }
    infile.close();
    return queries;
    
}    
/**
 * Funkce, ktera pomoci binarniho vyhledavaní (neboli
 * vyhledavani pulenim intervalu) najde v ciselniku nactenem
 * reprezentovanem vektorem polozek typu Item tu s danym klicem
 * a vrati jeji retezcovou hodnotu. 
 *
 * @param items Vektor reprezentujici ciselnik
 * @param key Klic, ktery v ciselniku budeme hledat
 * @return Retezcova hodnota (promenna value z polozky Item) polozky
 *         se zadanym klicem
 */
string findItem(vector<Item> &items, int k) {
    //Doplnte telo teto funkce
    int min = 0;                // min                  12
    int max = items.size();     // max             0 18 9, 10 18 14, 10 13 12
    int middle;                 // middle
    if ( items.empty() ){
        return NOT_FOUND;
    }
    while ( min <= max ){
        middle = (min+max)/2;
        if ( items[middle].key == k){
                return items[middle].value;
        }
        else{
            if ( items[middle].key > k ){
                max = middle-1;
            }
            else if ( items[middle].key < k ){
                min = middle+1;
            }
        }
    }
    return NOT_FOUND;
}
/*
void CreateLeafs(Item currentItem, Tree* tree){
    int intree = tree->item.key;
    if (currentItem.key > intree ){         // vetsi
        if (tree->higher == NULL){
            tree->higher = new Tree();
            tree->higher->item = currentItem;
        }
        else {
            CreateLeafs(currentItem, tree->higher);
        }
    }
    else if( currentItem.key < intree ){    // mensi
        if (tree->lower == NULL){
            tree->lower = new Tree();
            tree->lower->item = currentItem;
        }
        else {
            CreateLeafs(currentItem, tree->lower);
        }
    }
}
void CreateBinaryTree(vector<Item> &items, Tree* tree){
    if ( items.empty() ){
        return;
    }
    
    long unsigned int i = 0;
    tree->item = items[i];
    i++;
    while (i < items.size() ){
        CreateLeafs(items[i], tree);
        i++;
    }
};
string SearchItem(int index, Tree* tree){
    int intree = tree->item.key;
    if (index == intree){
        return tree->item.value;
    }
    else if (index > intree ){         // vetsi
        if (tree->higher != NULL){
            return SearchItem(index, tree->higher);
        }
        else {
            return NOT_FOUND;
        }
    }
    else if( index < intree ){    // mensi
        if (tree->lower != NULL){
            return SearchItem(index, tree->lower);
        }
        else {
            return NOT_FOUND;
        }
    }
    return NOT_FOUND;
}
*/
int main(int argc, char** argv){
    
    if(argc < 3){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
    
    vector<Item> items;
    vector<int> queries;
    items = read_items(argv[1]);
    queries = read_queries(argv[2]);
    /* Nadefinujte si vlastni typ Tree, pokud to nebude trida
     * nebo nebudete mit konstruovani celeho stromu z vektrou 
     * items reseno pomoci konstruktoru dane tridy, upravte
     * nasledujici radek
     */
    Tree* t = new Tree(items[0]);
    t->CreateBinaryTree(items);
    cout<<"Binarni vyhledavaci strom"<<endl;
    cout<<"-------------------------"<<endl;
    for (int x:queries) {
        /* Misto t.search(x) na nasledujicim radku dejte volani
         * vami vytvorene funkce pro vyhledavani v binarnim stromu,
         * predejte ji parametr x obsahujici cele cislo k vyhledani.
         */
        cout << x << " - " << t->SearchItem(x, t) << endl;
    }
    sort(items.begin(), items.end());
    cout<<endl;
    cout<<"Vyhledavani pulenim intervalu"<<endl;
    cout<<"-----------------------------"<<endl;
    for (int x:queries) {
        cout << x << " - " << findItem(items, x) << endl;
    }
    return 1;
}