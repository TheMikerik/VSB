#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

///Konstanta s retezcem vypisovanym, pokud polozka nebyla v ciselniku
const string NOT_FOUND = "Neexistujici polozka";

struct Item {
    int key; ///< Celociselna hodnota, klic polozky
    string value; ///< Nazev nebo jiny retezec popisujici polozku
    
    bool operator<(const Item a) const{
        return (key<a.key);
    }
};

struct Tree{
    Item item;

    Tree* lower = NULL;
    Tree* higher = NULL;
};

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
    
    int i = 0;
    tree->item = items[i];
    i++;
    while ( i < items.size() ){
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

int main(int argc, char** argv){
    
    if(argc < 3){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
    
    vector<Item> items;
    vector<int> queries;
    items = read_items(argv[1]);
    queries = read_queries(argv[2]);

    Tree* t = new Tree();
    CreateBinaryTree(items, t);
    cout<<"Binarni vyhledavaci strom"<<endl;
    cout<<"-------------------------"<<endl;
    for (int x:queries) {
        cout << x << " - " << SearchItem(x, t) << endl;
    }
/*
    sort(items.begin(), items.end());
    cout<<endl;
    cout<<"Vyhledavani pulenim intervalu"<<endl;
    cout<<"-----------------------------"<<endl;
    for (int x:queries) {
        cout << x << " - " << findItem(items, x) << endl;
    }*/
    return 1;
}


