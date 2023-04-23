#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void gen_perm(int k, string s, char a[], bool b[], vector<string>* v){     
    int vel = s.size();
    int pos = vel-k;

    if (k == 0){
        v->push_back(string(a, vel));
        return;
    }
    for (int i=0; i<vel; i++){
        if (b[i]){
            a[pos] = s[i];
            b[i] = false;
            gen_perm(k-1, s, a, b, v);
            b[i] = true;
        }
    }
}



void generate_candidates(string s, vector<string>* v) {
    int permSize = (s.size());
    char a[permSize];
    bool b[permSize];
    
    for (int i=0; i<permSize; i++){
        a[i] = 'a';
        b[i] = true;
    }
    if ( permSize == 1 ){
        v->push_back(s);
        return;
    }
    gen_perm(permSize, s, a, b, v);
}


int main(int argc, char** argv)
{
    if(argc < 2){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
    vector<string> *v = new vector<string>;
    generate_candidates(argv[1],v);
    sort(v->begin(), v->end());
    for(unsigned int i = 1; i<=v->size(); i++){
        cout << (*v)[i-1] << ((i%10 == 0)?'\n':' ');
    }
    delete v;
    return 1;
}