#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct CheckedWord{
    string wrd;
    int count = 1;
};

vector<CheckedWord> count_words(vector<string> w){
    vector<CheckedWord> temp_vec;
    bool first = true;
    CheckedWord tmp;

    while( !w.empty()){
        if (first){
            tmp.wrd = w.back();
            temp_vec.push_back(tmp);
            w.pop_back();

            first = false;
        }
        else{
            tmp.wrd = w.back();
            bool is_part = false;

            for (int i = 0; i < temp_vec.size(); i++){
                if( tmp.wrd == temp_vec[i].wrd){
                    temp_vec[i].count++;
                    is_part = true;
                }
            }
            if (!is_part){
                temp_vec.push_back(tmp);
            }
            w.pop_back();
        }
    }

    return temp_vec;
}

void print_final(vector<CheckedWord> c){
    while(!c.empty()){
        cout << "Slovo: " << c.back().wrd << " --> Cetnost: " << c.back().count << endl;
        c.pop_back();
    }
}

int main(){
    std::string path = "./words.txt";
    std::ifstream infile(path);

    if(!infile.is_open()){
        std::cerr << "File cannot be loaded" << std::endl;
        exit(-1);
    }
    if(infile.is_open()){
        std::cout << "File opened" << std::endl;
    }

    string word;
    vector<std::string> words;
    int lines = 0;
    for (lines; !infile.eof(); lines++){
        infile >> word;
        words.push_back(word);
    }
    infile.close();
    
    cout << "Lines: " << lines << endl;
    cout << "Counting" << endl;


    vector<CheckedWord> counter;
    counter = count_words(words);

    print_final(counter);

    return 0;
}