#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Word_Count{
    string word;
    int count = 1;
};

void CheckFile(string input){
    ifstream file(input);
    if(!file.is_open()){
        cerr << "File cannot be loaded" << endl;
        exit(-1);
    }
    if(file.is_open()){
        cout << "File opened" << endl;
    }
    file.close();
}

vector<string> ScanWords(string input){
    ifstream file(input);
    string word;
    vector<string> words;

    int lines = 0;
    while(!file.eof()){
        file >> word;
        words.push_back(word);
        lines++;
    }
    file.close();

    cout << "Lines: " << lines << endl;
    cout << "Counting..." << endl;

    return words;
}

vector<Word_Count> count_words(vector<string> input){
    vector<Word_Count> tmp_vector;
    bool first = true;
    Word_Count current;

    while( !input.empty()){
        if (first){
            current.word = input.back();
            tmp_vector.push_back(current);
            input.pop_back();

            first = false;
        }
        else{
            current.word = input.back();
            bool is_part = false;

            for (int i = 0; i < tmp_vector.size(); i++){
                if( current.word == tmp_vector[i].word){
                    tmp_vector[i].count++;
                    is_part = true;
                }
            }
            if (!is_part){
                tmp_vector.push_back(current);
            }
            input.pop_back();
        }
    }

    return tmp_vector;
}

void print_final(vector<Word_Count> input){
    while(!input.empty()){
        cout << "Slovo: " << input.back().word << " --> Cetnost: " << input.back().count << endl;
        input.pop_back();
    }
}

int main(){
    string path = "./words.txt";
    
    CheckFile(path);
    vector<string> words = ScanWords(path);
    vector<Word_Count> counter;
    counter = count_words(words);
    print_final(counter);

    return 0;
}