#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Reprezentace jedné polozky urcene k preprave
 */
struct item {
    int weight; ///< Vaha polozky
    int price;  ///< Cena za prepravu teto polozky
};


 
/**
 * Nacteni vstupniho souboru do vektoru obsahujiciho pro kazdou polozku
 * (coz odpovida radku ve vstupnim souboru) dvojici celociselnych hodnot 
 * vaha a cena
 *
 * @param name Jmeno souboru, ze ktereho se polozky budou nacitat
 * @return Vektor vsech polozek nactenych ze souboru
 */
vector<item> read_file(string name){
	
    ifstream infile; 
    infile.open(name); 
    vector<item> items;
    item it;

    if(!infile.is_open()){
        cerr << "File could not be opened" << endl;
        exit(-1);
    }
	
    while (!infile.eof()) {
        infile >> it.weight >> it.price;
        items.push_back(it);
    }
	infile.close();
    return items;
	
}



    /*
    gen_sets2(nrElem) {
    nrSets:= 1<<nrElem
    pouzij podmnozinu
    nrSets--
    nrSets krat opakuj
        j:=0
        dokud bits[j]=true
            bits[j]:=false
            j++
        bits[j]:=true
        pouzij podmnozinu
    */

   int gen_set(int elements, vector<item> itemy, int max){
        int nrSets = 1<<elements; // pocet podmnozin
        nrSets--;
        int price_final = 0;
    
        vector<bool> podmnozina(elements, false);

        for (int i=0; i<nrSets; i++){
            int tmp_weigth = 0;
            int tmp_price = 0;

            int j;
            for (j=0; podmnozina[j] == true; j++){    // 0 0 1, 
                podmnozina[j] = false;    
            }
            podmnozina[j] = true;

            for (int k = 0; k<elements; k++){           
                if ( podmnozina[k] ){               // dokud mame podmnozinu
                    tmp_price += itemy[k].price;
                    tmp_weigth += itemy[k].weight;
                }
            }
            if ( tmp_weigth <= max && tmp_price > price_final ){
                price_final = tmp_price;
            }
        }

    return price_final;
   }



/**
 * Najde maximalni mozny soucet cen produktu takovy, 
 * ze soucet vah polozek do nej zapoctenych je 
 * mensi nebo povolene nosnosti.
 *
 * @param items Vektor polozek, mezi nimiz hledame tu maximalni sadu
 * @param max_load Povolena nosnost - maximalni mozny soucet vah vybranych produktu
 * @return Nalezena maximalni mozna cena pri splneni podminek
 *
 */
int find_max(vector<item> items, int max_load) {
	
//Doplnte telo teto funkce
    int cannot_be_loaded = 0;

    for (int i = 0; i < items.size(); i++){
        if ( items[i].weight > max_load ){
            cannot_be_loaded++;
        }
    }
    if ( cannot_be_loaded == items.size() ){
        return 0;
    } else{
        return gen_set( items.size(), items, max_load );
    }
}


int main(int argc, char** argv)
{
    if(argc < 3){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
		
    cout << find_max(read_file(argv[1]), stoi(argv[2])) << endl;
	return 1;
}